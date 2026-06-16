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
 * app.h
 * This file is applicable for all devices with BTSTACK version 3.0 and greater, for example 55572
 *
 */
#ifndef _APP_AVRC_H__
#define _APP_AVRC_H__

/******************************************************
 *               Defines
 ******************************************************/

/******************************************************
 *               type Definitions
 ******************************************************/

typedef wiced_bt_avrc_rsp_t app_avrc_response_t;
typedef wiced_bt_avrc_metadata_cmd_t app_avrc_cmd_t;
typedef wiced_bt_avrc_metadata_reg_notif_rsp_t app_avrc_reg_notif_rsp_t;
typedef wiced_bt_avrc_pass_thru_hdr_t app_avrc_pass_thru_hdr_t;

/******************************************************
 *               Function Definitions
 ******************************************************/
wiced_result_t app_avrc_set_player_settings (uint16_t handle, uint8_t attr_id );
void app_avrc_handle_registered_notification_rsp(uint8_t handle, app_avrc_response_t *avrc_rsp);
void app_avrc_setting_change(uint8_t event_data[], uint16_t * idx, wiced_bt_avrc_player_app_param_t * setting);
void app_avrc_handle_element_attribute_rsp(uint8_t handle, app_avrc_response_t *avrc_rsp);
void app_avrc_passthrough_cback(uint8_t handle, wiced_bt_avrc_ctype_t ctype, wiced_bt_avrc_pass_thru_hdr_t *avrc_pass_rsp);

/******************************************************
 *               Macro Function Definitions
 ******************************************************/
#define app_avrc_send_pass_through( handle, id, state) wiced_bt_avrc_ct_send_pass_through_cmd((uint8_t) handle, id, state, 0 )
#define app_avrc_pdu( p ) ( p->type.metadata.metadata_hdr.pdu )
#define app_avrc_cmd_pdu( p ) ( p->metadata_hdr.pdu )
#define app_avrc_list_app_attr( p ) ( &p->type.metadata.u.list_app_attr )
#define app_avrc_p_attr( p ) ( p->type.metadata.u.list_app_attr.p_attrs )
#define app_avrc_list_app_values( p ) p->type.metadata.u.list_app_values
#define app_avrc_list_app_values_p_vals( p ) ( p->type.metadata.u.list_app_values.p_vals )
#define app_avrc_list_app_values_attr_id( p ) ( p->hdr.opcode )
#define app_avrc_get_cur_app_val( p ) p->type.metadata.u.get_cur_app_val
#define app_avrc_get_cur_app_val_attr_id( p ) ( p->type.metadata.u.get_cur_app_val.p_vals[0] )
#define app_avrc_get_cur_app_val_attr_val( p ) ( p->type.metadata.u.get_cur_app_val.p_vals[1] )

/******************************************************
 *               extern variables
 ******************************************************/

#endif // _APP_AVRC_H__
