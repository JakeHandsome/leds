using System.Drawing;
using System.Reflection;
using System.Diagnostics;
using System.Diagnostics.SymbolStore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using System.IO;
using Google.Protobuf;
using static NETServer.Protobuf.Color;
using IoT;
using System.Text;
using Microsoft.AspNetCore.Server.Kestrel.Core;
using Microsoft.Extensions.Primitives;

namespace NETserver
{
   public class Startup
   {
      private static LEDDriver LEDDriver;
      static Startup()
      {
         LEDDriver = new LEDDriver(150);
      }
      // This method gets called by the runtime. Use this method to add services to the container.
      // For more information on how to configure your application, visit https://go.microsoft.com/fwlink/?LinkID=398940
      public void ConfigureServices(IServiceCollection services)
      {
         services.Configure<KestrelServerOptions>(options =>
         {
            options.AllowSynchronousIO = true;
         });
      }

      // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
      public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
      {
         if (env.IsDevelopment())
         {
            app.UseDeveloperExceptionPage();
         }

         app.UseRouting();
         app.UseDefaultFiles();
         // Serve wwwroot/dist as a root
         app.UseStaticFiles();


         app.UseEndpoints(endpoints =>
         {
            endpoints.MapGet("/api/currentcolor/", async context =>
             {
                var response = context.Response;
                response.ContentType = "application/protobuf";
                NETServer.Protobuf.Color color = new NETServer.Protobuf.Color()
                {
                   R = LEDDriver.CurrentColor.R,
                   G = LEDDriver.CurrentColor.G,
                   B = LEDDriver.CurrentColor.B
                };
                await response.Body.WriteAsync(color.ToByteArray());
             });
            endpoints.MapPost("/api/changecolor/", async context =>
            {
               var buffer = await context.Request.BodyReader.ReadAsync();
               NETServer.Protobuf.Color color = NETServer.Protobuf.Color.Parser.ParseFrom(buffer.Buffer);
               LEDDriver.SetAllLights(Color.FromArgb(red: color.R, blue: color.B, green: color.G));
               context.Request.BodyReader.AdvanceTo(buffer.Buffer.Start, buffer.Buffer.End);
            });
         });
      }
   }
}
