/*******************************************************************************
* (c) 2021-2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

/** @file
 *
 * A2DP support for HCI AV Source application
 */
#pragma once

#include "bt_types.h"
#include "wiced_bt_sdp.h"
#include "wiced_bt_avdt.h"
#include <wiced_bt_audio.h>

#define CASE_RETURN_STR(const) case const: return #const;

/* Whether to use sine wave for audio output */
#define HCI_CONTROL_AUDIO_ROUTE_SINWAVE

/*A2DP Sampling Frequencies */
#define AUDIO_SF_16K                0x00
#define AUDIO_SF_32K                0x01
#define AUDIO_SF_44_1K              0x02
#define AUDIO_SF_48K                0x03

/* Channel Configurations */
#define AUDIO_CHCFG_MONO            0x00
#define AUDIO_CHCFG_STEREO          0x01

/* Audio File Format */
#define AUDIO_SRC_AUDIO_DATA_FORMAT_PCM 0
#define AUDIO_SRC_AUDIO_DATA_FORMAT_MP3 1

/* Support features */
#define AUDIO_SRC_FEATURE_I2S_INPUT (1 << 0)
#define AUDIO_SRC_FEATURE_MP3_FORMAT (1 << 1)

#define AV_RET_TOUT                 4
#define AV_SIG_TOUT                 4
#define AV_IDLE_TOUT                10
#define AV_SEC_MASK                 BTM_SEC_NONE

/* offset of media type in codec info byte array */
#define AV_MEDIA_TYPE_IDX           1

#define  AV_NUM_SEPS                7

typedef enum
{
    AV_STATE_IDLE,              /* Initial state (channel is unused) */
    AV_STATE_SDP_IN_PROGRESS,   /* SDP in Progress */
    AV_STATE_SDP_DONE,          /* SDP Complete */
    AV_STATE_CONNECTING,        /* Connecting */
    AV_STATE_CONNECTED,         /* Signaling Channel is connected and active */
    AV_STATE_CONFIGURE,         /* Remote has sent configuration request */
    AV_STATE_OPEN,              /* Data channel connected but not streaming */
    AV_STATE_STARTING,          /* Attempting Data streaming */
    AV_STATE_STARTED,           /* Data streaming */
    AV_STATE_RECONFIG,          /* Reconfiguring stream */
    AV_STATE_DISCONNECTING      /* Disconnecting */
} AV_STATE;

typedef enum
{
    AV_STREAM_STATE_STOPPED,
    AV_STREAM_STATE_STARTING,
    AV_STREAM_STATE_STARTED,
    AV_STREAM_STATE_STOPPING
} AV_STREAM_STATE;

#define AUDIO_IDLE_SUSPEND_TIMEOUT_IN_SECONDS 3

/* Entry in peer_cb table reserved for acceptor connection */
#define AV_IDX_ACP              0

/*  BIT pool calculation
    ********************
    bit_rate = 8*frame_length*fs(in kHz)/nrof_subbands/nrof_blocks,

    where,
    frame_length = 4+(4*nrof_subbands*nrof_channels)/8
                    +[nrof_blocks*nrof_channels*bitpool/8]
    for the MONO and DUAL_CHANNEL channel modes
    frame_length = 4+(4*nrof_subbands*nrof_channels)/8
                   +[(join*nrof_subbands + nrof_blocks*nrof_channels*bitpool)/8]
    for the STEREO a and JOIN_STEREO channel modes
    join = 1 when join stereo is used else 0

    for fs = 16kHz, nrof_subbands = 8, nrof_blocks = 16, nrof_channels = 1
    and channel mode = MONO
    => bit_rate = frame_length.
    => frame_length = 8+2*bitpool.
    Therefore, bitpool = (bit_rate-8)/2
    For bit_rate of 128kbps, bitpool = 60

    reference : A2DP spec v12
*/

void hci_control_audio_init(void);

uint8_t hci_control_audio_handle_command(uint16_t cmd_opcode, uint8_t* p_data, uint32_t len);

void av_app_init(void);

wiced_result_t av_app_deinit(void);

void hci_control_audio_support_features_send(void);

wiced_bool_t hci_control_audio_is_connected(void);

void a2dp_app_hci_control_audio_stop(void);
