import React, { useState } from "react";

function App() {
   const [data, setData] = useState<string>("data");
   const callBackEnd = async () => {
      fetch("/api")
         .then((res) => res.json())
         .then((d) => setData(data + JSON.stringify(d, null, 2)));
   };
   return (
      <div className="App">
         I want to die <button onClick={callBackEnd}>I am a dumb button</button>
         <p>{data}</p>
      </div>
   );
}

export default App;
