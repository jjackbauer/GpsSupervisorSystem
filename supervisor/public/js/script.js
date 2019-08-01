
//iniciando mapa setando uma posição aleatória
const mymap = L.map('mapid',{
    center: [50.5,30.5], 
    zoom: 10,
    zoomControl: false,
    zoomSnap: 0.25});

//setando a layer da openstreet para renderizar o mapa
const tileLayer = L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(mymap);

//iniciando o polyline para desenhar as linhas no mapa
const polyline = L.polyline([], {color: "rgba(0,0,0,.5)", weight: 2}).addTo(mymap);

//iniciando o icone do mapa
const myIcon = L.icon({
    iconUrl: 'images/icon2.png',
    iconSize: [30, 30],
    iconAnchor: [15, 30]
});

//setando um marcador
const marker = L.marker([50.5,30.5], {icon: myIcon}).addTo(mymap);

//Quando o documento estiver pronto
$(document).ready(function () {
    console.log("Ready!");

    $(document).on('input change', '#zoomControl', function() {
        mymap.setZoom($(this).val())
    });

    //seta a 
    //setPosition();
    setInterval(setPosition, 2000);
    
});

function setPosition(){
    /**
     * Função que pega os dados da rota /getData pelo metodo post.
     */
    $.post('/getData', function(res){
        console.log(res);
        if(res.status==200){
            if(!$('.loading').hasClass('fade-out')) $('.loading').addClass('fade-out');

            if($('.status-td span').hasClass('circle-red')) $('.status-td').html(`<span class="circle-green"></span> Signal Active`);
            mymap.setView([res.latitude, res.longitude]);
            marker.setLatLng([res.latitude, res.longitude]);
            polyline.addLatLng([res.latitude, res.longitude]);
            setDecoderResults(res);
        }else{
            setDecoderResults(false)
            if($('.status-td span').hasClass('circle-green')) $('.status-td').html(`<span class="circle-red"></span> Signal Active`);
        }
    }, 'json')
}

function setDecoderResults(data){
    /**
     * params:
     * @data objeto com valores para setar na tabela    
     */
    if(data){
    $('.position-td').html(`${data.latitude>0? data.latitude + ' N': Math.abs(data.latitude) + ' S'}, ${data.longitude>0? data.longitude + ' E': Math.abs(data.longitude) + ' W'}`)
    }else{
        $('.position-td').html("");
    }
}
