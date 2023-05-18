// Realiza um disparo via Ajax para o endereço do meu NodeMcu
input = document.getElementById('ip')

var led_controle = function(status) {
    var xmlhttp = new XMLHttpRequest();
    var set_status = "http://" +  input.value + status;
    xmlhttp.open("GET", set_status);
    xmlhttp.send();
    console.log(status)
}

botao = document.getElementById('toggle-manual')

botao.addEventListener('click', ()=>{
    
    if(botao.checked){
        led_controle("/led5_on")
        botao_switch.checked = false
        console.log("Ligou")
    }else{
        led_controle("/led5_off")
        console.log("Desligou")
    }
})

botao_switch = document.getElementById('toggle-ldr')
iframeLDR = document.getElementById('LDR')

botao_switch.addEventListener('click', ()=>{
    if(botao_switch.checked){
        let ldrFunction = setInterval(() => {
            if(botao_switch.checked){
                iframeLDR.src = `http://${input.value}/ldr`;
            }else{
                iframeLDR.src = ` `;
            }
        }, 1000);
        botao.checked = false
        console.log('ldr_on')
    }else{
        iframeLDR.src = ' '
        led_controle('/led5_off')
        console.log('Desligado')
    }
})


