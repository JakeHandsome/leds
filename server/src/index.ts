import express from "express";

const main = async () => {
  const app = express();

  app.get("/api", (_, res) => {
    res.send("hello");
  });
  app.listen(3000, () => {
    console.log("server.started on localhost:4000");
  });
};

main().catch((err) => {
  console.error(err);
});
