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
 * Hands-free profile Handsfree Unit support for watch application
 */

#ifndef __HCI_CONTROL_HFP_HF_H_
#define __HCI_CONTROL_HFP_HF_H_

#include "bt_types.h"
#include "wiced_bt_hfp_hf_int.h"

#ifndef BTM_SCO_PKT_TYPES_MASK_HV1
#define BTM_INVALID_SCO_INDEX           0xFFFF
#define BTM_SCO_LINK_ALL_PKT_MASK       0x003F
#define BTM_SCO_LINK_ONLY_MASK          0x0007
#define BTM_SCO_PKT_TYPES_MASK_HV3      0x0004
#define BTM_SCO_PKT_TYPES_MASK_EV3      0x0008
#define BTM_SCO_PKT_TYPES_MASK_EV4      0x0010
#define BTM_SCO_PKT_TYPES_MASK_EV5      0x0020
#define BTM_SCO_PKT_TYPES_MASK_NO_2_EV3 0x0040
#define BTM_SCO_PKT_TYPES_MASK_NO_3_EV3 0x0080
#define BTM_SCO_PKT_TYPES_MASK_NO_2_EV5 0x0100
#define BTM_SCO_PKT_TYPES_MASK_NO_3_EV5 0x0200
#define BTM_ESCO_RETRANS_POWER          2       // For S4 and T2 Retransmission_Effort=2
#define BTM_ESCO_RETRANS_QUALITY        2
#endif

// SDP Record for Hands-Free Unit
//#define HDLR_HANDS_FREE_UNIT                    0x10001
//#define HDLR_HEADSET_UNIT                       0x10002
#define HANDS_FREE_SCN                  0x01
//#define HEADSET_SCN                             0x02
//#define HANDS_FREE_DEVICE_NAME                  "free-hands"
//#define BT_AUDIO_HFP_VOLUME_MIN                 1
//#define BT_AUDIO_HFP_VOLUME_MAX                 15
//#define TRANS_UART_BUFFER_SIZE                  1024
#define BT_AUDIO_INVALID_SCO_INDEX      0xFFFF
//#define HANDSFREE_NVRAM_ID                      0x46
#define HANDS_FREE_SCO_PKT_TYPES        ( BTM_SCO_PKT_TYPES_MASK_HV3 | \
                                          BTM_SCO_PKT_TYPES_MASK_EV3 | \
                                          BTM_SCO_PKT_TYPES_MASK_EV4 | \
                                          BTM_SCO_PKT_TYPES_MASK_EV5 | \
                                          BTM_SCO_PKT_TYPES_MASK_NO_3_EV3 | \
                                          BTM_SCO_PKT_TYPES_MASK_NO_3_EV5 )

#define SCO_CONNECTION_WAIT_TIMEOUT     1000    // If AG won't trigger sco connection in 1000msec of time, we will initiate SCO connection.

#if (WICED_BT_HFP_HF_WBS_INCLUDED == TRUE)
#define SUPPORTED_FEATURES_ATT          ( WICED_BT_HFP_HF_SDP_FEATURE_ECNR | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_3WAY_CALLING | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_CLIP | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_VRECG | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_REMOTE_VOL_CTRL | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_WIDEBAND_SPEECH )

#define BT_AUDIO_HFP_SUPPORTED_FEATURES ( WICED_BT_HFP_HF_FEATURE_3WAY_CALLING | \
                                          WICED_BT_HFP_HF_FEATURE_CLIP_CAPABILITY | \
                                          WICED_BT_HFP_HF_FEATURE_VOICE_RECOGNITION_ACTIVATION | \
                                          WICED_BT_HFP_HF_FEATURE_REMOTE_VOLUME_CONTROL| \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_CALL_STATUS | \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_CALL_CONTROL | \
                                          WICED_BT_HFP_HF_FEATURE_CODEC_NEGOTIATION | \
                                          WICED_BT_HFP_HF_FEATURE_HF_INDICATORS | \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_VOICE_RECOGNITION)
