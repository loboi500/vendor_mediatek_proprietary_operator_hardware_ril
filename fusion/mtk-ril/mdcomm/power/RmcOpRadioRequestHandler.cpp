/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2017. All rights reserved.
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

#include "RmcOpRadioRequestHandler.h"
#include "libmtkrilutils.h"

#define RFX_LOG_TAG "RmcOpRadioReq"

RFX_IMPLEMENT_OP_HANDLER_CLASS(RmcOpRadioRequestHandler, RIL_CMD_PROXY_9);

RmcOpRadioRequestHandler::RmcOpRadioRequestHandler(int slotId, int channelId):
        RmcRadioRequestHandler(slotId, channelId) {
    const int requests[] = {RFX_MSG_REQUEST_COMMAND_BEFORE_RADIO_POWER,
            };
    registerToHandleRequest(requests, sizeof(requests)/sizeof(int));
}

RmcOpRadioRequestHandler::~RmcOpRadioRequestHandler() {
}

void RmcOpRadioRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
    int id = msg->getId();
    logD(RFX_LOG_TAG, "onHandleRequest: %d", id);
    switch(id) {
        case RFX_MSG_REQUEST_COMMAND_BEFORE_RADIO_POWER:
            onhandlePreRadioCommand(msg);
            break;
        default:
            RmcRadioRequestHandler::onHandleRequest(msg);
            break;
    }
}

void RmcOpRadioRequestHandler::onhandlePreRadioCommand(const sp<RfxMclMessage>& msg) {
    if (isOp12Support()) {
        String8 pco = getMclStatusManager()->getString8Value(RFX_STATUS_KEY_PCO_STATUS,
                String8(""));
        int power = ((int *)msg->getData()->getData())[0];
        char propValue[RFX_PROPERTY_VALUE_MAX] = {0};
        // new test case.: don't control radio flow at open device
        rfx_property_get("persist.vendor.pco5.radio.ctrl", propValue, "0");
        if (pco == String8::format("FF00:5") && !power && (atoi(propValue) != 0)) {
            logI(RFX_LOG_TAG, "Send COPS");
            atSendCommand("AT+COPS=2");
        }
    }
}