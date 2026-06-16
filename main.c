/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Headset Speaker Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
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

#include "cybsp.h"
#include "cyhal.h"
#include "cy_pdl.h"
#include "cy_retarget_io.h"
#include "wiced_bt_trace.h"
#include "wiced_bt_dev.h"
#include "wiced_timer.h"
#ifdef HCI_TRACE_OVER_TRANSPORT
#include "wiced_transport.h"
#include "wiced_hal_puart.h"
#include "hci_control_api.h"
#endif

/*******************************************************************************
* Macros
********************************************************************************/
#ifdef HCI_TRACE_OVER_TRANSPORT
#define TRANS_UART_BUFFER_SIZE 1024
#define TRANSPORT_BUFFER_SIZE 1500
#define TRANSPORT_BUFFER_COUNT 2
#define TRANSPORT_UART_BAUD_RATE 3000000
typedef wiced_bool_t (*classic_audio_rpc_cback_t)(uint16_t opcode, uint8_t *p_data, uint32_t data_len);
#endif

/*******************************************************************************
* Function Prototypes
********************************************************************************/
#ifdef HCI_TRACE_OVER_TRANSPORT
static void classic_audio_rpc_transport_status_handler(wiced_transport_type_t type);
static uint32_t classic_audio_rpc_rx_callback(uint8_t *p_buffer, uint32_t length);
static classic_audio_rpc_cback_t g_rpc_app_callback;
#endif

extern void APPLICATION_START(void);

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Function
********************************************************************************/

#ifdef HCI_TRACE_OVER_TRANSPORT
void wiced_hci_trace_enable(void)
{
    wiced_set_debug_uart(WICED_ROUTE_DEBUG_NONE);
    
    wiced_bt_dev_register_hci_trace(NULL);
}

#endif // #ifdef HCI_TRACE_OVER_TRANSPORT

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:      Application entry point
*
* Parameters:   void
*
* Return:
*  int
*
*******************************************************************************/

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    cyhal_syspm_lock_deepsleep();

    /* Enable global interrupts */
    __enable_irq();

#ifdef HCI_TRACE_OVER_TRANSPORT
    wiced_hci_trace_enable();
#endif

    APPLICATION_START();

    WICED_BT_TRACE( "#############################\n" );
    WICED_BT_TRACE( "# Audio_Watch APP START #\n" );
    WICED_BT_TRACE( "#############################\n" );

    return 0;
}


/* [] END OF FILE */
