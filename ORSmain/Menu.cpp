# include "Menu.h"
# include "Arduino.h"
# include "Adafruit_GFX.h"
# include "Adafruit_ILI9341.h"
# include "SPI.h"

Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

ItemMenu MainMenu(&Display);
ItemMenu ServoSignalMenu(&Display);
//EditMenu Channel1(&Display);

void Menu::setupTFT() {  
  pinMode(UP_PIN, INPUT_PULLDOWN);
  pinMode(DOWN_PIN, INPUT_PULLDOWN);
  pinMode(ENTER_PIN, INPUT_PULLDOWN);
  delay(100);
  Display.begin();
  Display.setRotation(1);
  
  MainMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Main Menu", FONT_TITLE, FONT_TITLE);
  MenuOption1 = MainMenu.addNI("Adjust Servos");
  MainMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
  MainMenu.setTitleBarSize(0, 0, 320, 40);
  MainMenu.setTitleTextMargins(60, 30);
  MainMenu.setMenuBarMargins(0, 310, 15, 4);
  MainMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER);
  MainMenu.setItemTextMargins(10, 45, 5);

  ServoSignalMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Adjust Servos", FONT_TITLE, FONT_TITLE);
  ServoSignalOption1 = ServoSignalMenu.addNI("Channel 1");
  ServoSignalOption2 = ServoSignalMenu.addNI("Channel 2");
  ServoSignalOption3 = ServoSignalMenu.addNI("Channel 3");
  ServoSignalOption4 = ServoSignalMenu.addNI("Channel 4");
  ServoSignalOption5 = ServoSignalMenu.addNI("Channel 5");
  ServoSignalOption6 = ServoSignalMenu.addNI("Channel 6");
  ServoSignalOption7 = ServoSignalMenu.addNI("Channel 7");
  ServoSignalOption8 = ServoSignalMenu.addNI("Channel 8");
  ServoSignalOption9 = ServoSignalMenu.addNI("Channel 9");
  ServoSignalOption10 = ServoSignalMenu.addNI("Channel 10");
  ServoSignalOption11 = ServoSignalMenu.addNI("Channel 11");
  ServoSignalOption12 = ServoSignalMenu.addNI("Channel 12");
  ServoSignalOption13 = ServoSignalMenu.addNI("Channel 13");
  ServoSignalOption14 = ServoSignalMenu.addNI("Channel 14");
  ServoSignalOption15 = ServoSignalMenu.addNI("Channel 15");
  ServoSignalOption16 = ServoSignalMenu.addNI("Channel 16");
  ServoSignalMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
  ServoSignalMenu.setTitleBarSize(0, 0, 320, 40);
  ServoSignalMenu.setTitleTextMargins(60, 30);
  ServoSignalMenu.setMenuBarMargins(0, 310, 15, 4);
  ServoSignalMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER);
  ServoSignalMenu.setItemTextMargins(10, 45, 5);
  
  Display.fillScreen(MENU_BACKGROUND);
}

void Menu::executeMenu() {
  if(digitalRead(ENTER_PIN)) {
    delay(DEBOUNCE);
    while(digitalRead(ENTER_PIN));
    processMainMenu();
    Display.fillScreen(MENU_BACKGROUND);
  }
  Display.fillScreen(MENU_BACKGROUND);
  Display.setCursor(10, 30);
  Display.setFont(&FONT_TITLE);
  Display.setTextColor(ILI9341_RED, ILI9341_WHITE);
  Display.println(F("Homescreen"));
  Display.println(F("Platzhalter"));
  delay(100);
  Display.fillScreen(MENU_BACKGROUND);
  Display.setCursor(10, 30);
  Display.setFont(&FONT_TITLE);
  Display.setTextColor(ILI9341_BLUE, ILI9341_BLUE);
  Display.println(F("Homescreen"));
  Display.println(F("Platzhalter"));
  delay(100);
}

void Menu::updateMenu() {
}

void Menu::executeAction() {
}

  
void Menu::processMainMenu() {
  int MainMenuOption = 1;
  Display.fillScreen(MENU_BACKGROUND);
  MainMenu.draw();
  
  while (MainMenuOption != 0) {
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      MainMenu.MoveUp();
    }
    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(DOWN_PIN));
      MainMenu.MoveDown();
    }
    
    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));
      MainMenuOption = MainMenu.selectRow();
      
      if (MainMenuOption == MenuOption1) {
        processServoSignalMenu();
        Display.fillScreen(MENU_BACKGROUND);
        MainMenu.draw();
      }
    }
  }
}

void Menu::processServoSignalMenu() {
  int EditMenuOption = 1;
  Display.fillScreen(MENU_BACKGROUND);
  ServoSignalMenu.draw();

  while (EditMenuOption != 0) {
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      ServoSignalMenu.MoveUp();
    }
    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      ServoSignalMenu.MoveDown();
    }

    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));
      EditMenuOption = ServoSignalMenu.selectRow();

      if (EditMenuOption == ServoSignalOption1) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption2) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption3) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption4) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption5) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption6) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption7) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption8) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption9) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption10) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption11) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption12) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption13) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption14) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption15) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }

      if (EditMenuOption == ServoSignalOption16) {
        Display.fillScreen(MENU_BACKGROUND);
        ServoSignalMenu.draw();
      }
    }
  }
}
