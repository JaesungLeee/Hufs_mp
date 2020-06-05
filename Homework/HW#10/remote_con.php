<?php
    if(isset($_GET['ultraSonic'])) {
        $ret = shell_exec('/home/pi/jaesung/US 2>&1');
        echo $ret;
    }

    else if(isset($_GET['LASERON'])) {
        $ret = shell_exec('/home/pi/jaesung/laserOn 2>&1');
        echo $ret;
    }

    else if(isset($_GET['LASEROFF'])) {
        $ret = shell_exec('/home/pi/jaesung/laserOff 2>&1');
        echo $ret;
    }

    else {
        echo "You entered wrong parameter. Please try again."
    }