#else
#define SUPPORTED_FEATURES_ATT          ( WICED_BT_HFP_HF_SDP_FEATURE_ECNR | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_3WAY_CALLING | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_CLIP | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_VRECG | \
                                          WICED_BT_HFP_HF_SDP_FEATURE_REMOTE_VOL_CTRL )

#define BT_AUDIO_HFP_SUPPORTED_FEATURES ( WICED_BT_HFP_HF_FEATURE_3WAY_CALLING | \
                                          WICED_BT_HFP_HF_FEATURE_CLIP_CAPABILITY | \
                                          WICED_BT_HFP_HF_FEATURE_VOICE_RECOGNITION_ACTIVATION | \
                                          WICED_BT_HFP_HF_FEATURE_REMOTE_VOLUME_CONTROL| \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_CALL_STATUS | \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_CALL_CONTROL | \
                                          WICED_BT_HFP_HF_FEATURE_HF_INDICATORS | \
                                          WICED_BT_HFP_HF_FEATURE_ENHANCED_VOICE_RECOGNITION)
#endif

/** HF device indicators. */
typedef enum
{
    WICED_BT_HFP_HF_SERVICE_IND     =   1,
    WICED_BT_HFP_HF_CALL_IND        =   2,
    WICED_BT_HFP_HF_CALL_SETUP_IND  =   3,
    WICED_BT_HFP_HF_CALL_HELD_IND   =   4,
    WICED_BT_HFP_HF_SIGNAL_IND      =   5,
    WICED_BT_HFP_HF_ROAM_IND        =   6,
    WICED_BT_HFP_HF_BATTERY_IND     =   7
} wiced_bt_hfp_hf_indicator_t;

/* data associated with HF_OPEN_EVT */
typedef struct
{
    BD_ADDR             bd_addr;
    uint8_t             status;
} hci_control_hfp_hf_open_t;

/* data associated with AT command response event */
typedef struct
{
    uint16_t            num;
    char                str[WICED_BT_HFP_HF_MAX_AT_CMD_LEN];
} hci_control_hfp_hf_value_t;

/* data associated with HF_CONNECTED_EVT */
typedef struct
{
    uint32_t           peer_features;
    uint8_t            profile_selected;
} hci_control_hfp_hf_connect_t;

/* union of data associated with HS callback */
typedef union
{
    hci_control_hfp_hf_open_t    open;
    hci_control_hfp_hf_connect_t conn;
    hci_control_hfp_hf_value_t   val;
} hci_control_hfp_hf_event_t;

typedef struct
{
    uint8_t pairing_allowed;
    hci_control_hfp_hf_connect_t connect;
    wiced_timer_t hfp_timer; 
    wiced_timer_t retry_conn_timer; 
    uint8_t       may_retry_conn;
    wiced_bt_device_address_t retry_bdaddr;
} hci_control_hfp_hf_app_cb;

typedef struct
{
    wiced_bt_device_address_t               peer_bd_addr;
    wiced_bt_hfp_hf_connection_state_t      connection_status;
    int                                     call_active;
    int                                     call_held;
    wiced_bt_hfp_hf_callsetup_state_t       call_setup;
    wiced_bt_hfp_hf_inband_ring_state_t     inband_ring_status;
    uint8_t                                 mic_volume;
    uint8_t                                 spkr_volume;
    uint16_t                                sco_index;
    uint16_t                                rfcomm_handle;
    wiced_bool_t                            init_sco_conn;
    wiced_bool_t                            is_sco_connected;
} bluetooth_hfp_context_t;

/*
 * Handsfree Unit init
 */
void hci_control_hf_init(void);

/*
 * Handle Handsfree commands received over UART.
 */
void hci_control_hf_handle_command(uint16_t opcode, uint8_t* p_data, uint32_t length);

/*
 * Process SCO management callback
 */
void hci_control_hf_sco_management_callback( wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data );

#endif /* __HCI_CONTROL_HFP_HF_H_ */
