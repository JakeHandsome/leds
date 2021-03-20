import bodyParser from "body-parser";
import express from "express";
import { exec as execNotAPromiseSoItsDumb } from "child_process";
import { promisify } from "util";
import { join } from "path";
const exec = promisify(execNotAPromiseSoItsDumb);
interface changecolor {
   color: RGBColor;
}

interface RGBColor {
   a?: number;
   b: number;
   g: number;
   r: number;
}

const main = async () => {
   const app = express();
   app.use(express.static(join(__dirname, "..", "..", "ui", "build")));
   app.use(express.static("public"));
   var jsonParser = bodyParser.json();
   app.get("/api", (_, res) => {
      res.json({ poop: ":)" });
   });
   app.post("/api/changecolor", jsonParser, (req, res) => {
      const data: changecolor = req.body;
      console.log(data.color);
      const color: RGBColor = data.color;

      exec(`python3 ../pytest/test.py ${color.r} ${color.g} ${color.b}`)
         .then(() => {
            res.statusCode = 200;
         })
         .catch(() => {
            res.statusCode = 500;
         });
   });
   app.listen(8000, () => {
      console.log("server.started on localhost:8000");
   });
};

main().catch((err) => {
   console.error(err);
});
