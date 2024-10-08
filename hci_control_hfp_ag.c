/*
 * Copyright 2016-2024, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * This file implements Hands-free profile Audio Gateway
 *
 */

#ifdef WICED_APP_HFP_AG_INCLUDED

#include "hci_control_api.h"
#include "wiced_bt_trace.h"
#include "wiced_transport.h"
#include "hci_control_hfp_ag.h"
#include "hci_control.h"

#include "wiced_bt_hfp_ag.h"

#if (BTM_WBS_INCLUDED == TRUE )
#define BT_AUDIO_HFP_SUPPORTED_FEATURES     (HFP_AG_FEAT_VREC | HFP_AG_FEAT_CODEC | HFP_AG_FEAT_ESCO | HFP_AG_FEAT_ECS)
#else
#define BT_AUDIO_HFP_SUPPORTED_FEATURES     (HFP_AG_FEAT_VREC | HFP_AG_FEAT_ESCO | HFP_AG_FEAT_ECS)
#endif

/******************************************************
 *               Variables Definitions
 ******************************************************/
hfp_ag_session_cb_t  ag_scb[HCI_CONTROL_AG_NUM_SCB];


/******************************************************
 *               Function Definitions
 ******************************************************/
#if defined(CYW55500A1)
/*
 * HF event callback. Format the data to be sent over the UART
 *
 * Format of transmit buffer:
 *          1 byte   HFP event code
 *          2 bytes  handle
 *          n bytes  data depending on event code
 */
void hci_control_hfp_ag_hci_send_ag_event( uint16_t evt, uint16_t handle, hfp_ag_event_t *p_data )
{
    uint8_t   tx_buf[300];
    uint8_t  *p = tx_buf;
    int       i;

    WICED_BT_TRACE("[%u]hfp_ag_hci_send_ag_event: Sending Event: %u  to UART\n", handle, evt);

    *p++ = ( uint8_t ) ( handle );
    *p++ = ( uint8_t ) ( handle >> 8 );

    switch ( evt )
    {
    case HCI_CONTROL_AG_EVENT_OPEN:       /* HS connection opened or connection attempt failed  */
        for ( i = 0; i < BD_ADDR_LEN; i++ )
            *p++ = p_data->open.bd_addr[BD_ADDR_LEN - 1 - i];
        *p++ = p_data->open.status;
        break;

    case HCI_CONTROL_AG_EVENT_CONNECTED: /* HS Service Level Connection is UP */
        *p++ = ( uint8_t ) ( p_data->conn.peer_features );
        *p++ = ( uint8_t ) ( p_data->conn.peer_features >> 8 );
        break;
    case HCI_CONTROL_AG_EVENT_AT_CMD:
        memcpy(p, p_data->at_cmd.cmd_ptr, p_data->at_cmd.cmd_len);
        p += p_data->at_cmd.cmd_len;
        break;
    case HCI_CONTROL_AG_EVENT_AUDIO_OPEN:
        *p++ = ( uint8_t ) (p_data->audio_open.wbs_supported);
        *p++ = ( uint8_t ) (p_data->audio_open.wbs_used);
        break;
    default:                             /* Rest have no parameters */
        break;
    }

    wiced_transport_send_data( evt, tx_buf, ( int ) ( p - tx_buf ) );
}
#endif
/*
 * Audio Gateway init
 */
void hci_control_ag_init( void )
{
    hfp_ag_session_cb_t *p_scb = &ag_scb[0];
    wiced_bt_dev_status_t result;
    int i;

    memset( &ag_scb, 0, sizeof( hfp_ag_session_cb_t ) );

    for ( i = 0; i < HCI_CONTROL_AG_NUM_SCB; i++, p_scb++ )
    {
        p_scb->app_handle = ( uint16_t ) ( i + 1 );

        if(i == 0)
            p_scb->hf_profile_uuid = UUID_SERVCLASS_HF_HANDSFREE;
        else
            p_scb->hf_profile_uuid = UUID_SERVCLASS_HEADSET;
    }
#if defined(CYW55500A1)
    hfp_ag_startup( &ag_scb[0], HCI_CONTROL_AG_NUM_SCB, BT_AUDIO_HFP_SUPPORTED_FEATURES, hci_control_hfp_ag_hci_send_ag_event );
#else
    hfp_ag_startup( &ag_scb[0], HCI_CONTROL_AG_NUM_SCB, BT_AUDIO_HFP_SUPPORTED_FEATURES);
#endif
}

/*
 * Handle Handsfree commands received over UART.
 */
void hci_control_ag_handle_command( uint16_t opcode, uint8_t* p_data, uint32_t length )
{
    uint16_t handle;
    uint8_t  hs_cmd;
    uint8_t  *p = ( uint8_t * ) p_data;

    switch ( opcode )
    {
    case HCI_CONTROL_AG_COMMAND_CONNECT:
        hci_control_switch_hfp_role( HFP_AUDIO_GATEWAY_ROLE );
        hfp_ag_connect( p );
        break;

    case HCI_CONTROL_AG_COMMAND_DISCONNECT:
        handle = p[0] | ( p[1] << 8 );
        hfp_ag_disconnect( handle );
        break;

    case HCI_CONTROL_AG_COMMAND_OPEN_AUDIO:
        handle = p[0] | ( p[1] << 8 );
        hfp_ag_audio_open( handle );
        break;

    case HCI_CONTROL_AG_COMMAND_CLOSE_AUDIO:
        handle = p[0] | ( p[1] << 8 );
        hfp_ag_audio_close( handle );
        break;
    case HCI_CONTROL_AG_COMMAND_SET_CIND:
        hfp_ag_set_cind((char *)&p[0], length);
        break;
    case HCI_CONTROL_AG_COMMAND_STR:
        handle = p[0] | ( p[1] << 8 );
        hfp_ag_send_cmd_str(handle, &p[2], length-2);
        break;
    default:
        WICED_BT_TRACE ( "hci_control_ag_handle_command - unkn own opcode: %u %u\n", opcode);
        break;
    }
}

#endif  // WICED_APP_HFP_AG_INCLUDED
