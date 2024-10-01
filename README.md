# Watch app

## Overview
This app demonstrates Bluetooth&#174; A2DP source, AVRCP Controller/Target, Apple Media Service (AMS), Apple Notification Center Service (ANCS), and HFP Audio Gateway/Hands-free Unit.

Features demonstrated:

 - AIROC&#8482; A2DP Source APIs
 - AIROC&#8482; AVRCP (Controller/Target) APIs
 - AIROC&#8482; GATT APIs
 - Apple Media Service and Apple Notification Center Services (AMS and ANCS)
 - Handling of the UART/SPI AIROC&#8482; protocol
 - SDP and GATT descriptor/attribute configuration
 - AIROC&#8482; SCO/RFCOMM initiator APIs and HFP Audio Gateway role
 - HFP Hands-free Unit role


## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) v3.2 or later (tested with v3.2) with ModusToolbox&trade; CYW955513 Early Access Pack for CYW955513EVK-01
- Board support package (BSP) minimum required version for : v1.0.0.
- Programming language: C
- Associated parts: CYW955513EVK-01

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`

## Supported kits (make variable 'TARGET')
- CYW955513EVK-01 Wi-Fi Bluetooth&reg; prototyping kit (`CYW955513EVK-01`)


## Hardware setup

This example uses the kit’s default configuration. See the respective kit guide to ensure that the kit is configured correctly.

**Note:** The CYW955513EVK-01 Wi-Fi Bluetooth&reg; prototyping kit ships with KitProg3 version 2.30 installed. The ModusToolbox&trade; software requires KitProg3 with latest version 2.50. Before using this code example, make sure that the board is upgraded to KitProg3 2.50. The tool and instructions are available in the [Firmware Loader](https://github.com/Infineon/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error such as "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".

### EVK Board Requirement

- This application is applicable for CYW955513EVK-01 with version >= REV02.

### Codec Board Requirement

- This application use the CYW9BTAUDIO5 as the audio codec shield board

## Software setup

Install the BTSpy.

- [BTSpy](https://github.com/Infineon/btsdk-utils): Bluetooth&reg; Trace through HCI Uart

## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

The "project-creator-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br />

The following example clones the "[Hello world](https://github.com/Infineon/mtb-example)" application with the desired name "MyHelloWorld" configured for the *CYW955513EVK-01* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CYW955513EVK-01 --app-id mtb-example-hal-hello-world --user-app-name MyHelloWorld --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can invoke the Library Manager GUI tool from the terminal using `make modlibs` command or use the Library Manager CLI tool "library-manager-cli" to change the BSP.

The "library-manager-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--add-bsp-name` | Name of the BSP that should be added to the application | Required
`--set-active-bsp` | Name of the BSP that should be as active BSP for the application | Required
`--add-bsp-version`| Specify the version of the BSP that should be added to the application if you do not wish to use the latest from manifest | Optional
`--add-bsp-location`| Specify the location of the BSP (local/shared) if you prefer to add the BSP in a shared path | Optional

<br />

Following example adds the CYW955513EVK-01 BSP to the already created application and makes it the active BSP for the app:

   ```
   library-manager-cli --project "C:/mtb_projects/MyHelloWorld" --add-bsp-name CYW955513EVK-01 --add-bsp-version "latest-v4.X" --add-bsp-location "local"

   library-manager-cli --project "C:/mtb_projects/MyHelloWorld" --set-active-bsp CYW955513EVK-01
   ```

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br />

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and then import the libraries using the `make getlibs` command.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation

## Instructions
To demonstrate the app, follow these steps:

