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

#ifndef RILOP_SERVICE_H
#define RILOP_SERVICE_H

#include <telephony/mtk_ril.h>
#include <telephony/mtk_rilop.h>
#include <rilop_internal.h>
#include <ril_internal.h>

namespace radio {

extern "C" void registerOpService(RIL_RadioFunctions *callbacks, android::CommandInfo *commands);
/*********************************************************************************/
/*  Vendor request                                                               */
/*********************************************************************************/
int setIncomingVirtualLineResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e,
                   void *response, size_t responselen);

int setRxTestConfigResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int getRxTestResultResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int dialFromResponse(unsigned int slotId, android::ClientId clientId,
                int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int sendUssiFromResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int cancelUssiFromResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int setEmergencyCallConfigResponse(unsigned int slotId, android::ClientId clientId,
                        int responseType, int serial, RIL_Errno e,
                        void *response, size_t responselen);

int setDisable2GResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int getDisable2GResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int sendRsuRequestResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response,
                   size_t responselen);

int deviceSwitchResponse(unsigned int slotId, android::ClientId clientId,
                 int responseType, int serial, RIL_Errno e,
                 void *response, size_t responselen);

int cancelDeviceSwitchResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e,
                       void *response, size_t responselen);

int switchRcsRoiStatusResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e,
                   void *response, size_t responselen);
int updateRcsCapabilitiesResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e,
                   void *response, size_t responselen);
int updateRcsSessionInfoResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e,
                   void *response, size_t responselen);

int exitSCBMResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e,
                   void *response, size_t responselen);

/*********************************************************************************/
/*  Vendor unsol                                                                 */
/*********************************************************************************/
// MTK-START: SIM TMO RSU
int onSimMeLockEvent(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);
// MTK-END
int onRsuEvent(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responselen);

int responseModulationInfoInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);

int enterSCBMInd(unsigned int slotId, int indicationType, int token,
                 RIL_Errno e, void *response, size_t responselen);

int exitSCBMInd(unsigned int slotId, int indicationType, int token,
                RIL_Errno e, void *response, size_t responselen);
}
#endif  // RILOP_SERVICE_H
