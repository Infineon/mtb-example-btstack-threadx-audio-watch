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

#pragma once
#ifdef WICED_APP_AUDIO_RC_CT_INCLUDED

#include <stdint.h>
#include <wiced_result.h>
#include "wiced_timer.h"
#include "wiced_bt_avrc_ct.h"
#include "app.h"

#define MAX_POSSIBLE_APP_ATTR_VALUES    4
#define MAX_POSSIBLE_APP_ATTR_SETTINGS  4

typedef struct
{
    wiced_bool_t available;
    uint8_t      current_index;
    uint8_t      num_possible_values;
    uint8_t      possible_values[MAX_POSSIBLE_APP_ATTR_VALUES]; /* Values are all 1 based */
} tAVRC_APP_SETTING_ATTR;

typedef struct
{
    wiced_bt_device_address_t remote_addr;
    wiced_bt_avrc_ct_connection_state_t connection_state;

    uint8_t num_app_settings;
    uint8_t num_app_settings_init;
    tAVRC_APP_SETTING_ATTR app_setting[MAX_POSSIBLE_APP_ATTR_SETTINGS + 1];
    uint8_t handle;
    uint8_t may_retry_sdp;
    wiced_timer_t retry_conn_timer; 
    wiced_bt_device_address_t retry_bdaddr;
} tRC_APP_CB;

void hci_control_rc_controller_init(void);
wiced_result_t hci_control_rc_controller_send_pass_through_cmd(uint8_t op_id, uint8_t state);
void avrc_handle_registered_notification_rsp(uint8_t handle, app_avrc_reg_notif_rsp_t *reg_notif);
void avrc_passthrough_cback( uint8_t handle, uint8_t operation_id, wiced_bt_avrc_ctype_t ctype, app_avrc_pass_thru_hdr_t *avrc_pass_rsp);
#endif

