# include "Arduino.h"
# include "Adafruit_GFX.h"
# include "Adafruit_ILI9341.h"
# include "Adafruit_ILI9341_Menu.h"

# include "fonts\FreeSans18pt7b.h"
# include "fonts\FreeSans12pt7b.h"
# include "fonts\FreeSansBold12pt7b.h"
# include "fonts\FreeSansBold9pt7b.h"
# include "fonts\FreeSans9pt7b.h"

# define ROW_HEIGHT          35
# define ROWS                5
# define DATA_COLUMN         200

# define TFT_DC    28
# define TFT_CS    26
# define TFT_RST   27

# define UP_PIN     9
# define DOWN_PIN   10
# define ENTER_PIN  11

# define FONT_SMALL       FreeSans9pt7b        // font for menus
# define FONT_EDITTITLE   FreeSans18pt7b            // font for menus
# define FONT_ITEM        FreeSans12pt7b         // font for menus
# define FONT_TITLE       FreeSans18pt7b      // font for all headings

# define BLACK    0x0000
# define BLUE     0x001F
# define RED      0xF800
# define GREEN    0x07E0
# define CYAN     0x07FF
# define MAGENTA  0xF81F
# define YELLOW   0xFFE0 
# define WHITE    0xFFFF

#define DEBOUNCE    150

class Menu {
    //variables
  private:
    int MenuOption = 0;
    int MenuOption1 = 0;

    int ServoSignalOption1 = 0, ServoSignalOption2 = 0, ServoSignalOption3 = 0, ServoSignalOption4 = 0,
        ServoSignalOption5 = 0, ServoSignalOption6 = 0, ServoSignalOption7 = 0, ServoSignalOption8 = 0,
        ServoSignalOption9 = 0, ServoSignalOption10 = 0, ServoSignalOption11 = 0, ServoSignalOption12 = 0,
        ServoSignalOption13 = 0, ServoSignalOption14 = 0, ServoSignalOption15 = 0, ServoSignalOption16 = 0;

    uint16_t MENU_TEXT = BLACK;
    uint16_t MENU_BACKGROUND = WHITE;
    uint16_t MENU_HIGHLIGHTTEXT = BLACK;
    uint16_t MENU_HIGHLIGHT = YELLOW;
    uint16_t MENU_HIGHBORDER = BLACK;
    uint16_t MENU_SELECTTEXT = RED;
    uint16_t MENU_SELECT = GREEN;
    uint16_t MENU_SELECTBORDER = BLACK;
    uint16_t MENU_DISABLE = WHITE;
    uint16_t TITLE_TEXT = BLACK;
    uint16_t TITLE_BACK = BLUE;
    
  public:
    void setupTFT();
    void executeMenu();
    void updateMenu();
    void executeAction();
    void processMainMenu();
    void processServoSignalMenu();

  private:
};
