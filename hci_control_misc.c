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
 * This file implements the Miscellaneous Commands controlled over UART. Please refer to
 * the WICED HCI Control Protocol Software User Manual (WICED-SWUM10x-R) for additional
 * details on the HCI UART control protocol
 */

#include "wiced_bt_cfg.h"
#include "hci_control_api.h"
#include "hci_control.h"
#include "hci_control_audio.h"
#include "wiced_transport.h"

#define BCM920706 20706
#define BCM920707 20707

/******************************************************************************
 *                          Constants
 ******************************************************************************/

/******************************************************************************
 *                          Function Declarations
 ******************************************************************************/
void hci_control_misc_handle_get_version( void );

/******************************************************************************
 *                          Variable Definitions
 ******************************************************************************/

/******************************************************************************
 *                          Function Definitions
 ******************************************************************************/
void hci_control_misc_handle_command( uint16_t cmd_opcode, uint8_t* p_data, uint32_t data_len )
{
    switch( cmd_opcode )
    {
    case HCI_CONTROL_MISC_COMMAND_PING:
        wiced_transport_send_data( HCI_CONTROL_MISC_EVENT_PING_REPLY, p_data, data_len );
        break;

    case HCI_CONTROL_MISC_COMMAND_GET_VERSION:
        hci_control_misc_handle_get_version();
        break;

    default:
        WICED_BT_TRACE( "unknown miscellaneous command\n");
        break;
    }
}

void hci_control_misc_handle_get_version( void )
{
    uint8_t   tx_buf[20];
    uint8_t   cmd = 0;

// If this is 20819 or 20820, we do detect the device from hardware
#define RADIO_ID    0x006007c0
#define RADIO_20820 0x80
#define CHIP_20820  20820
#define CHIP_20819  20819
#if (CHIP==CHIP_20819) || (CHIP==CHIP_20820)
    uint32_t chip = CHIP_20819;
    if (*(UINT32*) RADIO_ID & RADIO_20820)
    {
        chip = CHIP_20820;
    }
#else
    uint32_t  chip = CHIP;
#endif

    tx_buf[cmd++] = WICED_SDK_MAJOR_VER;
    tx_buf[cmd++] = WICED_SDK_MINOR_VER;
    tx_buf[cmd++] = WICED_SDK_REV_NUMBER;
    tx_buf[cmd++] = WICED_SDK_BUILD_NUMBER & 0xFF;
    tx_buf[cmd++] = (WICED_SDK_BUILD_NUMBER>>8) & 0xFF;
    tx_buf[cmd++] = chip & 0xFF;
    tx_buf[cmd++] = (chip>>8) & 0xFF;
    tx_buf[cmd++] = (chip>>24) & 0xFF;
    tx_buf[cmd++] = 0; // not used

    /* Send MCU app the supported features */
#ifdef WICED_APP_LE_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_GATT;
#endif
#ifdef WICED_APP_AUDIO_SRC_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_AUDIO;
#endif
#ifdef WICED_APP_ANCS_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_ANCS;
#endif
#ifdef WICED_APP_AUDIO_RC_CT_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_AVRC_CONTROLLER;
#endif
#ifdef WICED_APP_AMS_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_AMS;
#endif
#ifdef WICED_APP_AUDIO_RC_TG_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_AVRC_TARGET;
#endif
#ifdef WICED_APP_HFP_AG_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_AG;
#endif
#ifdef WICED_APP_HFP_HF_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_HF;
#endif

#ifdef WICED_APP_PANU_INCLUDED
    tx_buf[cmd++] = HCI_CONTROL_GROUP_PANU;
#endif
    wiced_transport_send_data( HCI_CONTROL_MISC_EVENT_VERSION, tx_buf, cmd );

    hci_control_audio_support_features_send();
}
