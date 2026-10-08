<?php
date_default_timezone_set("America/Los_Angeless");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

require_once "./productTools.php";
require_once "./validate.php";

$postTarget = htmlspecialchars($_SERVER['PHP_SELF']);

$product = [];
$errors = [];

if($_SERVER["REQUEST_METHOD"] == "POST"){
    if(isset($_POST['dump'])){
        dumpProducts();
    }else{
        foreach($_POST as $key => $value){
            $product[$key] = cleanData($value);
        }

        if(uniqueID($product['ID'])){
            $errors['ID'] = "Product is not found";
        }

        if(empty($errors)){
            removeProduct($product['ID']);
        }
    }
}

?>
<html>
<head>
<title>Remove Products</title>
<link type="text/css" rel="stylesheet" href="./style.css">
</head>

<body>
<div class="n-container">
<ul class="navbar">
<li><a href="./add.php">Add Products</a></li>
<li><a id="active" href="./remove.php">Remove Products</a></li>
</ul>
</div>

<div id="container">
<h1>Remove Products</h1>

<form method="post" action="<?= $postTarget?>">
<label for="id">ID</label><br>
<input type="text" name="ID" id="id"
       value= "<?= $product['ID'] ?? ""?>"> <?= $errors['ID'] ?? ""?><br>
<input type="submit" name = "dump" value="Dump">
<input type="submit" name="submit" value="Submit">
</form>

<div id="output">
<div>
<?php

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

</div> <!--close container div-->
</body>
</html>
