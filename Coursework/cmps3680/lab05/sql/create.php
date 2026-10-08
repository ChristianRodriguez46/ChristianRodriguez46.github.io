<?php
require_once('sqlTools.php');

$query = <<<TEXT
CREATE TABLE product (
    id int unsigned NOT NULL auto_increment,
    internalId varchar(20) NOT NULL,
    name varchar(255) NOT NULL,
    vendor varchar(255) NOT NULL,
    vendorPhone varchar(20) NOT NULL,
    quantity mediumint NOT NULL,
    lastPurchased datetime,
    createdAt datetime DEFAULT NOW(),
    updatedAt datetime ON UPDATE NOW(),
    PRIMARY KEY (id)
);
TEXT;

//MODIFY DATABSE

$db = getConnection();


if(mysqli_query($db, $query)){
    echo "PRODUCTS TABLE ADDED SUCCESSFULLY\n";
}else{
    echo "FAILED TO CREATE PRODUCT TABLE\n";
    die();
}

closeConnection($db);

?>
