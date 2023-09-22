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
    
    enviarComando(0, 0);
    enviarComando(1, 0);
    enviarComando(2, 0); 
    enviarComando(3, 0);
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

function piscarPorIntervalo() {
    const inicio = parseInt(document.getElementById("intervaloInicio").value, 10);
    const fim = parseInt(document.getElementById("intervaloFim").value, 10);
    const quantidade = parseInt(document.getElementById("quantidade-piscadas-intervalo").value, 10);

    // Valide os valores
    if (isNaN(inicio) || isNaN(fim) || isNaN(quantidade) ||
        inicio < 0 || inicio > 3 || fim < 0 || fim > 3 ||
        inicio > fim || quantidade < 1 || quantidade > 10) {
        alert("Por favor, insira valores válidos.");
        return;
    }

    // Lógica para piscar LEDs dentro do intervalo especificado
    const intervalo = fim - inicio + 1;
    const leds = [];

    for (let i = 0; i < intervalo; i++) {
        leds.push(inicio + i);
    }

    // Repetir o piscar LEDs pelo número de vezes especificado
    for (let j = 0; j < quantidade; j++) {
        for (let i = 0; i < leds.length; i++) {
            const led = leds[i];
            enviarComando(led, 1); // Liga o LED
            // Espera um pouco (tempo de espera entre piscadas)
            delay(10000);
            enviarComando(led, 0); // Desliga o LED
            delay(10000);
        }
    }
    enviarComando(0, 0);
    enviarComando(1, 0);
    enviarComando(2, 0); 
    enviarComando(3, 0);
}

function delay(milliseconds) {
    for (let i = 0; i < milliseconds; i++) {
        // Esta função cria um atraso, mas não bloqueia a execução do código
        // dentro do loop for.
        // O tempo exato do atraso pode variar dependendo do ambiente de execução.
    }
}



