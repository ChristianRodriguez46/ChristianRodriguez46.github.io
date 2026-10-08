<?php

define("DATA_DIR", "./data/");
define("PROD_FILE", DATA_DIR."products.json");

// MAKE SURE THE DATA DIRECTORY HAS BEEN CREATED
if (!file_exists(DATA_DIR)) {
    exit('data folder missing');
}

// CREATE THE PRODUCT FILE
if(!file_exists(PROD_FILE)){
    if(!touch(PROD_FILE)){
        exit('data folder permissions not set');
    }
}

// MAKE SURE THE ID PROVIDED IS UNIQUE
function uniqueID($id){
    $productList = getProducts();

    foreach($productList as $product){
        if($product['id'] === $id){
            return false;
        }
    }

    return true;
}

// ADD THE PRODUCT TO THE PRODUCTS FILE
function addProduct($product){
    $productList = getProducts();
    if(!isset($productList) || $productList == 'null'){
        $productList = [];
    }
    array_push($productList, $product);

    putProducts($productList);
}

// REMOVE THE PRODUCT FROM THE PRODUCTS FILE
function removeProduct($id){
    $productList = getProducts();
    $filter = fn($product) => $product['id'] != $id; 
    $productList = array_filter($productList, $filter);

    putProducts($productList);
}

// DUMP ALL PRODUCTS FROM THE PRODUCT FILE
function dumpProducts(){
    file_put_contents(PROD_FILE, json_encode([]));
}

// READ PRODUCTS FILE AND CONVERT TO AN ARRAY
function getProducts(){
    return json_decode(file_get_contents(PROD_FILE), true);
}

// CONVERT THE PRODUCT ARRAY TO JSON AND WRITE TO FILE
function putProducts($productList){
    file_put_contents(PROD_FILE, json_encode($productList));
}

?>

