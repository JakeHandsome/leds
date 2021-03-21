using System.Threading;
using System;
using System.Device.Spi;
using Iot.Device.Ws28xx;
using System.Drawing;

namespace IoT
{
   public class LEDDriver
   {
      private Ws28xx lights;
      private SpiDevice spi;
      public int Count { private set; get; }
      public LEDDriver(int count)
      {
         Count = count;
         var settings = new SpiConnectionSettings(0, 0)
         {
            ClockFrequency = 2_400_000,
            Mode = SpiMode.Mode0,
            DataBitLength = 8
         };
         spi = SpiDevice.Create(settings);
         lights = new Ws2812b(spi, Count);
      }
      public void SetAllLights(Color color)
      {
         var image = lights.Image;
         for (var i = 0; i < Count; i++)
         {
            image.SetPixel(i, 0, color);
         }
         lights.Update();
      }
   }
}
