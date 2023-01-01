#Copyright 2006 The Android Open Source Project

ifeq ($(MTK_RIL_MODE), c6m_1rild)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

RIL_LOCAL_SRC_FILES:= \
    libril/rilop_service.cpp \
    libril/rilop.cpp \
    mtk-ril/framework/core/RfxOpControllerFactory.cpp \
    mtk-ril/telcore/oem/RtcOpOemController.cpp \
    mtk-ril/mdcomm/power/RmcOpRadioRequestHandler.cpp \
    mtk-ril/telcore/client/RilOpOemClient.cpp \
    mtk-ril/telcore/client/RtcOpRilClientController.cpp \
    mtk-ril/telcore/data/RtcOpDataController.cpp \
    mtk-ril/telcore/sim/RtcCommSimOpController.cpp \
    mtk-ril/mdcomm/sim/RmcGsmSimOpRequestHandler.cpp \
    mtk-ril/mdcomm/sim/RmcCdmaSimOpRequestHandler.cpp \
    mtk-ril/mdcomm/sim/RmcCommSimOpRequestHandler.cpp \
    mtk-ril/mdcomm/sim/RmcGsmSimOpUrcHandler.cpp \
    mtk-ril/mdcomm/sim/RmcCdmaSimOpUrcHandler.cpp \
    mtk-ril/mdcomm/sim/RmcCommSimOpUrcHandler.cpp \
    mtk-ril/telcore/ims/RtcOpImsController.cpp \
    mtk-ril/mdcomm/ims/RmcOpImsControlRequestHandler.cpp \
    mtk-ril/mdcomm/ims/RmcOpImsControlUrcHandler.cpp \
    mtk-ril/telcore/cc/RtcOpCallController.cpp \
    mtk-ril/mdcomm/cc/RmcOpCallControlImsRequestHandler.cpp \
    mtk-ril/framework/base/RfxDialFromData.cpp \
    mtk-ril/framework/base/RfxOpRsuRequestData.cpp \
    mtk-ril/framework/base/RfxOpRsuResponseData.cpp \
    mtk-ril/telcore/ss/RtcOpSuppServController.cpp \
    mtk-ril/mdcomm/ss/RmcOpSuppServRequestHandler.cpp \
    mtk-ril/mdcomm/data/RmcOpDcImsReqHandler.cpp \
    mtk-ril/telcore/sms/RtcOpSCBMController.cpp \
    mtk-ril/mdcomm/sms/RmcOpSCBMUrcHandler.cpp\
    mtk-ril/mdcomm/sms/RmcOpSCBMRequestHandler.cpp\
    mtk-ril/telcore/capabilityswitch/RtcOpCapabilitySwitchChecker.cpp \
    mtk-ril/telcore/utils/RfxControllerUtils.cpp \
    mtk-ril/telcore/utils/RfxHandlerUtils.cpp \

RIL_MIPC_LOCAL_SRC_FILES:= \
    libril/rilop_service.cpp \
    libril/rilop.cpp \
    mtk-ril/framework/core/RfxOpControllerFactory.cpp \
    mtk-ril/framework/base/RfxDialFromData.cpp \
    mtk-ril/framework/base/RfxOpRsuRequestData.cpp \
    mtk-ril/framework/base/RfxOpRsuResponseData.cpp \
    mtk-ril/telcore_mipc/oem/RtmOpOemController.cpp \
    mtk-ril/mdcomm_mipc/power/RmmOpRadioRequestHandler.cpp \
    mtk-ril/telcore_mipc/client/RilOpOemClient.cpp \
    mtk-ril/telcore_mipc/client/RtmOpRilClientController.cpp \
    mtk-ril/telcore_mipc/data/RtmOpDataController.cpp \
    mtk-ril/telcore_mipc/ims/RtmOpImsController.cpp \
    mtk-ril/mdcomm_mipc/ims/RmmOpImsControlRequestHandler.cpp \
    mtk-ril/mdcomm_mipc/ims/RmmOpImsControlUrcHandler.cpp \
    mtk-ril/telcore_mipc/ss/RtmOpSuppServController.cpp \
    mtk-ril/mdcomm_mipc/ss/RmmOpSuppServRequestHandler.cpp \
    mtk-ril/telcore_mipc/sms/RtmOpSCBMController.cpp \
    mtk-ril/mdcomm_mipc/sms/RmmOpSCBMUrcHandler.cpp\
    mtk-ril/mdcomm_mipc/sms/RmmOpSCBMRequestHandler.cpp\
    mtk-ril/telcore_mipc/capabilityswitch/RtmOpCapabilitySwitchChecker.cpp \
    mtk-ril/telcore_mipc/utils/RfxMipcOpControllerUtils.cpp \

RIL_LOCAL_SHARED_LIBRARIES := \
    libmtkrillog \
    libmtkutils \
    libmtkcutils \
    libmtkhardware_legacy \
    libmtkrilutils \
    librilfusion \
    libratconfig \
    libmipc \

