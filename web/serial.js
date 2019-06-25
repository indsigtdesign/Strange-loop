const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('/dev/tty.usbmodem14201', { autoOpen: false })
const lineStream = port.pipe(new Readline({ delimiter: '\r\n' }))

port.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
})

// The open event is always emitted
port.on('open', function() {
})

// Switches the port into "flowing mode"
lineStream.on('data', function (data) {
	if (data == "ready") {
		console.log("Arduino is ready");

		
		port.write(new Buffer.from('12345', 'ascii'), function(err, results) {
			if(err) console.log('err ' + err);
			if(results) console.log('results ' + results);
		});
		
		// Sending the terminate character
		port.write(new Buffer.from('\n', 'ascii'), function(err, results) {
			if(err) console.log('err ' + err);
			if(results) console.log('results ' + results);
		});

	} else console.log('Data:', data)
})