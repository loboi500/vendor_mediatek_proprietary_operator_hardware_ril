/*
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
#include <hardware_legacy/mtk_power.h>
#include <telephony/ril_cdma_sms.h>
#include <telephony/mtk_ril.h>
#include <cutils/sockets.h>
#include <cutils/jstring.h>
#include <telephony/record_stream.h>
#include "mtk_log.h"
#include <utils/SystemClock.h>
#include <pthread.h>
#include <cutils/jstring.h>
#include <sys/types.h>
#include <sys/limits.h>
#include <sys/system_properties.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/un.h>
#include <assert.h>
#include <netinet/in.h>
#include <cutils/properties.h>
#include <RilSapSocket.h>
#include <ril_service.h>
#include <sap_service.h>
#include "libmtkrilutils.h"
#include "ril_internal.h"
#include <telephony/mtk_rilop.h>
#include <rilop_service.h>
#include "RfxHandlerManager.h"
#include "RfxMessageId.h"

#ifdef HAVE_AEE_FEATURE
#include "aee.h"
#endif

#undef LOG_TAG
#define LOG_TAG "RILC-OP"

// To indicate useless ID
#define INVALID_ID -1

namespace android {
// #define NUM_ELEMS(a)     (sizeof (a) / sizeof (a)[0])

static CommandInfo s_mtk_op_commands[] = {
#include <telephony/mtk_ril_op_commands.h>
};

static UnsolResponseInfo s_mtk_op_unsolResponses[] = {
#include <telephony/mtk_ril_op_unsol_commands.h>
};

extern "C" android::CommandInfo *getOpCommandInfo(int request) {
    mtkLogD(LOG_TAG, "getOpCommandInfo: request %d", request);
    android::CommandInfo *pCI = NULL;

   for (int i = 0; i < (int)NUM_ELEMS(s_mtk_op_commands); i++) {
        if (request == s_mtk_op_commands[i].requestNumber) {
            pCI = &(s_mtk_op_commands[i]);
            break;
        }
    }

    if (pCI == NULL) {
        mtkLogI(LOG_TAG, "getOpCommandInfo: unsupported request %d", request);
    }
    return pCI;
}

extern "C" UnsolResponseInfo *getOpUnsolResponseInfo(int unsolResponse) {
    mtkLogD(LOG_TAG, "getOpUnsolResponseInfo: unsolResponse %d", unsolResponse);
    android::UnsolResponseInfo *pUnsolResponseInfo = NULL;

    for (int i = 0; i < (int)NUM_ELEMS(s_mtk_op_unsolResponses); i++) {
        if (unsolResponse == s_mtk_op_unsolResponses[i].requestNumber) {
            pUnsolResponseInfo = &(s_mtk_op_unsolResponses[i]);
            mtkLogD(LOG_TAG, "find mtk op unsol index %d for %d, waketype: %d", i, unsolResponse, pUnsolResponseInfo->wakeType);
            break;
        }
    }

    if (pUnsolResponseInfo == NULL) {
        mtkLogI(LOG_TAG, "Can not find mtk op unsol index %d", unsolResponse);
    }
    return pUnsolResponseInfo;
}

extern "C" int getOpRequestIdFromMsgId(int msgId) {
    switch(msgId) {
        // RIL Request
        case RFX_MSG_REQUEST_SET_INCOMING_VIRTUAL_LINE:
            return RIL_REQUEST_SET_INCOMING_VIRTUAL_LINE;
        case RFX_MSG_REQUEST_DIAL_FROM:
            return RIL_REQUEST_DIAL_FROM;
        case RFX_MSG_REQUEST_SEND_USSI_FROM:
            return RIL_REQUEST_SEND_USSI_FROM;
        case RFX_MSG_REQUEST_CANCEL_USSI_FROM:
            return RIL_REQUEST_CANCEL_USSI_FROM;
        case RFX_MSG_REQUEST_SET_EMERGENCY_CALL_CONFIG:
            return RIL_REQUEST_SET_EMERGENCY_CALL_CONFIG;
        case RFX_MSG_REQUEST_DEVICE_SWITCH:
            return RIL_REQUEST_DEVICE_SWITCH;
        case RFX_MSG_REQUEST_CANCEL_DEVICE_SWITCH:
            return RIL_REQUEST_CANCEL_DEVICE_SWITCH;
        case RFX_MSG_REQUEST_EXIT_SCBM:
            return RIL_REQUEST_EXIT_SCBM;
        case RFX_MSG_REQUEST_SEND_RSU_REQUEST:
            return RIL_REQUEST_SEND_RSU_REQUEST;
        case RFX_MSG_REQUEST_SWITCH_RCS_ROI_STATUS:
            return RIL_REQUEST_SWITCH_RCS_ROI_STATUS;
        case RFX_MSG_REQUEST_UPDATE_RCS_CAPABILITIES:
            return RIL_REQUEST_UPDATE_RCS_CAPABILITIES;
        case RFX_MSG_REQUEST_UPDATE_RCS_SESSION_INFO:
            return RIL_REQUEST_UPDATE_RCS_SESSION_INFO;

        // RIL Unsol Request
        case RFX_MSG_UNSOL_RCS_DIGITS_LINE_INFO:
            return RIL_UNSOL_RCS_DIGITS_LINE_INFO; // RCS Over Interenet PDN
        case RFX_MSG_UNSOL_ENTER_SCBM:
            return RIL_UNSOL_ENTER_SCBM;
        case RFX_MSG_UNSOL_EXIT_SCBM:
            return RIL_UNSOL_EXIT_SCBM;
        case RFX_MSG_UNSOL_RSU_EVENT:
            return RIL_UNSOL_RSU_EVENT;
        default:
            return INVALID_ID;
    }
}

extern "C" int getOpMsgIdFromRequestId(int requestId) {
    switch(requestId) {
        // RIL Request
        case RIL_REQUEST_SET_INCOMING_VIRTUAL_LINE:
            return RFX_MSG_REQUEST_SET_INCOMING_VIRTUAL_LINE;
        case RIL_REQUEST_DIAL_FROM:
            return RFX_MSG_REQUEST_DIAL_FROM;
        case RIL_REQUEST_SEND_USSI_FROM:
            return RFX_MSG_REQUEST_SEND_USSI_FROM;
        case RIL_REQUEST_CANCEL_USSI_FROM:
            return RFX_MSG_REQUEST_CANCEL_USSI_FROM;
        case RIL_REQUEST_SET_EMERGENCY_CALL_CONFIG:
            return RFX_MSG_REQUEST_SET_EMERGENCY_CALL_CONFIG;
        case RIL_REQUEST_DEVICE_SWITCH:
            return RFX_MSG_REQUEST_DEVICE_SWITCH;
        case RIL_REQUEST_CANCEL_DEVICE_SWITCH:
            return RFX_MSG_REQUEST_CANCEL_DEVICE_SWITCH;
        case RIL_REQUEST_EXIT_SCBM:
            return RFX_MSG_REQUEST_EXIT_SCBM;
        case RIL_REQUEST_SEND_RSU_REQUEST:
            return RFX_MSG_REQUEST_SEND_RSU_REQUEST;
        case RIL_REQUEST_SWITCH_RCS_ROI_STATUS:
            return RFX_MSG_REQUEST_SWITCH_RCS_ROI_STATUS;
        case RIL_REQUEST_UPDATE_RCS_CAPABILITIES:
            return RFX_MSG_REQUEST_UPDATE_RCS_CAPABILITIES;
        case RIL_REQUEST_UPDATE_RCS_SESSION_INFO:
            return RFX_MSG_REQUEST_UPDATE_RCS_SESSION_INFO;

        // RIL Unsol Request
        case RIL_UNSOL_RCS_DIGITS_LINE_INFO:
            return RFX_MSG_UNSOL_RCS_DIGITS_LINE_INFO;
        case RIL_UNSOL_ENTER_SCBM:
            return RFX_MSG_UNSOL_ENTER_SCBM;
        case RIL_UNSOL_EXIT_SCBM:
            return RFX_MSG_UNSOL_EXIT_SCBM;
        case RIL_UNSOL_RSU_EVENT:
            return RFX_MSG_UNSOL_RSU_EVENT;
        default:
            return INVALID_ID;
    }
}
}
