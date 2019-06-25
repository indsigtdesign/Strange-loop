var express = require('express');
var router = express.Router();

//Serial com setup
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline');
/*
open port to arduino
todo : auto detect port and connect
*/
const loop = new SerialPort('/dev/tty.usbmodem14201', { autoOpen: false })
const station = new SerialPort('/dev/tty.usbmodem14101', { autoOpen: false })
//sets up listner from arduino with nice breaks etc
const loopStream = loop.pipe(new Readline({ delimiter: '\r\n' }))
const stationStream = station.pipe(new Readline({ delimiter: '\r\n' }))

var arduinoReady = false;

/* GET home page. */
router.get('/', function(req, res, next) {
	if (!arduinoReady) {
		res.render('index', { state: 'not ready' });
	} else {
		res.render('index', { state: 'ready' });
	}
});

router.post('/', function(req, res) {
	if (req.body.pov) {
	  pov = req.body.pov;
	  sendDataToArduino(pov.toString());
  	}

  	if (req.body.dScreen) {
	  dScreen = req.body.dScreen;
	  sendDataTodScreen(dScreen.toString());
  	}
});

loop.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
})


station.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
})

// The open event is always emitted
loop.on('open', function() {
	loop.write(new Buffer.from("9", 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
	
	// Sending the terminate character
	loop.write(new Buffer.from('\n', 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
})


station.on('open', function() {
	station.write(new Buffer.from("ass", 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
	
	// Sending the terminate character
	station.write(new Buffer.from('\n', 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
})

// Switches the port into "flowing mode"
loopStream.on('data', function (data) {
	console.log("loopStream says : ");
	if (data == "ready") {
		console.log("Arduino is ready");
		arduinoReady = true;
	} else console.log('Data:', data)
})


// Switches the port into "flowing mode"
stationStream.on('data', function (data) {
	console.log("stationStream says : " + data);
})

function sendDataToArduino(pov) {
	loop.write(new Buffer.from(pov, 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
	
	// Sending the terminate character
	loop.write(new Buffer.from('\n', 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
}

function sendDataTodScreen(dScreen) {
	station.write(new Buffer.from(dScreen, 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
	
	// Sending the terminate character
	station.write(new Buffer.from('\n', 'ascii'), function(err, results) {
		if(err) console.log('err ' + err);
		if(results) console.log('results ' + results);
	});
}

module.exports = router;
