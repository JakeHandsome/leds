const { chdir } = require("process");
const { parallel, series } = require("gulp");
const { execSync, exec } = require("child_process");
function installProtoBuf(cb) {
   chdir("protobuf");
   execSync("npm i");
   chdir("..");
   cb();
}
function installServer(cb) {
   chdir("server");
   execSync("npm i");
   chdir("..");
   cb();
}
function installClient(cb) {
   chdir("client");
   execSync("npm i");
   chdir("..");
   cb();
}

function clean(cb) {
   execSync("git clean -fXd");
   execSync("npm i");
   cb();
}

const protobuf = series(installProtoBuf, function buildProtobuf(cb) {
   chdir("protobuf");
   execSync("npm run build");
   chdir("..");
   cb();
});

const client = series(installClient, function buildClient(cb) {
   chdir("client");
   execSync("npm run build");
   chdir("..");
   cb();
});

const server = series(installServer, function buildServer(cb) {
   chdir("server");
   execSync("npm run build");
   chdir("..");
   cb();
});

function initESP32(cb) {
   chdir("ESP32");
   execSync("platformio init --ide vscode");
   chdir("..");
   cb();
}

const ESP32Build = series(initESP32, function ESP32Build(cb) {
   chdir("ESP32");
   execSync("platformio run");
   chdir("..");
   cb();
});

const ESP32 = ESP32Build;
const UploadCOM = series(ESP32Build, function UploadCOM(cb) {
   chdir("ESP32");
   execSync("platformio run --target upload --environment COM");
   chdir("..");
   cb();
});

const UploadOTA = series(ESP32Build, function UploadOTA(cb) {
   chdir("ESP32");
   execSync("platformio run --target upload --environment OTA");
   chdir("..");
   cb();
});

/* TODO figure out way to start everything
const StartServer = series(installServer, function StartServer(cb) {
   chdir("server");
   execSync("npm run dev");
   chdir("..");
   cb();
});

const StartClient = series(installClient, function StartClient(cb) {
   chdir("client");
   execSync("npm start");
   chdir("..");
   cb();
});
exports.start = series(protobuf, parallel(StartClient, StartServer, UploadCOM));
*/
const buildAll = series(protobuf, parallel(client, server, ESP32Build));
const install = parallel(installClient, installProtoBuf, installServer);

exports.install = install;
exports.clean = clean;
exports.protobuf = protobuf;
exports.server = series(protobuf, server);
exports.client = series(protobuf, client);
exports.default = buildAll;
exports.ESP32 = series(protobuf, ESP32);
exports.UploadOTA = series(protobuf, UploadOTA);
exports.UploadCOM = series(protobuf, UploadCOM);
