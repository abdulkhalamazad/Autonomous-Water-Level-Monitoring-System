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
 - First create an account on [blynk.io](blynk.io)
 

