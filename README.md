# OpenScaleRemote Transmitter

OpenScaleRemote is a open source platform for building your own RC Transmitter and Reciever. The Transmitter can be based of lots of different boards, including various arduino, esp32 and teensy boards.

## MCU

The software of the OpenScaleRemote has support for the following boards already implemented. But you can also use any other Board with support for SPI, I2C, GPIO based interrupts and a sufficient number of analog and digital input pins.  
Due to the lack of GPIO based interrupts the RP2040 running the arduino core by earlphilflower is not supported.

Board function | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
pin_led | LED_BUILTIN | 2 | not defined
bat_voltage | not defined | 15 | not defined

## Wireless communication

The OpenScaleRemote uses an [RFM95W LoRa module](https://www.hoperf.com/modules/lora/RFM95W.html) build by HopeRF running the [LoRa](https://github.com/sandeepmistry/arduino-LoRa) library by Sandeep Mistry. You can choose between different types of RFM95W boards. We recommend the [adafruit version](https://www.adafruit.com/product/3072), but any other board can be used too. Just make sure that it matches the logic voltage of your mcu or use a SPI capable logic level voltage converter.

RFM95W | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
rfm95w_mosi | 51 | 23 | not defined
rfm95w_miso | 50 | 19 | not defined
rfm95w_sck | 52 | 18 | not defined
rfm95w_cs | 53 | 5 | not defined
rfm95w_reset | 10 | 14 | not defined
rfm95w_dio0 | 2 | 2 | not defined

## Display and UI

The UI of the OpenScaleRemote Transmitter is build with [SquareLine Studio](https://squareline.io/) running on a [2,8 inch ILI9488](https://www.az-delivery.de/en/products/2-8-zoll-lcd-tft-touch-display) based tft witch capacitive touch. It uses the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) display library by Bodmer and the [lvgl](https://lvgl.io/) grafics library by kisvegabor. Make sure that the tft matches the logic voltage of your mcu or use a SPI capable logic level voltage converter.
Due too the lack of SRAM on the Arduino MEGA 2560, the SquareLine Studio based UI is not available for this mcu.

ILI9488 TFT + Touch | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
lcd_mosi | 51 | 23 | not defined
lcd_miso | 50 | 19 | not defined
lcd_sck | 52 | 18 | not defined
lcd_cs | 48 | 17 | not defined
lcd_reset | 49 | 16 | not defined
lcd_dc | 46 | 12 | not defined
touch_mosi | 51 | 23 | not defined
touch_miso | 50 | 19 | not defined
touch_sck | 52 | 18 | not defined
touch_cs | 47 | 4 | not defined

## Model data storage

The OpenScaleRemote Transmitter uses a SD-Card to store model spezific data such as name, servo directions and servo limits. Any SD or MicroSD card module can be used here.

SD-Card | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
sd_mosi | 51 | 23 | not defined
sd_miso | 50 | 19 | not defined
sd_sck | 52 | 18 | not defined
sc_cs | 44 | 13 | not defined

## Analog and digital input channels

Input channels | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
pin_ch0 | A0 | 36 | not defined
pin_ch1 | A1 | 39 | not defined
pin_ch2 | A2 | 34 | not defined
pin_ch3 | A3 | 35 | not defined
pin_ch4 | A4 | 32 | not defined
pin_ch5 | A5 | 33 | not defined
pin_ch6 | A6 | 25 | not defined
pin_ch7 | A7 | 26 | not defined
pin_ch8 | A8 | 27 | not defined
pin_ch9 | A9 | not available | not defined
pin_ch10 | A10 | not available | not defined
pin_ch11 | A11 | not available | not defined
pin_ch12 | A12 | not available | not defined
pin_ch13 | A13 | not available | not defined
pin_ch14 | 22 | not defined | not defined
pin_ch15 | 23 | not defined | not defined
pin_ch16 | 24 | not defined | not defined
pin_ch17 | 25 | not defined | not defined
pin_ch18 | 26 | not defined | not defined
pin_ch19 | 27 | not defined | not defined
pin_ch20 | 28 | not defined | not defined
pin_ch21 | 29 | not defined | not defined
pin_ch22 | 30 | not defined | not defined
pin_ch23 | 31 | not defined | not defined
pin_ch24 | 32 | not defined | not defined
pin_ch25 | 33 | not defined | not defined
pin_ch26 | 34 | not defined | not defined
pin_ch27 | 35 | not defined | not defined
pin_ch28 | 36 | not defined | not defined
pin_ch29 | 37 | not defined | not defined
