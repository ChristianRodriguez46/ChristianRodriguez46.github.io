<?php

function cleanData($data){
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

function validID($ID){
    return preg_match('/\b[0-9A-F]{4}-[0-9A-F]{4}/', $ID);
}

// TODO: Write validation functions for each field required

function validProductName($productName){
    return preg_match('/^[a-zA-z]+$/', $productName);
}
function validVendor($Vendor){
    return preg_match('/^[a-zA-Z]+$/', $Vendor);
}
function validPnum($vendorPhone){
    return preg_match('/^\d{3}-\d{3}-\d{4}$/', $vendorPhone);
}
function validQuantity($Quantity){
    return preg_match('/\d/', $Quantity); //quantity can be any number
}
function validLastpurchased($lastPurchased){
    return !empty($lastPurchased);
}
?>
