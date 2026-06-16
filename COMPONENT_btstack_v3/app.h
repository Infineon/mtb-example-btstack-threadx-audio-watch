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
#ifndef _APP_H__
#define _APP_H__

#include "wiced_bt_gatt.h"
#include "wiced_transport.h"
#include "wiced_memory.h"
#include "wiced_bt_event.h"
#include "hci_control.h"
#include "app_avrc.h"
#include "app_gatt.h"
#include "cycfg_gap.h"

/******************************************************
 *               Defines
 ******************************************************/

#define BT_STACK_HEAP_SIZE (1024 * 10)

#ifndef PACKED
#define PACKED
#endif

/******************************************************
 *               type Definitions
 ******************************************************/
#pragma pack(1)
typedef PACKED struct
{
    uint8_t                           br_edr_key_type;
    wiced_bt_link_key_t               br_edr_key;
    wiced_bt_dev_le_key_type_t        le_keys_available_mask;
    wiced_bt_ble_address_type_t       ble_addr_type;
    wiced_bt_ble_address_type_t       static_addr_type; //55572A1 does not have but 20721 does.
    wiced_bt_device_address_t         static_addr; //55572A1 does not have but 20721 does.
    wiced_bt_ble_keys_t               le_keys;
} wiced_bt_device_sec_keys_t_20721;

typedef PACKED struct
{
    wiced_bt_device_address_t   bd_addr;
    wiced_bt_device_sec_keys_t_20721  key_data;
} wiced_bt_device_link_keys_t_20721;
#pragma pack()

typedef wiced_bt_gatt_write_req_t app_gatt_write_req_t;

/******************************************************
 *               Function Definitions
 ******************************************************/
wiced_result_t         app_stack_init( void );
wiced_result_t         app_read_buffer_stats( void );
void                   app_pr_dev_started_evt();
int                    app_write_nvram( int nvram_id, int data_len, void *p_data, wiced_bool_t from_host );
wiced_bt_gatt_status_t app_gatt_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data );
void                   app_btu_hcif_send_cmd( uint16_t opcode, uint8_t* params, uint8_t params_length );
void                   app_paired_device_link_keys_update( wiced_bt_management_evt_data_t *p_event_data );
uint32_t               app_copy_advertisement_data( uint8_t *p_adv_data, uint8_t * buff, uint32_t buff_len );


/******************************************************
 *               Macro Function Definitions
 ******************************************************/
#define app_create_pool( size, count ) wiced_bt_create_pool( "pki", size, count, NULL )
#define app_transport_send_hci_trace( type, data, len ) wiced_transport_send_hci_trace( type, data, len )
#define app_free_rx_cmd_buffer( ptr )
#define app_get_pool_free_count( pool ) wiced_bt_get_pool_free_count( pool )
#define app_cfg_sec_mask() ( wiced_bt_cfg_settings.security_required )
#define APP_AVDT_CB p_avdt_ctrl_cback
#define app_gatt_db_init( data, len ) wiced_bt_gatt_db_init( data, len, watch_db_hash )
#define app_allocate_conn_id( id ) app_gatt_allocate_conn_cb()

/******************************************************
 *               extern variables
 ******************************************************/
extern wiced_bt_pool_t *            p_key_info_pool;  //Pool for storing the  key info
extern const wiced_transport_cfg_t  transport_cfg;
extern wiced_bt_db_hash_t           watch_db_hash;

#endif // _APP_H__
