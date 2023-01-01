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
/*
 * File name:  rfxOpControllerFactory.cpp
 * Author: Weilun Liu(MTK02772)
 * Description:
 *  Implementation of OP controller factory.
 */

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RmcGsmSimOpRequestHandler.h"
#include "RmcCdmaSimOpRequestHandler.h"
#include "RmcCommSimOpRequestHandler.h"
#include "RmcGsmSimOpUrcHandler.h"
#include "RmcCdmaSimOpUrcHandler.h"
#include "RmcCommSimOpUrcHandler.h"
#include <mtk-ril/mdcomm/data/RmcOpDcImsReqHandler.h>
#include <RmcDcPdnManager.h>

/*****************************************************************************
 * Define
 *****************************************************************************/
#define RFX_LOG_TAG "RfxOpContFac"

/*****************************************************************************
 * Class RfxOpControllerFactory
 *****************************************************************************/

extern "C" RmcGsmSimOpRequestHandler *createGsmSimOpRequestHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createGsmSimOpRequestHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcGsmSimOpRequestHandler *mGsmOpReqHandler = NULL;
    RFX_HANDLER_CREATE(mGsmOpReqHandler, RmcGsmSimOpRequestHandler, (slot_Id, channel_Id));
    return mGsmOpReqHandler;
}

extern "C" RmcCdmaSimOpRequestHandler *createCdmaSimOpRequestHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createCdmaSimOpRequestHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcCdmaSimOpRequestHandler *mCdmaOpReqHandler = NULL;
    RFX_HANDLER_CREATE(mCdmaOpReqHandler, RmcCdmaSimOpRequestHandler, (slot_Id, channel_Id));
    return mCdmaOpReqHandler;
}

extern "C" RmcCommSimOpRequestHandler *createCommSimOpRequestHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createCommSimOpRequestHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcCommSimOpRequestHandler *mCommOpReqHandler = NULL;
    RFX_HANDLER_CREATE(mCommOpReqHandler, RmcCommSimOpRequestHandler, (slot_Id, channel_Id));
    return mCommOpReqHandler;
}

extern "C" RmcGsmSimOpUrcHandler *createGsmSimOpUrcHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createGsmSimOpUrcHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcGsmSimOpUrcHandler *mGsmOpUrcHandler = NULL;
    RFX_HANDLER_CREATE(mGsmOpUrcHandler, RmcGsmSimOpUrcHandler, (slot_Id, channel_Id));
    return mGsmOpUrcHandler;
}

extern "C" RmcCdmaSimOpUrcHandler *createCdmaSimOpUrcHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createCdmaSimOpUrcHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcCdmaSimOpUrcHandler *mCdmaOpUrcHandler = NULL;
    RFX_HANDLER_CREATE(mCdmaOpUrcHandler, RmcCdmaSimOpUrcHandler, (slot_Id, channel_Id));
    return mCdmaOpUrcHandler;
}

extern "C" RmcCommSimOpUrcHandler *createCommSimOpUrcHandler(int slot_Id, int channel_Id) {
    mtkLogD(LOG_TAG, "createCommSimOpUrcHandler: slot_Id %d, channel_Id %d", slot_Id, channel_Id);
    RmcCommSimOpUrcHandler *mCommOpUrcHandler = NULL;
    RFX_HANDLER_CREATE(mCommOpUrcHandler, RmcCommSimOpUrcHandler, (slot_Id, channel_Id));
    return mCommOpUrcHandler;
}

extern "C" RmcOpDcImsReqHandler *createDcImsOpReqHandler(int slot_Id, int channel_Id, void *pPdnManager) {
    mtkLogD(LOG_TAG, "%s: slot_Id %d, channel_Id %d", __FUNCTION__, slot_Id, channel_Id);
    RmcOpDcImsReqHandler *pDcImsOpReqHandler = NULL;
    RFX_HANDLER_CREATE(pDcImsOpReqHandler, RmcOpDcImsReqHandler, (slot_Id, channel_Id, (RmcDcPdnManager *) pPdnManager));
    return pDcImsOpReqHandler;
}
