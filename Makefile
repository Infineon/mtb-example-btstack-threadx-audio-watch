################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Top-level application make file.
#
################################################################################
# \copyright
# Copyright 2018-2024, Cypress Semiconductor Corporation (an Infineon company)
# SPDX-License-Identifier: Apache-2.0
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################


################################################################################
# Basic Configuration
################################################################################

# Type of ModusToolbox Makefile Options include:
#
# COMBINED    -- Top Level Makefile usually for single standalone application
# APPLICATION -- Top Level Makefile usually for multi project application
# PROJECT     -- Project Makefile under Application
#
MTB_TYPE=COMBINED

# Target board/hardware (BSP).
# To change the target, it is recommended to use the Library manager
# ('make library-manager' from command line), which will also update Eclipse IDE launch
# configurations.
TARGET=CYW955513EVK-01

# Name of application (used to derive name of final linked file).
#
# If APPNAME is edited, ensure to update or regenerate launch
# configurations for your IDE.
APPNAME=mtb-example-btstack-threadx-audio-watch

# Name of toolchain to use. Options include:
#
# GCC_ARM -- GCC provided with ModusToolbox software
# ARM     -- ARM Compiler (must be installed separately)
# IAR     -- IAR Compiler (must be installed separately)
#
# See also: CY_COMPILER_PATH below
TOOLCHAIN=GCC_ARM

# Default build configuration. Options include:
#
# Debug -- build with minimal optimizations, focus on debugging.
# Release -- build with full optimizations
# Custom -- build with custom configuration, set the optimization flag in CFLAGS
#
# If CONFIG is manually edited, ensure to update or regenerate launch configurations
# for your IDE.
CONFIG=Debug

# If set to "true" or "1", display full command-lines when building.
VERBOSE=


################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS=a2dp_sink_profile_btstack  audio_sink_route_config_lib btsdk-include btstack_v3  audiomanager cyw9bt_audio5

# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS=

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.
SOURCES=

# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).
INCLUDES=

# Add additional defines to the build process (without a leading -D).
DEFINES=

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT=

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS=-Wno-unused-function -Wno-unused-variable -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS=

# Additional / custom linker flags.
LDFLAGS=

# Additional / custom libraries to link in to the application.
LDLIBS=

# Path to the linker script to use (if empty, use the default linker script).
LINKER_SCRIPT=

# Custom pre-build commands to run.
PREBUILD=

# Custom post-build commands to run.
POSTBUILD=


################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the shared repo location.
#
# All .mtb files have the format, <URI>#<COMMIT>#<LOCATION>. If the <LOCATION> field
# begins with $$ASSET_REPO$$, then the repo is deposited in the path specified by
# the CY_GETLIBS_SHARED_PATH variable. The default location is one directory level
# above the current app directory.
# This is used with CY_GETLIBS_SHARED_NAME variable, which specifies the directory name.
CY_GETLIBS_SHARED_PATH=../

# Directory name of the shared repo location.
#
CY_GETLIBS_SHARED_NAME=mtb_shared

# Absolute path to the compiler's "bin" directory. The variable name depends on the
# toolchain used for the build. Refer to the ModusToolbox user guide to get the correct
# variable name for the toolchain used in your build.
#
# The default depends on the selected TOOLCHAIN (GCC_ARM uses the ModusToolbox
# software provided compiler by default).
CY_COMPILER_GCC_ARM_DIR=


#
# App features/defaults
#
#BT_DEVICE_ADDRESS?=55500A100002
UART?=AUTO
TRANSPORT?=UART
A2DP_SRC_INCLUDED := 1
AVRCP_TG_INCLUDED := 1
AVRCP_CT_INCLUDED := 1
HFP_AG_INCLUDED ?= 0
HFP_HF_INCLUDED ?= 1
HCI_TEST_INCLUDED := 1
LE_INCLUDED := 1
ANCS_INCLUDED ?= 1
AMS_INCLUDED ?= 1
PANU_SUPPORT=0
PANNAP_SUPPORT=0
PAN_PTS_SUPPORT=0

# PAN only supported on CYW920721M2EVK-01 currently
ifeq (1,$(filter 1,$(PANU_SUPPORT) $(PANNAP_SUPPORT) $(PAN_PTS_SUPPORT)))
ifneq ($(TARGET),CYW920721M2EVK-01)
$(error PANU_INCLUDED PANNAP_INCLUDED and PAN_PTS_SUPPORT only supported on CYW920721M2EVK-01 TARGET)
endif
endif

