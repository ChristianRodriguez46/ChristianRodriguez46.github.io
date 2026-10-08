<?php
require_once "./productTools.php";
require_once "./validate.php";

$postTarget = htmlspecialchars($_SERVER['PHP_SELF']);

$product = [];
$errors = [];

if($_SERVER["REQUEST_METHOD"] == "POST"){

    // CLEAN ALL FIELDS FROM ANY BAD DATA
    foreach($_POST as $key => $value){
        $product[$key] = cleanData($value);
    }
    
    // VALIDATE ID    
    if(!validID($product['ID'])){
        $errors['ID'] = "Invalid ID";
    }else if(!uniqueID($product['ID'])){
        $errors['ID'] = "ID is not unique";
    }
    if(!validProductname($product['productName'])){
        $errors['productName'] = "Invalid Product Name";
    }
    if(!validVendor($product['Vendor'])){
        $errors['Vendor'] = "Invalid Vendor";
    }
    if(!validPnum($product['vendorPhone'])){
        $errors['vendorPhone'] = "Invalid Vendor Phone Number";
    }
    if(!validQuantity($product['Quantity'])){
        $errors['Quantity'] = "Invalid Quantity";
    }
        // IF THERE ARE NO ERRORS, ADD THE RECORD
    if(empty($errors)){
        addProduct($product);
    }
}

?>

<html>
<head>
<title>Add Products</title>
<link type="text/css" rel="stylesheet" href="./style.css">
</head>
<body>

<div class="n-container">
<ul class="navbar">
<li><a id="active" href="./add.php">Add Products</a></li>
<li><a href="./remove.php">Remove Products</a></li>
</ul>
</div>

<div id="container">
<h1>Add Products</h1>

<form method="post" action="<?= $postTarget ?>">
<label for="id">ID</label><br>
<input type="text" name="ID" id="id" placeholder="XXXX-XXXX (0-F)"
       value="<?= $product['ID'] ?? "" ?>" required> <?= $errors['ID'] ?? "" ?> <br> 

<!-- TODO: ADD ADDITIONAL FIELDS -->

<label for="productName">Product Name:</label><br>
<input type="text" name="productName" id="productName"
       value="<?= $product['productName'] ?? "" ?>" required> <?= $errors['productName'] ?? "" ?> <br> 

<label for="vendor">Vendor:</label><br>
<input type="text" name="Vendor" id="vendor"
       value="<?= $product['Vendor'] ?? "" ?>" required> <?= $errors['Vendor'] ?? "" ?> <br> 

<label for="vendorPhone">Vendor Phone:</label><br>
<input type="tel" name="vendorPhone" id="vendorPhone"
        placeholder="XXX-XXX-XXXX"
       value="<?= $product['vendorPhone'] ?? "" ?>" required> <?= $errors['vendorPhone'] ?? "" ?> <br> 

<label for="quantity">Quantity:</label><br>
<input type="number" name="Quantity" id="quantity" min="1"
       value="<?= $product['Quantity'] ?? "" ?>" required> <?= $errors['Quantity'] ?? "" ?> <br>

<label for="lastPurchased">Last purchased</label><br>
<input type="date" name="lastPurchased" id="lastPurchased"      
       value="<?= $product['lastPurchased'] ?? "" ?>" required> <?= $errors['lastPurchased'] ?? "" ?> <br> 

<input type="submit" value="Submit">
</form>

<div id="output">
<?php

// GET PRODUCTS AND GENERATE HTML
$products = getProducts();
foreach($products as $p){
    echo "<div class='product'>";
    foreach($p as $key => $value){
        if($key == "productName"){
            echo "Product Name: $value<br>";
        }elseif($key == "vendorPhone"){
            echo "Vendor Phone: $value<br>";
        }elseif($key == "lastPurchased"){
            echo "Last Purchased: $value<br>";
        }else{
            echo "$key: $value<br>";
        }
    }
    echo "</div>";
}

?>
</div>

</div>  <!--close container div-->

</body>
</html>
