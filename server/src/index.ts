import express from "express";

const main = async () => {
  const app = express();

  app.get("/api", (_, res) => {
    res.json({ poop: ":)" });
  });
  app.listen(8000, () => {
    console.log("server.started on localhost:8000");
  });
};

main().catch((err) => {
  console.error(err);
});
