function XHR_write(data) {
    var xhr = new XMLHttpRequest();

    xhr.open("GET","remote_con.php?" + data);
    xhr.send();
}

function XHR_read(data) {
    var xhr = new XMLHttpRequest();

    xhr.open("GET","remote_con.php?" + data, false);
    xhr.send();
    
    return xhr.responseText;
}

function repeat() {
    ultraSonic();
}
setInterval(function(){repeat();});

//--------------------------------------------------------//



function ultraSonic(){
var val=XHR_read('ultraSonic');

if(val>=20){
    document.ultraSonic.src='img/ultrasonic3.png';
}else if(val>=10){
    document.ultraSonic.src='img/ultrasonic2.png';
}else{
    document.ultraSonic.src='img/ultrasonic1.png';
}

document.getElementById("US_val").value=val+"cm";
}


function LASERON(){
    var state = document.getElementById("LASER_ON").value;

    if (state = "ON") {
        
        XHR_write('LASERON');
        document.LASER.src='img/laser_on.png';
        // document.getElementById("LASER_ON").value = "OFF"
        state = "OFF"
    }
    else {
        
        XHR_write('LASEROFF');
        document.LASER.src='img/laser_off.png';
        state = "ON"
        // document.getElementById("LASER_ON").value = "ON"
    }
}