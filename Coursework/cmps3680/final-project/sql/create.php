<?php
require_once('sqlTools.php');

$query = <<<TEXT
CREATE TABLE appointments (
    id int unsigned NOT NULL auto_increment,
    ordernumber varchar(225) NOT NULL UNIQUE,
    fname varchar(255) NOT NULL,
    lname varchar(255) NOT NULL,
    email varchar(255) NOT NULL,
    address varchar(255) NOT NULL,
    city varchar(255) NOT NULL,
    zip varchar(20) NOT NULL,
    phone varchar(20) NOT NULL,
    make varchar(20) NOT NULL,
    model varchar(20) NOT NULL,
    year varchar(20) NOT NULL,
    date DATE NOT NULL,
    time TIME NOT NULL,
    package varchar(255),
    exterior_services json,
    interior_services json,
    createdAt datetime DEFAULT NOW(),
    updatedAt datetime ON UPDATE NOW(),
    PRIMARY KEY (id)
);
TEXT;

$Users = <<<TABLE
CREATE TABLE users (
    id int UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    username varchar(255) NOT NULL UNIQUE,
    email varchar(255) NOT NULL,
    password varchar(255) NOT NULL
);    
TABLE;

$db = getConnection();

// if(mysqli_query($db, $query)){
//     echo "APPOINTMENTS ADDED SUCCESSFULLY\n";
// }else{
//     echo "FAILED TO CREATE TABLES\n";
//     die();
// }

if(mysqli_query($db, $Users)){
    echo "Users table ADDED SUCCESSFULLY\n";
}else{
    echo "FAILED TO CREATE User TABLES\n";
    die();
}
closeConnection($db);
?>
