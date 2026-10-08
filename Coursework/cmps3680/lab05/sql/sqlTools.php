<?php
require_once('config.php');


function getConnection(){

    $mysqli = mysqli_connect(
        $GLOBALS['servername'], 
        $GLOBALS['username'], 
        $GLOBALS['password'], 
        $GLOBALS['dbname']
    );

    if($mysqli){
        return $mysqli;
    }else{
        echo "INVALID DATABASE CREDENTIALS";
        die();
    }
}

function closeConnection($conn){
    if(mysqli_close($conn)){
        return true;
    }else{
        echo "UNABLE TO CLOSE DATABASE!";
        die();
     }
}
?>
