<?php
require_once('sqlTools.php');

$query = "DROP TABLE appointments";
//MODIFY DATABSE

$db = getConnection();

$users = "DROP TABLE users";

if(mysqli_query($db, $query)){
    echo "APPOINTMENTS TABLE SUCCESSFULLY REMOVED\n";
}else{
    echo "FAILED TO REMOVE APPOINTMENTS TABLE\n";
    die();
}


if(mysqli_query($db, $users)){
    echo "USERS TABLE SUCCESSFULLY REMOVED\n";
}else{
    echo "FAILED TO REMOVE USERS TABLE\n";
    die();
}

closeConnection($db);

?>