ifeq ($(PAN_PTS_SUPPORT), 1)
PAN_PTS_INCLUDED := 1
endif
ifeq ($(PANU_SUPPORT), 1)
PANU_INCLUDED := 1
endif
ifeq ($(PANNAP_SUPPORT), 1)
PANNAP_INCLUDED := 1
endif
ifeq ($(PANU_INCLUDED), 1)
ifeq ($(PANNAP_INCLUDED), 1)
$(error PANU_INCLUDED PANNAP_INCLUDED can't enable at the same time)
endif
endif

# Additional application c compiler flags
AMA_INCLUDED := 0
MP3_DECODER_INCLUDED ?= 0
ENABLE_DEBUG?=0
CYHAL_SLEEP_SUPPORT?=0
SLEEP_SUPPORT ?= 0
COEX_SUPPORT ?= 0
AUTO_ELNA_SWITCH ?= 0
AUTO_EPA_SWITCH ?= 0


-include internal.mk

ifeq ($(PAN_PTS_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_PAN_PTS_INCLUDED
endif
ifeq ($(PANU_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_PANU_INCLUDED
endif
ifeq ($(PANNAP_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_PANNAP_INCLUDED
endif

# wait for SWD attach
ifeq ($(ENABLE_DEBUG),1)
CY_APP_DEFINES+=-DENABLE_DEBUG=1
endif


# For devices that are memory constrained and can process CY_DISABLE_TRACE_PATH
# in the device CSP library in make/recipe/defines.mk:
# list paths with source files we would like to build without WICED_BT_TRACE_ENABLE.
CY_DISABLE_TRACE_PATH =$(SEARCH_btsdk-audio)
CY_DISABLE_TRACE_PATH+=$(SEARCH_btsdk-ota)
CY_DISABLE_TRACE_PATH+=$(SEARCH_btsdk-pan)
CY_DISABLE_TRACE_PATH+=$(SEARCH_btsdk-common)
CY_DISABLE_TRACE_PATH+=$(SEARCH_43012C0)

CY_APP_DEFINES += -DAPP_CFG_ENABLE_BR_AUDIO=1
CY_APP_DEFINES += -DWICED_BT_TRACE_ENABLE
CY_APP_DEFINES += -DWICED_HCI_TRANSPORT_SPI=2
CY_APP_DEFINES += -DWICED_HCI_TRANSPORT_UART=1
CY_APP_DEFINES += -DSLEEP_SUPPORTED=$(SLEEP_SUPPORT)
CY_APP_DEFINES += -DCOEX_SUPPORTED=$(COEX_SUPPORT)
#CY_APP_DEFINES += -DPTS_TEST_ONLY
ifeq ($(TRANSPORT),SPI)
#$(info Transport=SPI)
ifeq ($(TARGET),$(filter $(TARGET), CYW920719B2Q40EVB-01))
CY_APP_DEFINES += -DWICED_HCI_TRANSPORT=2
else
$(error invalid TARGET for SPI transport, supported only for CYW920719B2Q40EVB-01)
endif
else
#$(info Transport=UART)
CY_APP_DEFINES += -DWICED_HCI_TRANSPORT=1
endif # TRANSPORT

ifeq ($(A2DP_SRC_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_AUDIO_SRC_INCLUDED
endif

ifeq ($(AVRCP_TG_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_AUDIO_RC_TG_INCLUDED
CY_APP_DEFINES += -DCATEGORY_2_PASSTROUGH
endif

ifeq ($(AVRCP_CT_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_AUDIO_RC_CT_INCLUDED
CY_APP_DEFINES += -DMAX_CONNECTED_RCC_DEVICES=1
endif

ifeq ($(HFP_AG_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_HFP_AG_INCLUDED
endif

ifeq ($(HFP_HF_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_HFP_HF_INCLUDED
endif

ifeq ($(LE_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_LE_INCLUDED
CY_APP_DEFINES += -DWICED_APP_LE_PERIPHERAL_CLIENT_INCLUDED
endif

ifeq ($(ANCS_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_ANCS_INCLUDED
endif

ifeq ($(AMS_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_AMS_INCLUDED
endif

ifeq ($(AMA_INCLUDED), 1)
CY_APP_DEFINES += -DAMA_ENABLED
CY_APP_DEFINES += -DAMA_SPEECH_AUDIO_FORMAT_OPUS_BITRATE=0
CY_APP_DEFINES += -DAMA_VOICE_BUFFER_LENGTH_IN_MS=500
ifeq ($(HFP_HF_INCLUDED), 1)
CY_APP_DEFINES += -DAMA_HANDSFREE_INCLUDED
endif
endif

ifeq ($(HCI_TEST_INCLUDED), 1)
CY_APP_DEFINES += -DWICED_APP_TEST_INCLUDED
endif

ifeq ($(AUTO_ELNA_SWITCH),1)
CY_APP_DEFINES += -DAUTO_ELNA_SWITCH
endif

ifeq ($(AUTO_EPA_SWITCH),1)
CY_APP_DEFINES += -DAUTO_EPA_SWITCH
endif

#
# Patch Library for different target
#
ifeq ($(AVRCP_TG_INCLUDED), 1)
COMPONENTS += avrc_target
endif

ifeq ($(AVRCP_CT_INCLUDED), 1)
COMPONENTS += avrc_controller
endif

ifeq ($(HFP_AG_INCLUDED), 1)
COMPONENTS += hfp_audio_gateway
endif

ifeq ($(HFP_HF_INCLUDED), 1)
COMPONENTS += handsfree_profile
endif

ifeq ($(AMS_INCLUDED), 1)
COMPONENTS += ams
endif

ifeq ($(ANCS_INCLUDED), 1)
COMPONENTS += ancs
endif

ifeq ($(AMA_INCLUDED), 1)
COMPONENTS += ama
COMPONENTS += audio_record_lib
COMPONENTS += nanopbuf
endif

ifneq ($(filter 1, $(PANU_INCLUDED) $(PANNAP_INCLUDED)), )
COMPONENTS += pan_lib
endif

#
# Target Configuration
#
ifeq ($(TARGET),CYW955572BTEVK-01)
# Apply new Audio Profiles
ifeq ($(AVRCP_CT_INCLUDED), 1)
DISABLE_COMPONENTS += avrc_controller
COMPONENTS += avrc_controller_btstack
endif

ifeq ($(AVRCP_TG_INCLUDED), 1)
DISABLE_COMPONENTS += avrc_target
COMPONENTS += avrc_target_btstack
endif

ifeq ($(HFP_HF_INCLUDED), 1)
DISABLE_COMPONENTS += handsfree_profile
COMPONENTS += handsfree_profile_btstack
CY_APP_DEFINES += -DWICED_BT_HFP_HF_WBS_INCLUDED=TRUE
endif
endif # TARGET

ifeq ($(TARGET), $(filter %CYW955513EVK-01, $(TARGET)))
CY_APP_DEFINES += -DAPP_CFG_DYNMEM_SIZE_4=572
CY_APP_DEFINES += -DCYW9BT_AUDIO
CY_APP_DEFINES += -DNO_PUART_SUPPORT
CY_APP_DEFINES += -DHCI_TRACE_OVER_TRANSPORT
CY_APP_DEFINES += -DENABLE_BLUETOOTH_HCI_TRACE
# Apply new Audio Profiles
ifeq ($(AVRCP_CT_INCLUDED), 1)
DISABLE_COMPONENTS += avrc_controller
COMPONENTS += avrc_controller_btstack
endif

ifeq ($(AVRCP_TG_INCLUDED), 1)
DISABLE_COMPONENTS += avrc_target
DISABLE_COMPONENTS += avrc_controller
COMPONENTS += avrc_controller_btstack
COMPONENTS += avrc_target_btstack
endif

ifeq ($(HFP_HF_INCLUDED), 1)
DISABLE_COMPONENTS += handsfree_profile
COMPONENTS += handsfree_profile_btstack
CY_APP_DEFINES += -DWICED_BT_HFP_HF_WBS_INCLUDED=TRUE
SUPPORT_MXTDM = 1
endif

ifeq ($(HFP_AG_INCLUDED), 1)
DISABLE_COMPONENTS += hfp_audio_gateway
COMPONENTS += hfp_audio_gateway_btstack
endif

ifeq ($(SUPPORT_MXTDM), 1)
CY_APP_DEFINES+=-DSUPPORT_MXTDM
endif

ifeq ($(CYHAL_SLEEP_SUPPORT), 1)
CY_APP_DEFINES += -DCYHAL_SYSPM_WITH_TRANSPORT_MODE
CY_APP_DEFINES += -DCYHAL_SLEEP_SUPPORTED=$(CYHAL_SLEEP_SUPPORT)
endif
endif # TARGET


# Locate ModusToolbox helper tools folders in default installation
# locations for Windows, Linux, and macOS.
CY_WIN_HOME=$(subst \,/,$(USERPROFILE))
CY_TOOLS_PATHS ?= $(wildcard \
    $(CY_WIN_HOME)/ModusToolbox/tools_* \
    $(HOME)/ModusToolbox/tools_* \
    /Applications/ModusToolbox/tools_*)

# If you install ModusToolbox software in a custom location, add the path to its
# "tools_X.Y" folder (where X and Y are the version number of the tools
# folder). Make sure you use forward slashes.
CY_TOOLS_PATHS+=

# Default to the newest installed tools folder, or the users override (if it's
# found).
CY_TOOLS_DIR=$(lastword $(sort $(wildcard $(CY_TOOLS_PATHS))))

ifeq ($(CY_TOOLS_DIR),)
$(error Unable to find any of the available CY_TOOLS_PATHS -- $(CY_TOOLS_PATHS). On Windows, use forward slashes.)
endif

# tools that can be launched with "make open CY_OPEN_TYPE=<tool>
CY_BT_APP_TOOLS=BTSpy ClientControl

$(info Tools Directory: $(CY_TOOLS_DIR))

include $(CY_TOOLS_DIR)/make/start.mk
