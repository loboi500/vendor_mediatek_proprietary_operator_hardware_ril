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
#include "RfxOpControllerFactory.h"
#include "RfxController.h"
#include "RfxRootController.h"
#include "RfxSlotRootController.h"

#include "RfxRilAdapter.h"
#include "RfxLog.h"

/*****************************************************************************
 * Define
 *****************************************************************************/
#define RFX_LOG_TAG "RfxOpContFac"

#define RFX_CONTROLLER_CREATION_ENTRY(_className) \
        {_className::createInstance, _className::getClassInfoInstance, false}

/*****************************************************************************
 * Class RfxOpControllerFactory
 *****************************************************************************/
extern const rfx_ctrler_factory_init s_pre_non_slot_op_controllers[];
extern const rfx_ctrler_factory_init s_slot_op_controllers[];
extern const rfx_ctrler_factory_init s_non_slot_op_controllers[];

extern const int s_num_pre_non_slot_controller;
extern const int s_num_slot_controller;
extern const int s_num_non_slot_controller;

extern "C" const rfx_ctrler_factory_init* getPreNonSlotOpCtlerList() {
    RFX_LOG_D(RFX_LOG_TAG, "getPreNonSlotOpCtlerList");
    return &s_pre_non_slot_op_controllers[0];
}

extern "C" const rfx_ctrler_factory_init* getSlotOpCtlerList() {
    RFX_LOG_D(RFX_LOG_TAG, "getSlotOpCtlerList");
    return &s_slot_op_controllers[0];
}

extern "C" const rfx_ctrler_factory_init* getNonSlotOpCtlerList() {
    RFX_LOG_D(RFX_LOG_TAG, "getNonSlotOpCtlerList");
    return &s_non_slot_op_controllers[0];
}

extern "C" int getNumOfPreNonSlotOpCtler() {
    RFX_LOG_D(RFX_LOG_TAG, "getNumOfPreNonSlotOpCtler num:%d", s_num_pre_non_slot_controller);
    return s_num_pre_non_slot_controller;
}

extern "C" int getNumOfSlotOpCtler() {
    RFX_LOG_D(RFX_LOG_TAG, "getNumOfSlotOpCtler num:%d", s_num_slot_controller);
    return s_num_slot_controller;
}

extern "C" int getNumOfNonSlotOpCtler() {
    RFX_LOG_D(RFX_LOG_TAG, "getNumOfNonSlotOpCtler num:%d", s_num_non_slot_controller);
    return s_num_non_slot_controller;
}
