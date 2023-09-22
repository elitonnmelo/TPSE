const express = require("express");
const fs = require("fs");

const app = express();
const port = 7000;

app.use(express.static(__dirname + "/public"));
app.use(express.urlencoded({ extended: true }));

app.post("/led", (req, res) => {
    const led = req.query.led;
    const estado = req.query.estado;

    const filePath = `/sys/class/leds/beaglebone:green:usr${led}/brightness`;
    

    fs.writeFile(filePath, estado, (err) => {
        if (err) {
            console.error("Erro ao escrever no arquivo:", err);
            res.status(500).send("Erro ao controlar o LED.");
            return;
        }

        console.log(`LED ${led} definido como ${estado}`);
        res.send(`LED ${led} definido como ${estado}`);
    });
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
});
