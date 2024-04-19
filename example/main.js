const { spawn } = require("child_process");

const wmw = spawn("test.exe");

wmw.stdout.on("data", data => {
    console.log(data.toString().substr(0, data.length-1));
})