#use android binder, HIDL
RIL_LOCAL_CFLAGS += -DMTK_USE_HIDL
RIL_LOCAL_SHARED_LIBRARIES += libhwbinder libhidlbase libhidltransport \
    android.hardware.radio@1.0 \
    vendor.mediatek.hardware.radio_op@3.0

RIL_LOCAL_STATIC_LIBRARIES := \
    libprotobuf-c-nano-enable_malloc \

#LOCAL_CFLAGS := -DANDROID_MULTI_SIM -DDSDA_RILD1
RIL_LOCAL_CFLAGS += -Wno-unused-parameter
#ifneq ($(MTK_NUM_MODEM_PROTOCOL),1)
    RIL_LOCAL_CFLAGS += -DANDROID_MULTI_SIM
#endif

ifeq ($(HAVE_AEE_FEATURE),yes)
    RIL_LOCAL_SHARED_LIBRARIES += libaedv
    RIL_LOCAL_CFLAGS += -DHAVE_AEE_FEATURE
endif

ifeq ($(MTK_TC1_FEATURE),yes)
    RIL_LOCAL_CFLAGS += -DMTK_TC1_FEATURE
endif

RIL_LOCAL_CFLAGS += -DMTK_OPERATOR_ADDON

RIL_LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/include/telephony \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/include/telephony \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/include/telephony \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/libril \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/framework/include \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/framework/include/core \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/framework/include/base \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/capabilityswitch \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/oem \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/sim \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm/sim \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/ims \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm/ims \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/cc \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm/cc \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/ss \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm/ss \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore/sms \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc/sms \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc/capabilityswitch \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc/oem \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm_mipc \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc/ims \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm_mipc/ims \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm_mipc/cc \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/telcore_mipc/ss \
        $(TOP)/$(MTK_PATH_SOURCE)/operator/hardware/ril/fusion/mtk-ril/mdcomm_mipc/ss \


RIL_LOCAL_HEADER_LIBRARIES := libWpfaHeaders netagent_headers ccci_headers libMtkLogHeaders \
    libUtilsHeaders mtk_ril_include_headers ims_headers libaed_headers libandroid_sensor_headers libcarrierconfig_includes libmipc_includes libmtkril_includes

RIL_LOCAL_CFLAGS += -DMTK_MUX_CHANNEL_64
RIL_LOCAL_CFLAGS += -DMTK_USE_HIDL
RIL_LOCAL_CFLAGS += -DMTK_IMS_CHANNEL_SUPPORT
RIL_LOCAL_CFLAGS += -DMTK_TELEPHONYWARE_SUPPORT
RIL_LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
RIL_LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/../include \
        $(LOCAL_PATH)/mtk-ril/framework/include/ \

LOCAL_SRC_FILES := $(RIL_LOCAL_SRC_FILES)
LOCAL_SHARED_LIBRARIES := $(RIL_LOCAL_SHARED_LIBRARIES)
LOCAL_SHARED_LIBRARIES += libmtk-ril
LOCAL_STATIC_LIBRARIES := $(RIL_LOCAL_STATIC_LIBRARIES)
LOCAL_CFLAGS:= $(RIL_LOCAL_CFLAGS)
LOCAL_C_INCLUDES := $(RIL_LOCAL_C_INCLUDES)
LOCAL_HEADER_LIBRARIES := $(RIL_LOCAL_HEADER_LIBRARIES) libnetagent_includes
LOCAL_EXPORT_C_INCLUDE_DIRS := $(RIL_LOCAL_STATIC_LIBRARIES)

LOCAL_MULTILIB := first
LOCAL_MODULE:= libmtk-rilop
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_CLANG := true
LOCAL_SANITIZE := integer
include $(MTK_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(RIL_MIPC_LOCAL_SRC_FILES)
LOCAL_SHARED_LIBRARIES := $(RIL_LOCAL_SHARED_LIBRARIES)
LOCAL_SHARED_LIBRARIES += libmtkmipc-ril
LOCAL_STATIC_LIBRARIES := $(RIL_LOCAL_STATIC_LIBRARIES)
LOCAL_CFLAGS:= $(RIL_LOCAL_CFLAGS)
LOCAL_C_INCLUDES := $(RIL_LOCAL_C_INCLUDES)
LOCAL_HEADER_LIBRARIES := $(RIL_LOCAL_HEADER_LIBRARIES) libmipcnetagent_includes
LOCAL_EXPORT_C_INCLUDE_DIRS := $(RIL_LOCAL_STATIC_LIBRARIES)

LOCAL_MULTILIB := first
LOCAL_MODULE:= libmtkmipc-rilop
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_CLANG := true
LOCAL_SANITIZE := integer
include $(MTK_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE:=libopril_includes
LOCAL_EXPORT_C_INCLUDE_DIRS := $(RIL_LOCAL_EXPORT_C_INCLUDE_DIRS)
include $(BUILD_HEADER_LIBRARY)

endif
