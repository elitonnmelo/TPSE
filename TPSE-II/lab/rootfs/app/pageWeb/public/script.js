document.addEventListener('DOMContentLoaded', function () {
    openTab('info'); // Abre a aba "Início" por padrão

    const tablinks = document.querySelectorAll('.tablink');
    tablinks.forEach(tablink => {
        tablink.addEventListener('click', function () {
            const tabId = this.getAttribute('onclick').split("'")[1];
            openTab(tabId);
        });
    });
});

function openTab(tabId) {
    const tabs = document.querySelectorAll('.tab-content');
    tabs.forEach(tab => {
        tab.style.display = 'none';
    });

    const tabToOpen = document.getElementById(tabId);
    tabToOpen.style.display = 'block';
}



// script.j


/*document.addEventListener("DOMContentLoaded", () => {
    const ledSelect = document.getElementById("led-select");
    const ligarBtn = document.querySelector("button:nth-of-type(1)");
    const desligarBtn = document.querySelector("button:nth-of-type(2)");

    ligarBtn.addEventListener("click", ligarLED);
    desligarBtn.addEventListener("click", desligarLED);
});*/


document.addEventListener("DOMContentLoaded", () => {
    const ligarBtn = document.getElementById("on-button");
    const desligarBtn = document.getElementById("off-button");

    ligarBtn.addEventListener("click", ligarLED);
    desligarBtn.addEventListener("click", desligarLED);
});


function ligarLED() {
    const led = document.getElementById("led").value;
    enviarComando(led, 1);
}

function desligarLED() {
    const led = document.getElementById("led").value;
    enviarComando(led, 0);
}

function enviarComando(led, estado) {
    fetch(`/led?led=${led}&estado=${estado}`, { method: "POST" })
        .then((response) => response.text())
        .then((data) => {
            console.log(data);
        })
        .catch((error) => {
            console.error("Erro:", error);
        });
}

function piscarLED() {
    const led = document.getElementById("led-select-pisca").value;
    const quantidadePiscadas = parseInt(document.getElementById("quantidade-piscadas").value);

    if (quantidadePiscadas >= 1 && quantidadePiscadas <= 10) {
        // Enviar comandos para piscar o LED a quantidade de vezes desejada
        for (let i = 0; i < quantidadePiscadas; i++) {
            setTimeout(() => {
                enviarComando(led, 1); // Liga o LED
                setTimeout(() => {
                    enviarComando(led, 0); // Desliga o LED
                }, 500); // Aguarda 500 ms antes de desligar (ajuste conforme necessário)
            }, i * 1000); // Aguarda i segundos antes de ligar (ajuste conforme necessário)
        }
    } else {
        console.error("Informe um número de piscadas entre 1 e 10.");
    }
}


