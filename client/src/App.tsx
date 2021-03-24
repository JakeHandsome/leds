import React, { useState } from "react";
import { ColorResult } from "react-color";
import LED from "./components/Colorbox";
import { Color } from "./protobuf/Color";
function App() {
   const [color, setColor] = useState<Color>({ r: 0, g: 0, b: 0 });
   const [curColor, setCurColor] = useState<Color>({ r: 0, g: 0, b: 0 });
   const handleChange = (event: ColorResult) => {
      setColor(event.rgb);
      submit();
   };

   const submit = () => {
      const requestOptions: RequestInit = {
         method: "POST",
         headers: { "Content-Type": "application/protobuf" },
         body: Color.encode(color).finish(),
      };
      fetch("/api/changecolor/", requestOptions);
   };

   const poll = () => {
      fetch("/api/currentcolor/")
         .then((r) => r.arrayBuffer())
         .then((data) => setCurColor(Color.decode(Buffer.from(data))));
   };
   return (
      <div className="App">
         <label>LED</label>
         <LED color={color} setColor={setColor} onChange={handleChange} />
         <button onClick={submit}>Change color</button>
         <button onClick={poll}>Get current Color</button>
         <LED color={curColor} />
      </div>
   );
}

export default App;
