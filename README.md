# OpenScaleRemote Transmitter

OpenScaleRemote is a open source platform for building your own RC Transmitter and Reciever. The Transmitter can be based of lots of different boards, including various arduino, esp32 and teensy boards.

## MCU

The software of the OpenScaleRemote has support for the following boards already implemented. But you can also use any other Board with support for SPI, I2C, GPIO based interrupts and a sufficient number of analog and digital input pins.  
Due to the lack of GPIO based interrupts the RP2040 running the arduino core by earlphilflower is not supported.

Board function | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
pin_led | LED_BUILTIN | 2 | not set yet

## Wireless communication

The OpenScaleRemote uses an RFM95W LoRa module build by HopeRF. You can choose between different types of RFM95W boards. We recommend the [adafruit version](https://www.adafruit.com/product/3072), but any other board can be used too. Just make sure that it matches the logic voltage of your mcu or use a SPI capable logic level voltage converter.

RFM95W | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
rfm95w_mosi | 51 | 23 | not set yet
rfm95w_miso | 50 | 19 | not set yet
rfm95w_sck | 52 | 18 | not set yet
rfm95w_cs | 53 | 5 | not set yet
rfm95w_reset | 10 | 14 | not set yet
rfm95w_dio0 | 2 | 2 | not set yet

## Display and UI

The UI of the OpenScaleRemote Transmitter is based on SquareLineUI running on a [2,8 inch ILI9488 based tft witch capacitive touch](https://www.az-delivery.de/en/products/2-8-zoll-lcd-tft-touch-display). It uses the TFT_eSPI display library by Bodmer and the lvgl grafics library by kisvegabor. Make sure that the tft matches the logic voltage of your mcu or use a SPI capable logic level voltage converter.
Due too the lack of SRAM on the Arduino MEGA 2560, the SquareLineUI based UI is not available for this mcu.

ILI9488 TFT + Touch | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
lcd_mosi | not available | 23 | not set yet
lcd_miso | not available | 19 | not set yet
lcd_sck | not available | 18 | not set yet
lcd_cs | not available | 17 | not set yet
lcd_reset | not available | 16 | not set yet
lcd_dc | not available | 12 | not set yet
touch_mosi | not available | 23 | not set yet
touch_miso | not available | 19 | not set yet
touch_sck | not available | 18 | not set yet
touch_cs | not available | 4 | not set yet

## Model data storage

The OpenScaleRemote Transmitter uses a SD-Card to store model spezific data such as name, servo directions and servo limits. Any SD or MicroSD card module can be used here.

SD-Card | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
sd_mosi | 51 | 23 | not set yet
sd_miso | 50 | 19 | not set yet
sd_sck | 52 | 18 | not set yet
sc_cs | not set yet | 13 | not set yet

## Analog and digital input channels

Input channels | Arduino MEGA 2560 | ESP32WROOM32 | Teensy4.1
-------- | -------- | -------- | --------
pin_ch0 | A0 | 36 | not set yet
pin_ch1 | A1 | 39 | not set yet
pin_ch2 | A2 | 34 | not set yet
pin_ch3 | A3 | 35 | not set yet
pin_ch4 | A4 | 32 | not set yet
pin_ch5 | A5 | 33 | not set yet
pin_ch6 | A6 | 25 | not set yet
pin_ch7 | A7 | 26 | not set yet
pin_ch8 | A8 | 27 | not set yet
pin_ch9 | A9 | 15 | not set yet
pin_ch10 | A10 | not available | not set yet
pin_ch11 | A11 | not available | not set yet
pin_ch12 | A12 | not available | not set yet
pin_ch13 | A13 | not available | not set yet
pin_ch14 | 22 | not set yet | not set yet
pin_ch15 | 23 | not set yet | not set yet
pin_ch16 | 24 | not set yet | not set yet
pin_ch17 | 25 | not set yet | not set yet
pin_ch18 | 26 | not set yet | not set yet
pin_ch19 | 27 | not set yet | not set yet
pin_ch20 | 28 | not set yet | not set yet
pin_ch21 | 29 | not set yet | not set yet
pin_ch22 | 30 | not set yet | not set yet
pin_ch23 | 31 | not set yet | not set yet
pin_ch24 | 32 | not set yet | not set yet
pin_ch25 | 33 | not set yet | not set yet
pin_ch26 | 34 | not set yet | not set yet
pin_ch27 | 35 | not set yet | not set yet
pin_ch28 | 36 | not set yet | not set yet
pin_ch29 | 37 | not set yet | not set yet
