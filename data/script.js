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
        console.log("Ligou")
    }else{
        led_controle("/led5_off")
        console.log("Desligou")
    }
})