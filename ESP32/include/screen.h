#ifndef SCREEN_H
#define SCREEN_H
#include <Arduino.h>
#include <U8g2lib.h>

#define TERMINAL_WIDTH 25
#define TERMINAL_HEIGHT 8

#define base U8G2_SSD1306_128X64_NONAME_F_HW_I2C
class Screen : public base
{
private:
   uint8_t buf[TERMINAL_HEIGHT * TERMINAL_WIDTH];
   Screen() : base(U8G2_R2, RST_OLED, SCL_OLED, SDA_OLED) {}
   // Stop compiler generating methods to copy object
   Screen(Screen const &copy);
   Screen &operator=(Screen const &copy);

public:
   U8G2LOG log;
   void begin()
   {
      base::begin();
      setFont(u8g2_font_profont10_tf);
      log.begin((class U8G2 &)*this, TERMINAL_WIDTH, TERMINAL_HEIGHT, buf);

      log.println("Screen init");
   }
   static Screen &GetInstance()
   {
      static Screen s;
      return s;
   }
   void clearLog()
   {
      log.print('\f');
   }
};
#undef base
#endif // SCREEN_H
