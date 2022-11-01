# include "Menu.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(26, 28, 27);

void Menu::constTFT() {
  tft.begin();
  pinMode(13, INPUT_PULLDOWN);
  pinMode(14, INPUT_PULLDOWN);
  pinMode(15, INPUT_PULLDOWN);
  tft.setCursor(0,0);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
}

void Menu::updateMenu() {
  switch(menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(">MenuItem1");
      tft.println(" MenuItem2");
      tft.println(" MenuItem3");
      tft.println(" MenuItem4");
      break;
    case 2:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" MenuItem1");
      tft.println(">MenuItem2");
      tft.println(" MenuItem3");
      tft.println(" MenuItem4");
      break;
    case 3:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" MenuItem1");
      tft.println(" MenuItem2");
      tft.println(">MenuItem3");
      tft.println(" MenuItem4");
      break;
    case 4:
      tft.fillScreen(BLACK);
      tft.setCursor(0,0);
      tft.println(" MenuItem1");
      tft.println(" MenuItem2");
      tft.println(" MenuItem3");
      tft.println(">MenuItem4");
      break;
    case 5:
      menu = 4;
      break;
  }
}
