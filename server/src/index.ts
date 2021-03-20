import bodyParser from "body-parser";
import express from "express";
import { exec as execNotAPromiseSoItsDumb } from "child_process";
import { promisify } from "util";
const exec = promisify(execNotAPromiseSoItsDumb);
interface changecolor {
   color: string;
}

interface Color {
   Red: number;
   Green: number;
   Blue: number;
}

const colorToInts = (color: string): Color => {
   return {
      Red: parseInt(`0x${color.slice(1, 3)}`),
      Green: parseInt(`0x${color.slice(3, 5)}`),
      Blue: parseInt(`0x${color.slice(5, 7)}`),
   };
};

const main = async () => {
   const app = express();
   var jsonParser = bodyParser.json();
   app.get("/api", (_, res) => {
      res.json({ poop: ":)" });
   });
   app.listen(8000, () => {
      console.log("server.started on localhost:8000");
   });
   app.post("/api/changecolor", jsonParser, (req, res) => {
      const data: changecolor = req.body;
      console.log(data.color);
      const color = colorToInts(data.color);

      exec(
         `python3 ../pytest/test.py ${color.Red} ${color.Blue} ${color.Green}`
      )
         .then(() => {
            res.statusCode = 200;
         })
         .catch(() => {
            res.statusCode = 500;
         });
   });
};

main().catch((err) => {
   console.error(err);
});
