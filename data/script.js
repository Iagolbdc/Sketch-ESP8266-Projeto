// Realiza um disparo via Ajax para o endereço do meu NodeMcu
var led_controle = function(status) {
    var xmlhttp = new XMLHttpRequest();
    var set_status = "http://192.168.1.41/" + status;
    xmlhttp.open("GET", set_status);
    xmlhttp.send();
    console.log(status)
}

botao = document.getElementById('toggle-manual')

botao.addEventListener('click', ()=>{
    
    if(botao.checked){
        led_controle("led5_on")
        console.log("Ligou")
    }else{
        led_controle("led5_off")
        console.log("Desligou")
    }
})