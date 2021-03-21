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

namespace NETserver
{
   public class Color
   {
      public int r;
      public int g;
      public int b;
      public int? a;
   }

   public class Startup
   {
      // This method gets called by the runtime. Use this method to add services to the container.
      // For more information on how to configure your application, visit https://go.microsoft.com/fwlink/?LinkID=398940
      public void ConfigureServices(IServiceCollection services)
      {
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
            endpoints.MapGet("/api", async context =>
            {
               Debug.WriteLine("Got api2");
               await context.Response.WriteAsync(@"{""poop"":"":)""}");
            });
            endpoints.MapPost("/api/changecolor", async context =>
            {
               // TODO protobuffer
            });
         });
      }
   }
}
