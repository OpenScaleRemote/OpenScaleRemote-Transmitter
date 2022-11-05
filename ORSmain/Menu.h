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

# define UP_PIN     13
# define DOWN_PIN   14
# define ENTER_PIN  15

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
    int AllowColorMenu = 0;

    int MenuOption1 = 0, MenuOption2 = 0, MenuOption3 = 0, MenuOption4 = 0, MenuOption5 = 0;
    int MenuOption6 = 0, MenuOption7 = 0, MenuOption8 = 0, MenuOption9 = 0;

    int ColorOption1 = 0, ColorOption2 = 0, ColorOption3 = 0, ColorOption4 = 0, ColorOption5 = 0;
    int ColorOption6 = 0, ColorOption7 = 0, ColorOption8 = 0, ColorOption9 = 0, ColorOption10 = 0, ColorOption11 = 0;

    int OptionOption1 = 0, OptionOption2 = 0, OptionOption3 = 0, OptionOption4 = 0, OptionOption5 = 0;
    int OptionOption6 = 0, OptionOption7 = 0, OptionOption8 = 0, OptionOption9 = 0;

    int WirelessOption1 = 0, WirelessOption2 = 0, WirelessOption3 = 0, WirelessOption4 = 0, WirelessOption5 = 0;
    int WirelessOption6 = 0, WirelessOption7 = 0, WirelessOption8 = 0, WirelessOption9 = 0;
    int WirelessOption10 = 0, WirelessOption11 = 0, WirelessOption12 = 0, WirelessOption13 = 0;

    float Temp1Adj = 0.2, Temp2Adj = -.3, AlarmVal = 1;

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
    
    /*uint16_t MENU_TEXT = C_VALUES[1];
    uint16_t MENU_BACKGROUND = C_VALUES[0];
    uint16_t MENU_HIGHLIGHTTEXT = C_VALUES[1];
    uint16_t MENU_HIGHLIGHT = C_VALUES[21];
    uint16_t MENU_HIGHBORDER = C_VALUES[10];
    uint16_t MENU_SELECTTEXT = C_VALUES[0];
    uint16_t MENU_SELECT = C_VALUES[4];
    uint16_t MENU_SELECTBORDER = C_VALUES[37];
    uint16_t MENU_DISABLE = C_VALUES[2];
    uint16_t TITLE_TEXT = C_VALUES[13];
    uint16_t TITLE_BACK = C_VALUES[36];*/
    
  public:
    void setupTFT();
    void executeMenu();
    void processMainMenu();
    void processOptionMenu();
    void processColorMenu();
    void processWirelessMenu();

  private:
    const char *ReadoutItems[3] =   {"Absolute", "Deg F", "Deg C"};
    const char *RefreshItems[7] =   {"Off", "1 second", "2 seconds", "10 seconds", "30 seconds", "1 minute", "5 minutes"};
    const char *PrecisionItems[5] =   {"10", "0", "0.0", "0.00", "0.000"};
    const char *TuneItems[6] =   {"Slope/Offset", "Simple", "Linear", "2nd order ", "3rd order", "Log"};
    const char *OffOnItems[2] =   {"Off", "On"};
    const char *DataRateItems[7] =   {"300 baud", "1.2 kbd", "2.4 kbd", "4.8 kbd", "9.6 kbd", "19.2 kbd", "56 kbd"};
    const char *C_NAMES[46] = {"White", "Black", "Grey", "Blue", "Red", "Green", "Cyan", "Magenta",
                            "Yellow", "Teal", "Orange", "Pink", "Purple", "Lt Grey", "Lt Blue", "Lt Red",
                            "Lt Green", "Lt Cyan", "Lt Magenta", "Lt Yellow", "Lt Teal", "Lt Orange", "Lt Pink", "Lt Purple",
                            "Medium Grey", "Medium Blue", "Medium Red", "Medium Green", "Medium Cyan", "Medium Magenta", "Medium Yellow", "Medium Teal",
                            "Medium Orange", "Medium Pink", "Medium Purple", "Dk Grey", "Dk Blue", "Dk Red", "Dk Green", "Dk Cyan",
                            "Dk Magenta", "Dk Yellow", "Dk Teal", "Dk Orange", "Dk Pink", "Dk Purple"};
   const uint16_t  C_VALUES[46] = {  0XFFFF, 0X0000, 0XC618, 0X001F, 0XF800, 0X07E0, 0X07FF, 0XF81F, //7
           0XFFE0, 0X0438, 0XFD20, 0XF81F, 0X801F, 0XE71C, 0X73DF, 0XFBAE, //15
           0X7FEE, 0X77BF, 0XFBB7, 0XF7EE, 0X77FE, 0XFDEE, 0XFBBA, 0XD3BF, //23
           0X7BCF, 0X1016, 0XB000, 0X0584, 0X04B6, 0XB010, 0XAD80, 0X0594, //31
           0XB340, 0XB00E, 0X8816, 0X4A49, 0X0812, 0X9000, 0X04A3, 0X0372, //39
           0X900B, 0X94A0, 0X0452, 0X92E0, 0X9009, 0X8012 //45
        };
};
