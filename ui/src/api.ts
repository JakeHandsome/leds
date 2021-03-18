import express from "express";

const app = express();
app.listen(8000);
app.get("/api", (req, res) => {
  res.send("fuck");
});
