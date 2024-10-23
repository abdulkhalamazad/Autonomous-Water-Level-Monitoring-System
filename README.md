# Autonomous-Water-Level-Monitoring-System
The Autonomous Water Level Monitoring System uses an ESP8266 and Blynk app to track water levels at 25%, 50%, 75%, and 100% via stainless steel probes. The system automatically controls a pump, turning it on below 25% and off at 100%. Users can monitor levels and manually control the pump remotely via the Blynk app for efficient water management.
## Features
- Will show the water level on the blynk application on your smartphone and also on the LCD Display on the device.
- Will show the time when the motor last turned ON.
- Will show the total time taken by the motor to fill the tank.
- It shows the current status of the motor (ON/OFF)
- Send push notification to smartphone when motor turns ON and OFF.
- It shows "Error" when any of the lower level sensors malfunctions, also shows this on the app by blinking an LED. (eg. if 50% sensor detects water but 25% doesn't and so on)
- Dry Run protection.(If under any circumstances the motor runs continuously for 8 minutes, the motor turn OFF and it requires manual reset for working again, it also notifies on the smartphone.)
- There is a virtual ON/OFF button on the smartphone, which you can use for manually controlling the motor. (if motor is ON you can turn OFF the motor by pressing the button and vice versa. if the water level is a 0% or 100% don't try to press the button as this will cause rapid toggling of the state of the motor.)
 ## Setting Up
 ### Blynk Setup
 - First create an account on [blynk.io](https://blynk.io/)
 - Then create a new device with the name "Autonomous water level monitoring system"
 - you'll get blynk auth token, blynk template name, blynk template id from this which is needed to be updated on the code.
 - Then go to "developer zone" and select "Datastreams"
 - Add 5 virtual pins from "V1 to V4" of integer datatype and "V5" of string datatype and provide it with some name.
 - "V1" is responsible for the count (No: of times motor turned ON in a day. Use "Value Widget" to represent that.)
 - "V2" is responsible for water level in percentage. (Use "Guage Widget" to represent that.)
 - "V3" is responsible for the ON/OFF button in the application (Use "Switch Widget" for this.)
 - "V4" is responsible to show error if there is any. (Use "LED Widget" for this).
 - "V5" is responsible to show the last motor turn ON time. (Use "Value Widget" for this.)
 - Final look of the application is provided in the "Final Product Images" folder.
### Code Setup
- Modify the blynk auth token, blynk template name, blynk template id with your device's credentials.
- Modify the Wifi SSID and Password with your Id and password.
- upload the code to ESP 8266 without any peripherals connected.
### Circuit Setup
- Connect the circuit as shown in the diagram.
- If you don't want to remove the physical switch, you can do the bypass method for both normal and dipole switches. (Switch's input to relay's input and switch's output to relay's output.)
- I have used several pullup and pulldown resistors of 10k to avoid floating of terminals and to make sure no noise are being picked up.
### General Setup
- Try to provide a basic ventillation for dissipation of heat, SSRs may generate heat during opration.
- Try to place the device where the signal strength is above average (-55 to -75 dBm atleast).
- There is a possibility of Electrolysis and material deposition on the tips of the probe, So make sure to clean it in a month or so (Working on a solution for this).

