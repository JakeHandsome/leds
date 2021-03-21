import React, { useState } from "react";
import {
   ChromePicker,
   ColorResult,
   HuePicker,
   SketchPicker,
} from "react-color";

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
      const requestOptions: RequestInit = {
         method: "POST",
         headers: { "Content-Type": "application/json" },
         body: JSON.stringify(color?.rgb),
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
