

#include <Arduino.h>
#include <U8g2lib.h>
#include "screen.h"


#define base U8G2_SSD1306_128X64_NONAME_F_HW_I2C

Screen::Screen() : base(U8G2_R2, RST_OLED, SCL_OLED, SDA_OLED) {}
void Screen::begin()
{
   base::begin();
   setFont(u8g2_font_profont10_tf);
   log.begin((class U8G2 &)*this, TERMINAL_WIDTH, TERMINAL_HEIGHT, buf);

   log.println("Screen init");
}

Screen &Screen::GetInstance()
{
   static Screen s;
   return s;
}

void Screen::clearLog()
{
   log.print('\f');
}
