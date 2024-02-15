//######################################
//########## OpenRemoteSender ##########
//######################################



//########## serial data ##########
//#define serialData



//########## pins - RFM96W ##########
/*
Set matching pins for your microcontroller.
*/

#define rfm95w_mosi 51
#define rfm95w_miso 50
#define rfm95w_sck 52
#define rfm95w_cs 53
#define rfm95w_reset 10
#define rfm95w_dio0 2



//########## pins - analog channels ##########
/*
Set matching pins for your microcontroller.
*/

#define pin_ch0 A0
#define pin_ch1 A1
#define pin_ch2 A2
#define pin_ch3 A3
#define pin_ch4 A4
#define pin_ch5 A5
#define pin_ch6 A6
#define pin_ch7 A7
#define pin_ch8 A8
#define pin_ch9 A9
#define pin_ch10 A10
#define pin_ch11 A11
#define pin_ch12 A12
#define pin_ch13 A13



//########## pins - digital channels ##########
/*
Set matching pins for your microcontroller.
*/

#define pin_ch14 22
#define pin_ch15 23
#define pin_ch16 24
#define pin_ch17 25
#define pin_ch18 26
#define pin_ch19 27
#define pin_ch20 28
#define pin_ch21 29
#define pin_ch22 30
#define pin_ch23 31
#define pin_ch24 32
#define pin_ch25 33
#define pin_ch26 34
#define pin_ch27 35
#define pin_ch28 36
#define pin_ch29 37



//########## moving average filter ##########
#define windowSize 5



//########## analog input channels ##########
/*
*/

//channel 0
  #define ch0_active
  #define ch0_fast
  //#define ch0_slow
  #define ch0_analogLinear

//channel 1
  #define ch1_active
  #define ch1_fast
  //#define ch1_slow
  #define ch1_analogLinear

//channel 2
  //#define ch2_active
  //#define ch2_fast
  //#define ch2_slow
  //#define ch2_analogLinear

//channel 3
  //#define ch3_active
  //#define ch3_fast
  //#define ch3_slow
  //#define ch3_analogLinear

//channel 4
  //#define ch4_active
  //#define ch4_fast
  //#define ch4_slow
  //#define ch4_analogLinear

//channel 5
  //#define ch5_active
  //#define ch5_fast
  //#define ch5_slow
  //#define ch5_analogLinear

//channel 6
  //#define ch6_active
  //#define ch6_fast
  //#define ch6_slow
  //#define ch6_analogLinear

//channel 7
  //#define ch7_active
  //#define ch7_fast
  //#define ch7_slow
  //#define ch7_analogLinear

//channel 8
  //#define ch8_active
  //#define ch8_fast
  //#define ch8_slow
  //#define ch8_analogLinear

//channel 9
  //#define ch9_active
  //#define ch9_fast
  //#define ch9_slow
  //#define ch9_analogLinear

//channel 10
  //#define ch10_active
  //#define ch10_fast
  //#define ch10_slow
  //#define ch10_analogLinear

//channel 11
  //#define ch11_active
  //#define ch11_fast
  //#define ch11_slow
  //#define ch11_analogLinear

//channel 12
  //#define ch12_active
  //#define ch12_fast
  //#define ch12_slow
  //#define ch12_analogLinear

//channel 13
  //#define ch13_active
  //#define ch13_fast
  //#define ch13_slow
  //#define ch13_analogLinear



//########## digital input channels ##########
/*
If you want to use the digital3Way functions on for example channel 14 then channel 15 must be inactive for the digital3Way function to work properly.
*/

//channel 14
  #define ch14_active
  //#define ch14_fast
  #define ch14_slow
  #define ch14_digital2Way
  //#define ch14_digital3Way

//channel 15
  //#define ch15_active
  //#define ch15_fast
  //#define ch15_slow
  //#define ch15_digital2Way

//channel 16
  //#define ch16_active
  //#define ch16_fast
  //#define ch16_slow
  //#define ch16_digital2Way
  //#define ch16_digital3Way

//channel 17
  //#define ch17_active
  //#define ch17_fast
  //#define ch17_slow
  //#define ch17_digital2Way

//channel 18
  //#define ch18_active
  //#define ch18_fast
  //#define ch18_slow
  //#define ch18_digital2Way
  //#define ch18_digital3Way

//channel 19
  //#define ch19_active
  //#define ch19_fast
  //#define ch19_slow
  //#define ch19_digital2Way

//channel 20
  //#define ch20_active
  //#define ch20_fast
  //#define ch20_slow
  //#define ch20_digital2Way
  //#define ch20_digital3Way

//channel 21
  //#define ch21_active
  //#define ch21_fast
  //#define ch21_slow
  //#define ch21_digital2Way

//channel 22
  //#define ch22_active
  //#define ch22_fast
  //#define ch22_slow
  //#define ch22_digital2Way

//channel 23
  //#define ch23_active
  //#define ch23_fast
  //#define ch23_slow
  //#define ch23_digital2Way

//channel 24
  //#define ch24_active
  //#define ch24_fast
  //#define ch24_slow
  //#define ch24_digital2Way

//channel 25
  //#define ch25_active
  //#define ch25_fast
  //#define ch25_slow
  //#define ch25_digital2Way

//channel 26
  //#define ch26_active
  //#define ch26_fast
  //#define ch26_slow
  //#define ch26_digital2Way

//channel 27
  //#define ch27_active
  //#define ch27_fast
  //#define ch27_slow
  //#define ch27_digital2Way

//channel 28
  //#define ch28_active
  //#define ch28_fast
  //#define ch28_slow
  //#define ch28_digital2Way

//channel 29
  //#define ch29_active
  //#define ch29_fast
  //#define ch29_slow
  //#define ch29_digital2Way