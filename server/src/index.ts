import { serverStart } from "./server/server";

const main = async () => {
   serverStart();
};

main().catch((err) => {
   console.error(err);
});
