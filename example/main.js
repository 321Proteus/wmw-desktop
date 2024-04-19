const { spawn } = require("child_process");
const express = require("express");

const app = express()
const wmw = spawn("test.exe");

var text = "";

wmw.stdout.on("data", data => {
    console.log(data.toString().substr(0, data.length-1));
    text = data.toString();
})

app.get("/", (req, res) => {
    console.log(text);
    res.send(text);
})

app.listen(5500, () => console.log("Port 5500"));