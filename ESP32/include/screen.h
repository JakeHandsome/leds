#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <U8g2lib.h>

#define TERMINAL_WIDTH 25
#define TERMINAL_HEIGHT 8

class Screen : public U8G2_SSD1306_128X64_NONAME_F_HW_I2C
{
private:
   uint8_t buf[TERMINAL_HEIGHT * TERMINAL_WIDTH];
   Screen();
   // Stop compiler generating methods to copy object
   Screen(Screen const &copy);
   Screen &operator=(Screen const &copy);
public:
   U8G2LOG log;
   void begin();
   static Screen &GetInstance(void);
   void clearLog(void);
};
#endif
