import React, { useState } from "react";
import { ColorResult, SketchPicker } from "react-color";
import { Color } from "./protobuf/Color";
function App() {
   const [data, setData] = useState<string>("data");
   const [color, setColor] = useState<ColorResult>();
   const callBackEnd = async () => {
      fetch("/api")
         .then((res) => res.json())
         .then((d) => setData(data + JSON.stringify(d, null, 2)));
   };
   const handleChange = (event: any) => {
      console.log({ event });
      setColor(event);
      //setColor(event.target.value);
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
      fetch("/api/changecolor", requestOptions)
         .then((response) => response.json())
         .then((data) => console.log(data));
   };
   return (
      <div className="App">
         I want to die
         <button onClick={callBackEnd}>I am a dumb button</button>
         <p>{data}</p>
         <label>Color</label>
         <SketchPicker color={color?.hex} onChange={handleChange} />
         <p>
            R: {color?.rgb.r} G: {color?.rgb.g} B: {color?.rgb.b}
         </p>
         <button onClick={submit}>Change color</button>
      </div>
   );
}

export default App;
