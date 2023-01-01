/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2016. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

// MTK fusion include
#include <vector>

#include "RfxVoidData.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxIntsData.h"
#include "RfxMessageId.h"

// Ims Op Control Local include
#include "RmcOpImsControlRequestHandler.h"
#include "RmcOpImsControlInterface.h"

#define RFX_LOG_TAG "RmcOpImsControl"

 // register handler to channel
RFX_IMPLEMENT_OP_HANDLER_CLASS(RmcOpImsControlRequestHandler, RIL_CMD_PROXY_1);

// register request to RfxData
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SWITCH_RCS_ROI_STATUS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_UPDATE_RCS_CAPABILITIES);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_UPDATE_RCS_SESSION_INFO);

static const int requests[] = {
    RFX_MSG_REQUEST_SWITCH_RCS_ROI_STATUS,
    RFX_MSG_REQUEST_UPDATE_RCS_CAPABILITIES,
    RFX_MSG_REQUEST_UPDATE_RCS_SESSION_INFO
};

RmcOpImsControlRequestHandler::RmcOpImsControlRequestHandler(
    int slot_id, int channel_id) : RfxBaseHandler(slot_id, channel_id) {
    // register to handle request
    registerToHandleRequest(requests, sizeof(requests) / sizeof(int));
}

RmcOpImsControlRequestHandler::~RmcOpImsControlRequestHandler() {
}

void RmcOpImsControlRequestHandler::onHandleTimer() {
}

void RmcOpImsControlRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
    int requestId = msg->getId();
    // logD(RFX_LOG_TAG, "onHandleRequest: %s", RFX_ID_TO_STR(requestId));
    switch (requestId) {
        case RFX_MSG_REQUEST_SWITCH_RCS_ROI_STATUS:
            switchRcsRoiStatus(msg);
            break;
        case RFX_MSG_REQUEST_UPDATE_RCS_CAPABILITIES:
            updateRcsCapabilities(msg);
            break;
        case RFX_MSG_REQUEST_UPDATE_RCS_SESSION_INFO:
            updateRcsSessionInfo(msg);
            break;
        default:
            break;
    }
}

void RmcOpImsControlRequestHandler::switchRcsRoiStatus(const sp<RfxMclMessage>& msg) {
    int status = ((int *)msg->getData()->getData())[0];
    logD(RFX_LOG_TAG, "switchRcsRoiStatus:%d", status);
    int err = RIL_E_GENERIC_FAILURE;
    switch (status) {
        case 0:
        case 1:
        {
            sp<RfxAtResponse> p_response =
                atSendCommand(String8::format("AT+EIMSRCS=%d", status + 3));
            err = p_response->getError();
            if (err < 0 || p_response->getSuccess() == 0) {
                logD(RFX_LOG_TAG, "switchRcsRoiStatus error:%d", err);
            }
            break;
        }

        default:
            logD(RFX_LOG_TAG, "switchRcsRoiStatus error, unsupport status");
            break;
    }

    sp<RfxMclMessage> response
        = RfxMclMessage::obtainResponse(msg->getId(),
                                        err >= 0 ? RIL_E_SUCCESS : RIL_E_GENERIC_FAILURE,
                                        RfxVoidData(),
                                        msg);
    responseToTelCore(response);
}

void RmcOpImsControlRequestHandler::updateRcsCapabilities(const sp<RfxMclMessage>& msg) {
    char** data = (char**)msg->getData()->getData();
    char* mode = data[0];
    char* featureTags = data[1];
    int err = RIL_E_GENERIC_FAILURE;
    logD(RFX_LOG_TAG, "updateRcsCapabilities mode:%s, featureTags:%s", mode, featureTags);

    sp<RfxAtResponse> p_response =
        atSendCommand(String8::format("AT+EIMSRCS=%s,%s", mode, featureTags));
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logD(RFX_LOG_TAG, "switchRcsRoiStatus error:%d", err);
    }

    sp<RfxMclMessage> response
        = RfxMclMessage::obtainResponse(msg->getId(),
                                        err >= 0 ? RIL_E_SUCCESS : RIL_E_GENERIC_FAILURE,
                                        RfxVoidData(),
                                        msg);
    responseToTelCore(response);
}

void RmcOpImsControlRequestHandler::updateRcsSessionInfo(const sp<RfxMclMessage>& msg) {
    int count = ((int *)msg->getData()->getData())[0];
    logD(RFX_LOG_TAG, "updateRcsSessionInfo count:%d", count);
    int err = RIL_E_GENERIC_FAILURE;

    switch (count) {
        case 0:
        case 1:
        case 254:
        {
            sp<RfxAtResponse> p_response =
                atSendCommand(String8::format("AT+EIMSRCSCONN=%d", count));
            err = p_response->getError();
            if (err < 0 || p_response->getSuccess() == 0) {
                logD(RFX_LOG_TAG, "switchRcsRoiStatus error:%d", err);
            }
            break;
        }

        default:
            logD(RFX_LOG_TAG, "updateRcsSessionInfo error, unsupport count");
            break;
    }
    sp<RfxMclMessage> response
        = RfxMclMessage::obtainResponse(msg->getId(),
                                        err >= 0 ? RIL_E_SUCCESS : RIL_E_GENERIC_FAILURE,
                                        RfxVoidData(),
                                        msg);
    responseToTelCore(response);
}
