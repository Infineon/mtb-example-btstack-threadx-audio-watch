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

#ifndef HCI_CONTROL_PANU_H
#define HCI_CONTROL_PANU_H

#include <stdint.h>

#ifdef WICED_APP_PANU_INCLUDED

typedef struct
{
    BD_ADDR             bd_addr;
} panu_open_t;

typedef struct
{
    BD_ADDR             bd_addr;
    BD_ADDR             local_bdaddr;
} panu_connect_t;

typedef union
{
    panu_open_t    open;
    panu_connect_t conn;
} panu_event_t;

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
extern void panu_hci_send_panu_event(uint16_t evt, uint16_t handle, panu_event_t *p_data);
extern void panu_connected(BD_ADDR bd_addr);
extern void panu_disconnected(uint16_t handle);
extern void panu_connect_failed(uint16_t handle);
extern void hci_control_panu_init( void );
extern void hci_control_panu_handle_command(uint16_t opcode, uint8_t* p_data, uint32_t length);
extern void hci_control_panu_set_pfilter(uint16_t handle);
extern void hci_control_panu_set_mfilter(uint16_t handle);
extern void testcase_pan_panu_ip_app_bv_05_i(uint16_t handle);

#endif

#endif // HCI_CONTROL_PANU_H
