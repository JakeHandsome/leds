import axios from "axios";
import express from "express";
import { ESP32Init } from "../../protobuf/ESP32Init";
import find from "local-devices";
import * as serverConstants from "../serverConstants";

interface ESP32InitDevice extends ESP32Init {
   ip: string;
}

export const scan: express.RequestHandler = async function (_, res) {
   const responses: Array<ESP32InitDevice> = [];
   const devices = await find();

   await Promise.all(
      devices.map(async (d) => {
         try {
            const response = await axios({
               method: "get",
               url: `http://${d.ip}${serverConstants.APIHEADER}/init`,
               responseType: "arraybuffer",
               headers: { "content-type": "application/protobuf" },
               timeout: 500,
            });
            if (
               response.status == 200 &&
               response.headers["content-type"] === "application/protobuf"
            ) {
               try {
                  const init = ESP32Init.decode(response.data);
                  console.log(`Valid response from ${d.ip}`);
                  responses.push({ ...init, ip: d.ip });
               } catch (error) {
                  console.log(`Parsing error from ${d.ip}`);
               }
            } else {
               console.log(`Invalid response from ${d.ip}`);
            }
         } catch (err) {
            console.log(`No response from ${d.ip}`);
         }
      })
   );
   res.send(JSON.stringify(responses));
};
