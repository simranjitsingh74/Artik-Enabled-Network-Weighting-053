# Artik-Enabled-Network-Weighting-053


Welcome to the Artik-Enabled-Network-Weighting-053 wiki!


TOOLKIT:

Artik 053 Module from Samsung.
1Kg Load Cell
24Bit ADC
A strip of male to female headers


Artik IDE Installation:
1. Download the IDE from Artik Website.
2. Install it.
3. Follow the steps mentioned on the Artik Website.
4. Select: "Artil 053 SDK v1.7"  in select the package to install or remove window
5. Select: "gcc-aarch64-linux-gnu v5.4.1-2017.05"  in Toolchains
6. DONE


Description:
Connect the Artik Development Board to the computer using USB.
Open Artik IDE
Creating Console window:  select window> show view> console> command shell console> ""Give name to connection name and select the serial port> finish.
Press reset button the Artik Module
Details will be shown on the newly created console window about Artik.


Installing the JTAG Driver for running Tizen RT application:
Go to Computer directory where IDE is installed.
1. "ArtikIDE installation directory> tools.
2. select "zadig-2.3.exe" application and open it.
3. Under "options", select "list of all devices".
4. Select drop-down list, select interface 0 of the dual COM port interface.
5. Replace "FTDIBUS" driver> WINUSB by clicking "replace driver"
6. USB JTAG driver installed.


Working on Pre-defined project in the Artik IDE:
1. Select FILE> NEW> C Project> project name> Select Artik 053C> Next> Select "any examples you're interested in"> Accept> Default and Finish.

Compile the project:
1. Right-click on the project name in the left pane "whatever the name of the project is".
2. Select "build project"
3. Flash ALL
4. Right-click on the project name again.
5. Run as Tizen RT Application
6. Again right-click and select Debug as "Tizen RT application.

NOTE: During the debug mode, it stops at a breakpoint. RESUME it for further action.


Artik with WIFI using Mobile:

1. Create new project, Select NEW> C Project> PROJECT name> Artik 053c> Artik Onboarding and finish.
2. Select the ‘artik_onboarding.c” and Select the project> Build project> Flash ALL > Run as Tizen > Debug as Tizen.
3. Open Artik APP in mobile and scan the QR code on module. It’ll automatically connect to the Artik Module Wi-Fi and then choose another WIFI connection.
4. Using that APP, we can turn ON/OFF onboard LED.
