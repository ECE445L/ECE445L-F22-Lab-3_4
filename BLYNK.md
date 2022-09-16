# BLYNK.md

## Prerequisites

1. Hardware is setup (TM4C hooked up to ESP8266 via UART)
2. ESP8266 is flashed with latest [firmware](https://github.com/ECE445L/EE445L-SP22-ESP8266-Blynk)
    1. See section [Updating ESP8266](#updating-esp8266)

## Running Blynk

1. Log in/Create an account
2. Go to my devices page
3. Create a new device and use Quickstart Template
4. You are provided a BLYNK template ID, device name, and auth token
    1. Only need the auth token
5. Use the blynk_init function call to pass in your auth token, SSID, and password to connect to Blynk!
	1. We suggest the SSID and PASS to correspond to the Lab IOT WiFi or hotspot.
6. Compile and flash program to TM4C
7. If the HW is setup properly, then Blynk should say the device is online.

## Updating ESP8266

1. Download the [Arduino IDE](https://www.arduino.cc/en/software)
    1. Last tested version: `1.8.19`
2. Add ESP8266 indices to Arduino board manager URLs `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
    1. `File > Preferences > Additional Board Manager URLs:`
    2. Go to `Tools > Boards Manager`
    3. Search for `esp8266`
    4. Install `v3.0.2`
3. Add Blynk libraries
    1. `Tools > Manage Libraries...`
    2. Search for `blynk`, install `Blynk` by Volodymyr Shymanskyy v1.1.0
4. Change board to `esp8266`
    1. `Tools > Board: "xxx" > ESP8266 Boards (3.0.2) > Generic ESP8266 Module`
5. Clone latest [firmware](https://github.com/ECE445L/EE445L-SP22-ESP8266-Blynk)
6. Open up ESP_TM4C_Xfer_Rev_HandShake_NEW_BLYNK project
    1. `EE445L-F22-ESP8266-Blynk > ESP_TM4C_Xfer_Rev_HandShake_NEW_BLYNK > ESP_TM4C_Xfer_Rev_HandShake_NEW_BLYNK.ino`
7. Compile project (checkmark button)
8. Select port to flash to
    1. `Tools > Port: "xxx"`
    2. Select open port, assuming only one USB device is currently connected
9. Connect ESP8266 to ECE 445L ESP8266 flasher board (or similar UART-USB FTDI board)
10. Upload using flash button (rightward facing arrow).
