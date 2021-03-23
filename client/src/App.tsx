import React, { useState } from "react";
import { ColorResult, HuePicker, SketchPicker } from "react-color";
import { Color } from "./protobuf/Color";
function App() {
   const [color, setColor] = useState<ColorResult>();
   const [curColor, setCurColor] = useState<Color>();
   const handleChange = (event: any) => {
      setColor(event);
      submit();
   };

   const submit = () => {
      const colorToSend: Color = {
         r: color?.rgb?.r ?? 0,
         g: color?.rgb?.g ?? 0,
         b: color?.rgb?.b ?? 0,
      };
      const requestOptions: RequestInit = {
         method: "POST",
         headers: { "Content-Type": "application/protobuf" },
         body: Color.encode(colorToSend).finish(),
      };
      fetch("/api/changecolor/", requestOptions)
         .then((response) => response.json())
         .then((data) => console.log(data));
   };

   const poll = () => {
      fetch("/api/currentcolor/")
         .then((r) => r.arrayBuffer())
         .then((data) => setCurColor(Color.decode(Buffer.from(data))));
   };
   return (
      <div className="App">
         <label>Color</label>
         <HuePicker color={color?.hex} onChange={handleChange} />
         <p>
            r: {color?.rgb.r} g: {color?.rgb.g} b: {color?.rgb.b}
         </p>
         <button onClick={submit}>Change color</button>
         <button onClick={poll}>Get current Color</button>
         <p>
            r: {curColor?.r} g: {curColor?.g} b: {curColor?.b}
         </p>
      </div>
   );
}

export default App;
