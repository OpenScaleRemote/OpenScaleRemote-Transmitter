# include "Menu.h"
# include "Arduino.h"
# include "Adafruit_GFX.h"
# include "Adafruit_ILI9341.h"

Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

ItemMenu MainMenu(&Display);
EditMenu OptionMenu(&Display);
EditMenu ColorMenu(&Display);
EditMenu WirelessMenu(&Display);


void Menu::setupTFT() {  
  pinMode(UP_PIN, INPUT_PULLDOWN);
  pinMode(DOWN_PIN, INPUT_PULLDOWN);
  pinMode(ENTER_PIN, INPUT_PULLDOWN);
  Display.begin();
  Display.setRotation(1);
  
  MainMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Main Menu", FONT_TITLE, FONT_TITLE);
  MenuOption1 = MainMenu.addNI("Options");
  MenuOption2 = MainMenu.addNI("Colors");
  MenuOption3 = MainMenu.addNI("Wireless");
  MenuOption4 = MainMenu.addNI("Servos");
  MenuOption5 = MainMenu.addNI("Motors");
  MenuOption6 = MainMenu.addNI("Sensors");
  MainMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
  MainMenu.setTitleBarSize(0, 0, 320, 40);
  MainMenu.setTitleTextMargins(60, 30);
  MainMenu.setMenuBarMargins(0, 310, 15, 4);
  MainMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER);
  MainMenu.setItemTextMargins(10, 45, 5);

  OptionMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT, DATA_COLUMN, ROW_HEIGHT, ROWS, "Option Menu", FONT_ITEM, FONT_TITLE);
  OptionOption1 = OptionMenu.addNI("Colors", AllowColorMenu, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  OptionOption2 = OptionMenu.addNI("Temp Adj.", Temp2Adj, -1.0, 1.0 , .05, 2, NULL);
  OptionOption3 = OptionMenu.addNI("Readout", 2, 0, sizeof(ReadoutItems) / sizeof(ReadoutItems[0]), 1, 0, ReadoutItems);
  OptionOption4 = OptionMenu.addNI("Tune", 0, 0, 20 , 1, 0, NULL);
  OptionOption5 = OptionMenu.addNI("Alarm", AlarmVal, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  OptionOption6 = OptionMenu.addNI("Precision", 0, 0, sizeof(PrecisionItems) / sizeof(PrecisionItems[0]), 1, 0, PrecisionItems);
  OptionOption7 = OptionMenu.addNI("Refresh", 0, 0.0, sizeof(RefreshItems) / sizeof(RefreshItems[0]), 1, 0, RefreshItems);
  OptionMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
  OptionMenu.setTitleBarSize(0, 0, 320, 40);
  OptionMenu.setTitleTextMargins(60, 30);
  OptionMenu.setItemTextMargins(7, 25, 10);
  OptionMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

  ColorMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT, 170, 30, 6, "Color Menu", FONT_ITEM, FONT_TITLE);
  ColorOption1 = ColorMenu.addNI("Menu Text", 1, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption2 = ColorMenu.addNI("Background", 0, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption3 = ColorMenu.addNI("Selector Text", 1, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption4 = ColorMenu.addNI("Selector Bar", 21, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption5 = ColorMenu.addNI("Selector Border", 10, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption6 = ColorMenu.addNI("Edit Text", 0, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption7 = ColorMenu.addNI("Edit Bar", 4, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption8 = ColorMenu.addNI("Edit Border", 37, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption9 = ColorMenu.addNI("Disable Text", 2, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]) , 1, 0, C_NAMES);
  ColorOption10 = ColorMenu.addNI("Banner Text", 13, 0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorOption11 = ColorMenu.addNI("Banner Fill", 36, 0.0, sizeof(C_NAMES) / sizeof(C_NAMES[0]), 1, 0, C_NAMES);
  ColorMenu.setTitleTextMargins(50, 30);
  ColorMenu.setItemTextMargins(16, 25, 5);
  ColorMenu.setMenuBarMargins(10, 305, 4, 2);

  WirelessMenu.init(MENU_TEXT, MENU_BACKGROUND, ILI9341_WHITE, ILI9341_BLUE, MENU_SELECTTEXT, MENU_SELECT, DATA_COLUMN, 20, 9, "Wireless Menu", FONT_SMALL, FONT_ITEM);
  WirelessOption1 = WirelessMenu.addNI("Channel", 0, 0, 63 , 1, 0);
  WirelessOption2 = WirelessMenu.addNI("Address", 0, 0, 255, 1, 0);
  WirelessOption3 = WirelessMenu.addNI("Data rate", 2, 0, sizeof(DataRateItems) / sizeof(DataRateItems[0]), 1, 0, DataRateItems);
  WirelessOption4 = WirelessMenu.addNI("Air rate", 2, 0, sizeof(DataRateItems) / sizeof(DataRateItems[0]), 1, 0, DataRateItems);
  WirelessOption5 = WirelessMenu.addNI("Error checking", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessOption6 = WirelessMenu.addNI("Power", 0, 0, 100, 10, 0);
  WirelessOption7 = WirelessMenu.addNI("FEC", 0, 0, 100, 10, 0);
  WirelessOption8 = WirelessMenu.addNI("Callback", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessOption9 = WirelessMenu.addNI("Use buffer", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessOption10 = WirelessMenu.addNI("Open drain", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessOption11 = WirelessMenu.addNI("Use pullups", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessOption12 = WirelessMenu.addNI("Antenna height", 0, 0, 8, 1, 0);
  WirelessOption13 = WirelessMenu.addNI("Broadband", 1, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
  WirelessMenu.setTitleTextMargins(50, 30);
  WirelessMenu.setItemTextMargins(16, 15, 5);
  WirelessMenu.setMenuBarMargins(10, 305, 4, 2);
  WirelessMenu.setIncrementDelay(150);

  //processMainMenu();
  //Display.fillScreen(MENU_BACKGROUND);
}

void Menu::executeMenu() {
  if(digitalRead(ENTER_PIN)) {
    delay(DEBOUNCE);
    while(digitalRead(ENTER_PIN));
    processMainMenu();
    //Display.fillScreen(MENU_BACKGROUND);
  }
  Display.fillScreen(MENU_BACKGROUND);
  Display.setCursor(10, 100);
  Display.setFont(&FONT_TITLE);
  Display.setTextColor(ILI9341_RED, ILI9341_WHITE);
  Display.print(F("Done"));
  delay(5);
  Display.setCursor(10, 100);
  Display.setFont(&FONT_TITLE);
  Display.setTextColor(ILI9341_BLUE, ILI9341_BLUE);
  Display.print(F("Done"));
  delay(5);
}

void Menu::processMainMenu() {
    // set an inital flag that will be used to store what menu item the user exited on
  int MainMenuOption = 1;

  // blank out the screen
  Display.fillScreen(MENU_BACKGROUND);

  // draw the main menu
  MainMenu.draw();

  // run the processing loop until user move selector to title bar (which becomes exit, i.e. 0 return val)
  // and selectes it
  // note menu code can return - 1 for errors so run unitl non zero

  while (MainMenuOption != 0) {

    // attempt to debouce these darn things...
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      MainMenu.MoveUp();
    }
    
    // attempt to debouce these darn things...
    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(DOWN_PIN));
      MainMenu.MoveDown();
    }

    // but wait...the user pressed the button on the encoder
    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));

      // get the row the selector is on
      MainMenuOption = MainMenu.selectRow();

      // here is where you process accordingly
      // remember on pressing button on title bar 0 is returned and will exit the loop

      if (MainMenuOption == MenuOption1) {
        // item 1 was the Option menu
        processOptionMenu();
        // when done processing that menu, return here
        // clear display and redraw this main menu
        Display.fillScreen(MENU_BACKGROUND);
        MainMenu.draw();
      }
      if (MainMenuOption == MenuOption2) {
        processColorMenu();
        Display.fillScreen(MENU_BACKGROUND);
        MainMenu.draw();
      }
      if (MainMenuOption == MenuOption3) {
        processWirelessMenu();
        Display.fillScreen(MENU_BACKGROUND);
        MainMenu.draw();
      }

      if (MainMenuOption == MenuOption4) {
        //ImTooLazyToWriteAnotherExampe();
        Display.fillScreen(MENU_BACKGROUND);
        MainMenu.draw();
      }

    }
  }

  // at this point MenuOption better be 0...
  
}

void Menu::processOptionMenu() {
  // the entire menu processing are basically 3 calls
  // YourMenu.MoveUp();
  // YourMenu.MoveDown();
  // EditMenuOption = YourMenu.selectRow();

  // set an inital flag that will be used to store what menu item the user exited on
  int EditMenuOption = 1;

  // blank out the screen
  Display.fillScreen(MENU_BACKGROUND);

  // draw the main menu
  OptionMenu.draw();

  // run the processing loop until user move selector to title bar (which becomes exit)
  // and selectes it
  while (EditMenuOption != 0) {

    // attempt to debouce these darn things...
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      OptionMenu.MoveUp();
    }

    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      OptionMenu.MoveDown();
    }

    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));
      EditMenuOption = OptionMenu.selectRow();


      // this next section is purely optional and shows how data change can be used
      // the EditMenu object type is special cased where if you select a menu item
      // the library consideres that a desire to start editing the item
      // the menu bar color changes and any MoveUp / MoveDown will then be directed
      // to editing the item value itself
      // once user Selects the selected row, the library will consider editign done
      // and restore menu selection with MoveUp / MoveDown
      // watch the YouTube video for a demo
      // to modify other values
      if (EditMenuOption == OptionOption5) { // budget item
        if (OptionMenu.value[OptionOption5] == 0) {
          OptionMenu.disable(OptionOption4);
          OptionMenu.setItemText(OptionOption4, "Tune (Alarm OFF)");
          OptionMenu.drawRow(OptionOption4);
        }
        else {
          OptionMenu.enable(OptionOption4);
          OptionMenu.setItemText(OptionOption4, "Tune");
          OptionMenu.drawRow(OptionOption4);
        }
      }
    }
  }

  // user must have pressed the encorder select button while on the title bar (which returns 0)
  // hence exiting the loop
  // now you can process / store / display the menu selections
  // remember this is from the EditMenu and has associated value property with each menu item
  Serial.println("Option Menu Selections ");
  Serial.println("______________________________");
  Serial.print("Color Adj "); Serial.println(OptionMenu.value[OptionOption1]);
  Serial.print("Temp2 Adj "); Serial.println(OptionMenu.value[OptionOption2]);
  Serial.print("Readout "); Serial.println(ReadoutItems[(int)OptionMenu.value[OptionOption3]]);
  Serial.print("Tune "); Serial.println(TuneItems[(int)OptionMenu.value[OptionOption4]]);
  Serial.print("Alarm "); Serial.println(OffOnItems[(int)OptionMenu.value[OptionOption5]]);
  Serial.print("Precision "); Serial.println(PrecisionItems[(int)OptionMenu.value[OptionOption6]]);
  Serial.print("Refresh "); Serial.println(OptionMenu.value[OptionOption7]);

  // an example of how to set other menu values based on selection here
  // remember all menu values passed in or returned are floats
  // so recast to int if you need to
  AllowColorMenu = (int) OptionMenu.value[OptionOption1];

  if (AllowColorMenu == 0) {
    MainMenu.disable(MenuOption2);
  }
  else {
    MainMenu.enable(MenuOption2);
  }
}

void Menu::processColorMenu() {

  // the entire menu processing are basically 3 calls
  // YourMenu.MoveUp();
  // YourMenu.MoveDown();
  // EditMenuOption = YourMenu.selectRow();


  // set an inital flag that will be used to store what menu item the user exited on
  int EditMenuOption = 1;

  // blank out the screen
  Display.fillScreen(MENU_BACKGROUND);

  // draw the main menu
  ColorMenu.draw();

  // run the processing loop until user move selector to title bar (which becomes exit)
  // and selectes it
  while (EditMenuOption != 0) {
    
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      ColorMenu.MoveUp();
    }

    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      ColorMenu.MoveDown();
    }

    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));
      EditMenuOption = ColorMenu.selectRow();

    }
  }

  // out of menu now time for processing

  // set global back color
  Serial.print("back color");

  Serial.println(C_VALUES[ (int) ColorMenu.value[ColorOption2]]);


  MENU_BACKGROUND = C_VALUES[ (int) ColorMenu.value[ColorOption2]];

  // set Option menu colors

  MainMenu.SetAllColors(C_VALUES[ (int) ColorMenu.value[ColorOption1]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption2]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption3]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption4]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption8]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption9]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption10]],
                        C_VALUES[ (int) ColorMenu.value[ColorOption11]]);

  OptionMenu.SetAllColors(C_VALUES[ (int) ColorMenu.value[ColorOption1]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption2]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption3]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption4]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption5]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption6]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption7]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption8]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption9]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption10]],
                          C_VALUES[ (int) ColorMenu.value[ColorOption11]]);
  // set color menu colors
  ColorMenu.SetAllColors(C_VALUES[ (int) ColorMenu.value[ColorOption1]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption2]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption3]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption4]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption5]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption6]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption7]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption8]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption9]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption10]],
                         C_VALUES[ (int) ColorMenu.value[ColorOption11]]);
  // set color menu colors
  WirelessMenu.SetAllColors(C_VALUES[ (int) ColorMenu.value[ColorOption1]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption2]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption3]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption4]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption5]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption6]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption7]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption8]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption9]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption10]],
                            C_VALUES[ (int) ColorMenu.value[ColorOption11]]);

}

void Menu::processWirelessMenu() {

  int EditMenuOption = 1;

  Display.fillScreen(MENU_BACKGROUND);

  WirelessMenu.draw();

  while (EditMenuOption != 0) {
    if (digitalRead(UP_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      WirelessMenu.MoveUp();
    }

    if (digitalRead(DOWN_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(UP_PIN));
      WirelessMenu.MoveDown();
    }

    if (digitalRead(ENTER_PIN)) {
      delay(DEBOUNCE);
      while(digitalRead(ENTER_PIN));
      EditMenuOption = WirelessMenu.selectRow();

    }
  }
}
