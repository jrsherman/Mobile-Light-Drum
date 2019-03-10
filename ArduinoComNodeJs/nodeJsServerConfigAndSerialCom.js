const fs = require('fs');

const express = require('express');
const app = express();
var dataFromArduino = ''

app.use(express.static(__dirname + '/nodeTrialDir'));



// app.get('/', (req, res) => {
//     res.send(dataFromArduino);
// });
app.listen(3000, () => console.log('Gator app listening on port 3000!'));
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('/dev/cu.usbmodem144201', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
// Read the port data
port.on("open", () => {
  console.log('serial port open');
});

var counter = 0;
parser.on('data', data =>{
dataFromArduino = data
var name = data.toString();
// console.log(typeof data);
console.log(data.charCodeAt(0));

	var trialStuff = '{ "'+"pete"+'":"'+data.charCodeAt(0)+'" }';
	fs.writeFile("/Users/valkyrie/Desktop/nodeTrialDir/test.json", trialStuff, function(err) {
		 if(err) {
			  return console.log(err);
		 }
	});

counter++;

});
