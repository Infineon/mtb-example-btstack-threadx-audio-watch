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
 * This file implement BTLE application controlled over UART.
 * The GATT database is defined in this file and is not changed by the MCU.
 */
#ifndef __HCI_CONTROL_LE_H_
#define __HCI_CONTROL_LE_H_

#pragma once

#include <wiced_bt_cfg.h>
#include <wiced_bt_gatt.h>
#include <wiced_timer.h>

#include "hci_control_api.h"
#include "app.h"

/******************************************************
 *                     Constants
 ******************************************************/
#ifndef LE_CONTROL_MAX_CONNECTIONS
#define LE_CONTROL_MAX_CONNECTIONS          20
#endif
#define LE_CONTROL_CONNECT_TIMEOUT          10

#define CYPRESS_COMPANY_ID 0x0131

/******************************************************
 *                     Structures
 ******************************************************/
typedef struct
{
#define LE_CONTROL_STATE_IDLE                       0
#define LE_CONTROL_STATE_DISCOVER_PRIMARY_SERVICES  1
#define LE_CONTROL_STATE_DISCOVER_CHARACTERISTICS   2
#define LE_CONTROL_STATE_DISCOVER_DESCRIPTORS       3
#define LE_CONTROL_STATE_READ_VALUE                 4
#define LE_CONTROL_STATE_WRITE_VALUE                5
#define LE_CONTROL_STATE_WRITE_NO_RESPONSE_VALUE    6
#define LE_CONTROL_STATE_NOTIFY_VALUE               7
#define LE_CONTROL_STATE_INDICATE_VALUE             8
#define LE_CONTROL_STATE_WRITE_DESCRIPTOR_VALUE     9
#define LE_CONTROL_STATE_DISCONNECTING              10

    uint8_t           state;                // Application discovery state
    wiced_bool_t      indication_sent;      // WICED_TRUE if indication sent and not acked
    BD_ADDR           bd_addr;
    uint16_t          conn_id;              // Connection ID used for exchange with the stack
    uint16_t          peer_mtu;             // MTU received in the MTU request (or 23 if peer did not send MTU request)

    uint8_t           role;                 // HCI_ROLE_CENTRAL or HCI_ROLE_PERIPHERAL
} hci_control_le_conn_state_t;

typedef struct
{
    hci_control_le_conn_state_t conn[LE_CONTROL_MAX_CONNECTIONS + 1];
} hci_control_le_cb_t;

typedef struct t_hci_control_le_pending_tx_buffer_t
{
    wiced_bool_t        tx_buf_saved;
    uint16_t            tx_buf_conn_idx;
    uint16_t            tx_buf_type;
    uint16_t            tx_buf_len;
    uint16_t            tx_buf_handle;
    uint8_t             tx_buf_data[HCI_CONTROL_GATT_COMMAND_MAX_TX_BUFFER];
} hci_control_le_pending_tx_buffer_t;

/******************************************************
 *               Function Definitions
 ******************************************************/
void hci_control_le_init(void);
void hci_control_le_enable(const wiced_bt_cfg_settings_t *settings);
void hci_control_le_connect_timeout(TIMER_PARAM_TYPE count);
wiced_bt_gatt_status_t hci_control_le_gatt_callback(wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data);
void hci_control_le_gatt_op_comp_read_handle(uint16_t conn_idx, wiced_bt_gatt_operation_complete_t *p_complete);
void hci_control_le_gatt_op_comp_write_handle(uint16_t conn_idx, wiced_bt_gatt_status_t status);
void hci_control_le_notification_handler( uint16_t conn_idx, uint16_t handle, uint8_t *p_data, uint16_t len );
void hci_control_le_indication_handler( uint16_t conn_idx, uint16_t handle, uint8_t *p_data, uint16_t len );
wiced_bt_gatt_status_t hci_control_le_write_handler( uint16_t conn_idx, app_gatt_write_req_t * p_data );
wiced_result_t hci_control_le_write_exec_handler( uint16_t conn_idx, wiced_bt_gatt_exec_flag_t flag );
wiced_result_t  hci_control_le_conf_handler( uint16_t conn_idx, uint16_t handle );

/******************************************************
 *               extern
 ******************************************************/
extern hci_control_le_cb_t le_control_cb;


#endif // __HCI_CONTROL_LE_H_
