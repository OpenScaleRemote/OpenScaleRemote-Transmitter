# include "Arduino.h"
# include "Adafruit_GFX.h"
# include "Adafruit_ILI9341.h"

class Menu {
  private:
  #define BLACK    0x0000
  #define BLUE     0x001F
  #define RED      0xF800
  #define GREEN    0x07E0
  #define CYAN     0x07FF
  #define MAGENTA  0xF81F
  #define YELLOW   0xFFE0 
  #define WHITE    0xFFFF
  
  public:
  int mode = 0;
  int menu = 2;

  public:
    void setupTFT();
    void updateMenu();
    void executeAction();
    void action1();
    void action2();
    void action3();
    void action4();
    
};
