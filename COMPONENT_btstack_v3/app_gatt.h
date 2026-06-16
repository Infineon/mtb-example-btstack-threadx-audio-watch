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

#ifndef _APP_HCI_H_
#define _APP_HCI_H_

/******************************************************
 *               Macro Function Definitions
 ******************************************************/
#define app_gatt_valid_conn_id( idx ) ( le_control_cb.conn[idx].conn_id != 0 )
#define app_gatt_discovery_type( p ) ( p->discovery_type )

#define APP_GATT_WRITE_NRSP GATT_CMD_WRITE   // should change to GATT_REQ_WRITE?
#define APP_GATT_WRITE GATT_REQ_WRITE

/******************************************************
 *               Function Definitions
 ******************************************************/
uint16_t               app_gatt_get_conn_idx(uint16_t conn_id);
uint16_t               app_gatt_allocate_conn_cb(void);
uint16_t               app_gatt_get_conn_id(uint16_t conn_idx);
wiced_result_t         app_gatt_operation_comp_cb( wiced_bt_gatt_operation_complete_t *p_complete);
wiced_bt_gatt_status_t app_gatt_req_cb(wiced_bt_gatt_attribute_request_t *p_req);
wiced_bt_gatt_status_t app_gatt_send_write(uint8_t conn_idx, uint16_t attr_handle, uint8_t *p_data, uint16_t len, wiced_bt_gatt_opcode_t type);
wiced_bt_gatt_status_t app_gatt_client_send_read_handle(uint16_t conn_idx, uint16_t handle);
wiced_bt_gatt_status_t app_gatt_send_response(uint16_t conn_id, uint16_t handle, uint8_t *p_data, uint16_t len);
wiced_bt_gatt_status_t app_gatt_operation_complete(wiced_bt_gatt_operation_complete_t *p_data);
void                   app_gatt_send_read_by_handle(uint16_t conn_id, uint16_t handle);
wiced_bool_t           app_gatt_send_read_by_type(uint16_t conn_id, uint16_t s_handle, uint16_t e_handle, uint16_t uuid);

#endif // _APP_HCI_H_
