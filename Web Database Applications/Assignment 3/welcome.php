<?php
    //print out the name of the logged-in user
    if(isset($_GET['username'])){
        echo "Welcome ".$_GET['username']."!";
    }
?>
