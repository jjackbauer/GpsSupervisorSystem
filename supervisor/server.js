const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const express = require('express');
const path = require('path');
var public = path.join(__dirname, 'public');

const port = new SerialPort('COM5', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

const app = express();

global.gpsData = null;

function nmeaConverter(value, direction){
  /**
   * @params:
   * @value String com o valor de lat e lng gerado pelo gps
   */
  DD = parseInt(parseFloat(value)/100);
  SS = parseFloat(value) - DD * 100;
  decimal = (DD + SS/60);
  return direction == 'S' || direction == 'W' ? -1*decimal : decimal;
}

function distance(lat1, lon1, lat2, lon2){
  R = 6371000;
  dLat = lat2 - lat1;
  dLon = lon2 - lon1;

  a = Math.pow(Math.sin(dLat/2),2) + Math.cos(lat1) * Math.cos(lat2) *  Math.pow(Math.sin(dLon/2),2);
  c = 2*Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));

  return R*c;
}

function getDateTime(date, time){
	day = parseInt(date[0]+date[1]);
	month = parseInt(date[2]+date[3]);
	year = parseInt('20'+date[4]+date[5]);
	hour = parseInt(time[0]+time[1]);
	min = parseInt(time[2]+time[3]);
	sec = parseInt(time[4]+time[5]);
	return new Date(year,month-1, day, hour, min, sec);
}

app.use(express.static(public));

app.get('/gps', (req, res) => {
  res.sendFile(path.join(public, 'index.html'));
})

app.post('/getData', (req, res)=>{
  res.json(global.gpsData);
})

// Read the port data
port.on("open", () => {
  console.log('serial port open');
});

//$GPRMC,150023.00,A,0924.79199,S,04030.97658,W,0.375,,040719,,,A*72
parser.on('data', data =>{
  dados = data.split(',')
  status = dados[2] ? dados[2]: false;

  if(status) {
    switch(status){
      case 'V': global.gpsData = {status: 404, msg: "Sinal não encontrado!", datetime: getDateTime(dados[9], dados[1])};
                break;
      case 'A': 
          if(global.gpsData){
			  dist =distance(global.gpsData.latitude, global.gpsData.longitude , nmeaConverter(dados[3], dados[4]),nmeaConverter(dados[5], dados[6]))
			  //console.log(dist);
            //if(dist>1000){
              //return false;
            //}
          }
          global.gpsData = {status: 200, datetime: getDateTime(dados[9], dados[1]), latitude: nmeaConverter(dados[3], dados[4]), longitude: nmeaConverter(dados[5], dados[6])};
                break;
      default: global.gpsData = {status: 404, msg: "Sinal não encontrado!", datetime: getDateTime(dados[9], dados[1])};
                break;
              }
            }
});

app.listen(3000, function() {
  console.log("Servidor rodando na porta 3000!");
});