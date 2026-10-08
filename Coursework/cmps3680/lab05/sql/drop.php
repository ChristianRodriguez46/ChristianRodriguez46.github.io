<?php
require_once('sqlTools.php');

$query = "DROP TABLE product";
//MODIFY DATABSE

$db = getConnection();


if(mysqli_query($db, $query)){
    echo "PRODUCTS TABLE SUCCESSFULLY REMOVED\n";
}else{
    echo "FAILED TO REMOVE PRODUCT TABLE\n";
    die();
}

closeConnection($db);

?>
