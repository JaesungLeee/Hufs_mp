function measurement_start() {
	console.log('start...');
	measurementCnt = document.getElementById("measurementCnt");
	socket.emit('measurement_start', {iterations: parseInt(measurementCnt.value)});
}

var socket = io.connect('http://' + document.domain + ':' + location.port);

socket.on('connect', function() {
	console.log('Websocket connected!');
});

var arr_time_vals = [];
var arr_sound_vals = [];

socket.on('msg_from_server', function(msg) {
	console.log(msg);
	
	var logArea = document.getElementById("log"); 
	var graphArea = document.getElementById("mydiv");

	if(msg==null) { 
		logArea.textContent='';
	} 
	else { 
		logArea.textContent='time value='+ msg.timeVal + 
							'\nsound value=' + msg.soundVal + 
							'\n'+logArea.textContent;     
	}

	arr_sound_vals.push(msg.soundVal);
	arr_time_vals.push(msg.timeVal);

	var trace1 = {
		x : arr_time_vals,
		y : arr_sound_vals
	}

	var data = [trace1]

	Plotly.newPlot('myDiv', data)
});