1. Build and download the application to the AIROC&#8482; board.
2. Open the ClientControl application
     - [UART] Open the "WICED HCI" port for the device. (Default baud rate configured in the application is defined by the BSP HCI\_UART\_DEAULT\_BAUD #define, usually either 3M or 115200 depending on the board UART capabilities.)
3. Use the ClientControl application to send various commands as mentioned below.
4. Run the BTSpy program to view protocol and application traces.

BR/EDR Audio Source and AVRC Target:

- The Watch app can demonstrate how to use BR/EDR Audio Source and AVRC TG profiles.
- Audio Source can use I2S interrupt or SW timer to decide the timing to read PCM.
  For media type as 'I2S input', it will use I2S interrupt, and you need to configure 4 GPIOs as AIROC&#8482; I2S PINs.
  For media type as 'Wav file' or 'Sine wave', it will use SW timer by calling wiced\_audio\_use\_sw\_timing(1).
  In general, if using the "WICED HCI" UART to transmit audio, it must either allocate I2S pins on unused pins for
  I2S interrupt OR use wiced\_audio\_use\_sw\_timing(1) to enable SW timer.
- Use the buttons in the ClientControl AV Source tab.
- To play a sine wave sample, set the audio frequency to the desired value (48kHz, 44.1kHz, etc.)
  and select the Media type as 'Sine Wave' in the UI. In this case, built-in sine wave audio is played.
- To play music from a .wav file, select the Media type as File, browse and select a .wav file,
  and set the audio frequency to the desired value (48kHz, 44.1kHz, etc.)
  In this case, audio for the .wav file is routed over the "WICED HCI" UART to the AIROC&#8482; board.<br>

sinc\_44100\_16\_L440\_R1000\_50s\_stereo.wav in the app folder can be used as the input of 44.1KHz 16bits stereo samples.
- To play music from a .mp3 file, select the Media type as File, browse and select a .mp3 file,
  and set the audio frequency to the desired value (48kHz, 44.1kHz, etc.)
  In this case, audio for the .mp3 file is routed over the "WICED HCI" UART to the AIROC&#8482; board.

### BT SDK Features:

BR/EDR AVRCP Controller:

- The Watch app can demonstrate how to use the AVRC CT profile.
- Disconnect all devices if any are connected.
- Make an audio source device such as an iPhone discoverable/pairable from the Bluetooth&#174; Settings UI on the phone.
- Using the "BR/EDR Discovery" "Start" button, search and select the device.
- Use the buttons in the ClientControl AVRC CT tab to Connect and accept pairing.
- Play music on the audio source device and control the music via buttons in the AVRC CT tab.
- In Controller mode, pass-thru commands are executed via Play, Pause, Stop, etc. buttons.
- Absolute volume change can be done via the drop-down Volume or Vol Up/Down buttons.
- Note that iPhone does not support Vol buttons.
- Note that music will continue to play on the audio source device.

iOS ANCS and AMS GATT Services:

- The Watch app can demonstrate how to use AMS and ANCS iOS services as shown below.
- Disconnect all devices if any are connected.
- Select Pairable if it is not checked.
- Click the "Start Adverts" button in the GATT tab.
- Set MAX_PHONE_CONNECTIONS for support of more than one iPhone.
- From an iPhone app such as 'LightBlue', find and connect to the 'Watch' app.
- Allow pairing with the iPhone.
- AMS:
  - Play media on each iPhone. Play, Pause, Prev, Next, Vol Up, Vol Down notification messages will be displayed on the UI.
  - Use buttons like Play, Pause, Prev, Next, Vol Up, and Vol Down in the ClientControl AVRC CT tab to control the music.
  - Note that music will continue to play on iPhone.
- ANCS:
  - Incoming calls and messages to each iPhone notification message will be displayed on the UI.
  - Make an incoming call to each iPhone. See a call notification displayed on the UI to accept or reject the call. Similarly, missed call notifications are seen.
  - Send an SMS message to each iPhone to see a message notification.

LE Client:

- The Watch app can demonstrate LE Client functionality as shown below.
- Make sure there is a Bluetooth&#174; device with GATT services that is advertising. For example, use an app
  such as 'LightBlue' on your phone and create a 'Virtual Peripheral' such as 'Blood Pressure'.
- To find GATT devices:
  - Click on the "Start" button for the "LE Discovery" combo box.
  - Click on the "Stop" button to end discovery.
- To connect an LE device:
  - Choose a device from the "LE Discovery" drop-down combo box and click the "Connect" button.
- To discover services: Click on the "Discover Services" button
- To discover characteristics: Enter the handles in the edit box and click
  on "Discover Characteristics"
- To discover descriptors: Enter the handles in the edit box and click on
  "Discover Descriptors"
- Enter the Handle and Hex Value to write to the remote device using buttons:
  - "Write": Write a hex value to the remote handle
  - "Write no rsp": Write a hex value without a response to the remote handle
  - "Value Notify": Write a notification value to the remote handle
  - "Value Indicate": Write an indication value to the remote handle

HFP Audio Gateway:

- Build with "HFP\_AG\_INCLUDED=1" to enable AG. (disables Hands-free Unit simultaneously)
- The Watch app can demonstrate how to use HFP AG as shown below.
- Make an HFP Headset (headphone or earbuds) discoverable and pairable by its specific behavior.
- In ClientControl, click on the "Start" button from the "BR/EDR Discovery" combo box to find the Headset device.
- Select the peer device in the BR/EDR Discovery combo box.
- Click the "Connect" button under the ClientControl AG tab.
- Click the "Audio Connect" button. The AG will create a SCO connection to the Headset, and wide-band speech is supported.
- Click the "Audio Disconnect" button to remove the SCO connection.
- Use Speaker Volume and Mic Volume  drop-down menu to set HF Speaker gain and HF Microphone gain respectively.
- Use the indicators (Service availability, call status, call setup, call held, signal strength, battery value, and roaming) drop-down menu to simulate indicator changes.
- To simulate incoming/outgoing calls, use the indicators  drop-down menu and RING/CCWA button.


HFP Hands-free Unit:

- To create a hands-free connection with a remote Audio Gateway (AG) device (such as a mobile phone), use ClientControl and choose the Bluetooth&#174; address of the remote AG device from the BR/EDR combo box.<br/>
  Click the "Connect" button under the HF tab.
- OR Put the device in discoverable and connectable mode and search for the device from the AG device and connect.
- The following HF operations can be performed using the ClientControl HF tab:
   -  Connect / Disconnect the HF or SCO connection
   -  Answer / Hang up the call
   -  Dial / Redial the number
   -  Control Held calls - features supported are:
      - Release all held
      - Release active accept other
      - Place active on hold and accept other
      - Add held to the conversation (Note: This functionality depends on the support from telecom network operator. AG always supports this feature and responds with OK.)
   -  Mic / Speaker gain control

### Application Settings
Application-specific settings are as shown below:

- CYHAL\_SLEEP\_SUPPORTED
    - This option allows the device to enter low power mode. By default, the option is off. When sleep is enabled, ClientControl will not be able to communicate with the embedded app unless a GPIO is asserted.
    - It is supported in 55500A1-related target (CYW955513EVK-01).

## BTSTACK version

BTSDK AIROC&#8482; chips contain the embedded AIROC&#8482; Bluetooth&#174; stack, BTSTACK. Different chips use different versions of BTSTACK, so some assets may contain variant sets of files targeting the different versions in COMPONENT\_btstack\_vX (where X is the stack version). Applications automatically include the appropriate folder using the COMPONENTS make variable mechanism, and all BSPs declare which stack version should be used in the BSP .mk file, with a declaration such as:<br>
> COMPONENTS+=btstack\_v1<br>
or:<br>
> COMPONENTS+=btstack\_v3

## Common application settings

Application settings below are common for all BTSDK applications and can be configured via the makefile of the application or passed in via the command line.

##### BT\_DEVICE\_ADDRESS
> Set the BDA (Bluetooth&#174; Device Address) for your device. The address is 6 bytes, for example, 20819A10FFEE. By default, the SDK will set a BDA for your device by combining the 7 hex digit device ID with the last 5 hex digits of the host PC MAC address.

##### UART
> Set to the UART port you want to use to download the application. For example 'COM6' on Windows or '/dev/ttyWICED\_HCI\_UART0' on Linux or '/dev/tty.usbserial-000154' on macOS. By default, the SDK will auto-detect the port.

### Testing with PTS
1. While testing with PTS for certification test cases, please define ENABLE\_PTS\_TESTING flag in makefile as shown below.
   CY\_APP\_DEFINES += -DENABLE\_PTS\_TESTING

2. For A2DP/SNK/REL/BV/02-I test case, to initiate disconnection from IUT, please long press and hold the Vol- button

3. For A2DP/SNK/CC/BV-03-I and A2DP/SNK/CC/BV-04-I test cases, 16Khz and 32Khz sampling rate will be supported by defining ENABLE\_PTS\_TESTING flag

## BTSpy

BTSpy is a trace utility that can be used in the AIROC&trade; Bluetooth&reg; platforms to view protocol and generic trace messages from the embedded device. BTSpy is available as part of the ModusToolbox&trade; installation. If not, download and install [BTSpy](https://github.com/Infineon/btsdk-utils).

1. Add the `HCI_TRACE_OVER_TRANSPORT` macro in the Makefile or command-line `CY_APP_DEFINES+=HCI_TRACE_OVER_TRANSPORT`.

2. Call `wiced_hci_trace_enable();`

3. Ensure that retarget-io is not enabled on the same UART port as BTSpy. There is no need to initialize the retarget-io library if the application wants to send both application messages and Bluetooth&reg; protocol traces to the same port through BTSpy.

4. Use compiler directives to either initialize the retarget-io library or BTSpy logs depending on the debug macro setting.

   For example:
   ``` cpp
   #ifdef HCI_TRACE_OVER_TRANSPORT
   #define TRANS_UART_BUFFER_SIZE 1024
   #define TRANSPORT_BUFFER_SIZE 1500
   #define TRANSPORT_BUFFER_COUNT 2
   #define TRANSPORT_UART_BAUD_RATE 3000000
   typedef wiced_bool_t (*classic_audio_rpc_cback_t)(uint16_t opcode, uint8_t *p_data, uint32_t data_len);
   #endif
   ```

### Enable BTSpy logs

1. In the Makefile, set `CY_APP_DEFINES+=HCI_TRACE_OVER_TRANSPORT`.
2. Build and program the board.
3. Open ClientControl.
4. Set the baud rate to 3000000.
5. Deselect flow control.
6. Select the port and click **Open port**.
7. Launch BTSpy.
8. Press and release the reset button on the board to get BTSpy logs.
9. You should see all the application traces and the Bluetooth&reg; HCI messages. These messages help debug the HCI commands issued to the Bluetooth&reg; controller. Application traces indicate the start/stop of advertisements, connection/disconnection, and PHY updates.


## Design and implementation

### Resources and settings

**Table 1. Application resources**

Resource         | Alias/object             | Purpose
:----------------|:-------------------------|:-----------------------------------------------------------
HCI-UART (HAL)   | cy\_retarget\_io\_uart\_obj  | UART HAL object used by retarget-io for the Debug UART port
LHL GPIO 6 (HAL) | PLATFORM\_BUTTON\_CUSTOM   | User custom button
BT GPIO 4 (HAL)  | PLATFORM\_BUTTON\_VOL_UP   | Volume+
BT GPIO 5 (HAL)  | PLATFORM\_BUTTON\_VOL\_DOWN | Volume-
BT GPIO 17 (HAL) | mSPI                     | SPI interface for cs47l35 dsp (SPI CLK)
LHL GPIO 8 (HAL) | mSPI                     | SPI interface for cs47l35 dsp (SPI MOSI)
LHL GPIO 9 (HAL) | mSPI                     | SPI interface for cs47l35 dsp (SPI MISO)
BT GPIO 16 (HAL) | mSPI                     | SPI interface for cs47l35 dsp (SPI CS)
TDM2 SCK         |                          | tdm and i2s interface for cs47l35 dsp 
TDM2 WS          |                          | tdm and i2s interface for cs47l35 dsp 
TDM2 DO          |                          | tdm and i2s interface for cs47l35 dsp 
TDM2 DI          |                          | tdm and i2s interface for cs47l35 dsp 

<br />

## Related resources

Resources            | Links
---------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Device documentation | Contact infineon sales for device documentation
Development kits     | Contact infineon sales for kit samples
Libraries on GitHub  | [mtb-pdl-cat5](https://github.com/Infineon/mtb-pdl-cat5) – CYW55513 peripheral driver library (PDL)  <br /> [mtb-hal-cat5](https://github.com/Infineon/mtb-hal-cat5) – Hardware abstraction layer (HAL) library <br /> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Tools                | [Eclipse IDE for ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices.


## Other resources

Infineon provides a wealth of data at [www.infineon.com](https://www.infineon.com) to help you select the right device, and quickly and effectively integrate it into your design.


## Document history

Document title: *CE240259* - *Bluetooth&reg; mtb-example-btstack-threadx-audio-watch*

 Version | Description of change
 ------- | ---------------------
 1.0.0   | New code example
<br>


© Cypress Semiconductor Corporation, 2020-2022. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br />
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit www.infineon.com. Other names and brands may be claimed as property of their respective owners.

