# The TARGET variable determines what target system the application is
# compiled for. It either refers to an XN file in the source directories
# or a valid argument for the --target option when compiling
TARGET = C22-ComECAT-IfmBLDC-XScope

# The APP_NAME variable determines the name of the final .xe file. It should
# not include the .xe postfix. If left blank the name will default to
# the project name
APP_NAME = app

# The USED_MODULES variable lists other module used by the application.
USED_MODULES = module_adc module_blocks module_common module_commutation module_ctrl_loops module_hall module_i2c_master module_mutual_thread_comm module_profile module_pwm_common module_pwm_symmetrical module_qei module_sm module_spi_master module_webserver module_wifi_tiwisl sc_sncn_ctrlproto/module_ctrlproto sc_sncn_ethercat/module_ethercat sc_somanet-base/module_nodeconfig

# The flags passed to xcc when building the application
# You can also set the following to override flags for a particular language:
# XCC_XC_FLAGS, XCC_C_FLAGS, XCC_ASM_FLAGS, XCC_CPP_FLAGS
# If the variable XCC_MAP_FLAGS is set it overrides the flags passed to
# xcc for the final link (mapping) stage.
XCC_FLAGS_Debug = -g -O0 -Wcodes -Xmapper -Wcodes -lxscope
XCC_FLAGS_Release = -g -O3 -Wcodes -Xmapper -Wcodes -lxscope

# The VERBOSE variable, if set to 1, enables verbose output from the make system.
VERBOSE = 0

WEBFS_TYPE = internal

WEBSERVER_USE_MODULE_WIFI = 1


#=============================================================================
# The following part of the Makefile includes the common build infrastructure
# for compiling XMOS applications. You should not need to edit below here.

XMOS_MAKE_PATH ?= ../..
ifneq ($(wildcard $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.common),)
include $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.common
else
include ../module_xcommon/build/Makefile.common
endif
