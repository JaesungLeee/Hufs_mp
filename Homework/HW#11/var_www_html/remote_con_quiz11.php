<?php
	if(isset($_GET['lightLog'])) {
              $value = shell_exec("/home/pi/jslee/php_lightLog 2>&1");
              echo $value;
       } 
       else if(isset($_GET['touchAlert'])) {
              $value = shell_exec("/home/pi/jslee/php_touchAlert 2>&1");
              echo $value;
       }
       else if(isset($_GET['switchAlert'])) {
              $value = shell_exec("home/pi/jslee/switch_alert_php 2>&1");
              echo $value;
       }
       else {
              echo "No Such Argument!!! by jaesung.";
       }
?>
