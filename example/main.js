const { spawn } = require("child_process");
const express = require("express");

const app = express()
const wmw = spawn("wmw_1.0-release.exe", { stdio: "pipe" });

var text = "";

wmw.stdout.on("data", data => {
    text = data.toString().substr(0, data.length-2);
})

app.get("/", (req, res) => {
    console.log(text);
    res.send(text);
})

app.listen(5500, () => console.log("Port 5500"));