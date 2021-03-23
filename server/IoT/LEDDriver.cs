using System.Data;
using System.Threading;
using System;
#if LINUX_ARM
using System.Device.Spi;
using Iot.Device.Ws28xx;
#endif
using System.Drawing;

namespace IoT
{
   public class LEDDriver
   {
#if LINUX_ARM
      private Ws28xx lights;
      private SpiDevice spi;
#endif
      public Color CurrentColor { private set; get; }
      public int Count { private set; get; }
      public LEDDriver(int count)
      {
#if LINUX_ARM
         Count = count;
         var settings = new SpiConnectionSettings(0, 0)
         {
            ClockFrequency = 2_400_000,
            Mode = SpiMode.Mode0,
            DataBitLength = 8
         };
         spi = SpiDevice.Create(settings);
         lights = new Ws2812b(spi, Count);
#endif
         CurrentColor = Color.Black;
      }
      public void SetAllLights(Color color)
      {
         Console.WriteLine($"Setting All lights to {color.ToString()}");
         CurrentColor = color;
         Console.WriteLine($"Current color is {CurrentColor.ToString()}");
#if LINUX_ARM
         var image = lights.Image;
         for (var i = 0; i < Count; i++)
         {
            image.SetPixel(i, 0, color);
         }
         lights.Update();
#endif
      }
   }
}
