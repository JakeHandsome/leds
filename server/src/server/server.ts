import express from "express";
import { scan } from "./endpoints/scan";
export function serverStart(): void {
   const app = express();
   app.use(express.static("../client/build"));
   app.listen(5000, () => console.log("server started on 5000"));
   app.get("/api/scan/", scan);
}
