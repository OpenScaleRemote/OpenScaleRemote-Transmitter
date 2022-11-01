# include "Menu.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(26, 28, 27);

void Menu::setupTFT() {
  tft.begin();
  tft.setRotation(1);
  tft.setCursor(0,0);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
}

void Menu::updateMenu() {
  switch(menu) {
    case 0:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println("Ubersicht");
      break;
      
    case 1:
      menu = 2;
      break;
      
    case 2:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(">back");
      tft.println(" MenuItem2");
      tft.println(" MenuItem3");
      tft.println(" MenuItem4");
      break;
      
    case 3:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" back");
      tft.println(">MenuItem2");
      tft.println(" MenuItem3");
      tft.println(" MenuItem4");
      break;
      
    case 4:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" back");
      tft.println(" MenuItem2");
      tft.println(">MenuItem3");
      tft.println(" MenuItem4");
      break;
      
    case 5:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" back");
      tft.println(" MenuItem2");
      tft.println(" MenuItem3");
      tft.println(">MenuItem4");
      break;
      
    case 6:
      menu = 5;
      break;
  }
}

void Menu::executeAction() {
  switch(menu) {
    case 2:
      action1();
      break;
    case 3:
      action2();
      break;
    case 4:
      action3();
      break;
    case 5:
      action4();
      break;
  }
}

void Menu::action1() {
  mode = 0;
  menu = 0;
}

void Menu::action2() {
  
}

void Menu::action3() {
  
}

void Menu::action4() {
  
}
