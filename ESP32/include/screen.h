#ifndef SCREEN_H
#define SCREEN_H
#include <Arduino.h>
#include <U8g2lib.h>

#define TERMINAL_WIDTH 25
#define TERMINAL_HEIGHT 8

#define base U8G2_SSD1306_128X64_NONAME_F_HW_I2C
class Screen : public base
{
   public:
      U8G2LOG log;
      uint8_t buf[TERMINAL_HEIGHT * TERMINAL_WIDTH];
      int LineHeight;
      int MaxWidth;
      int MaxHeight;
      int MaxLines;
      Screen() : base(U8G2_R2, RST_OLED, SCL_OLED, SDA_OLED)
      {
      }
      void begin()
      {
         base::begin();
         setFont(u8g2_font_profont10_tf);
         LineHeight = getFontAscent() - getFontDescent();
         MaxHeight = getHeight();
         MaxWidth = getWidth();
         log.begin((class U8G2&) *this, TERMINAL_WIDTH, TERMINAL_HEIGHT, buf);

         log.println("Screen init");
      }
};
#undef base
#endif
