<div align="center">

# WiFi Thief Catcher

**A captive portal prank for ESP8266 to catch unwanted network guests.**

---

### Project Overview

This project turns an ESP8266 into a honeypot for people trying to steal WiFi. It broadcasts a fake, open WiFi network. When a user connects and attempts to log in or access the internet, they are redirected to a captive portal. Instead of granting access, it triggers a humorous prank featuring an image and loud audio.

---

### Hardware Requirements

* ESP8266 Microcontroller (e.g., NodeMCU, Wemos D1 Mini)
* Micro-USB Cable

---

### Setup Instructions

#### 1. Configure the Code
Open `Main.ino` and configure the network settings:
* Update `ap_ssid` to the name you want the fake network to broadcast.
* Update `sta_ssid` and `sta_password` to your actual internet-connected WiFi.

#### 2. Flash the ESP8266
Connect your ESP8266 to your computer and upload the `Main.ino` sketch using the Arduino IDE. Make sure you have the ESP8266 board definitions installed.

#### 3. Power On
Once flashed, the ESP8266 will broadcast the fake network. Connect to it from any device, and the captive portal should automatically pop up and trigger the prank!

---

### Disclaimer

This project is intended for educational and entertainment purposes only. Please use responsibly and do not use it to harm or disrupt networks that do not belong to you.



### Created By

**Sarthak Bhopale**
<br>
[GitHub Profile](https://github.com/1sarthak7)


</div>


