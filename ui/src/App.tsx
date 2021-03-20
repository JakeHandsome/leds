import React, { useState } from "react";

function App() {
   const [data, setData] = useState<string>("data");
   const [color, setColor] = useState<string>("#FFFFFF");
   const callBackEnd = async () => {
      fetch("/api")
         .then((res) => res.json())
         .then((d) => setData(data + JSON.stringify(d, null, 2)));
   };
   const handleChange = (event: any) => {
      console.log({ event });
      console.log(event.target.value);
      setColor(event.target.value);
   };

   const submit = () => {
      const requestOptions: RequestInit = {
         method: "POST",
         headers: { "Content-Type": "application/json" },
         body: JSON.stringify({ color: color }),
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
         <input type="color" value={color} onChange={handleChange} />
         <button onClick={submit}>Change color</button>
      </div>
   );
}

export default App;
