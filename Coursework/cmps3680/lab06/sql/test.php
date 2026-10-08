<?php
require_once('./sqlTools.php');

/*
$prod1 = [
    "id" => "1234-5678",
    "productName" => "gear",
    "vendor" => "Bob's Widgets",
    "vendorPhone" => "661-555-5555",
    "quantity" => 30,
    "lastPurchased" => "2024-03-05"
];

$prod2 = [
    "id" => "1234-5679",
    "productName" => "gear",
    "vendor" => "Bob's Widgets",
    "vendorPhone" => "661-555-5555",
    "quantity" => 30,
    "lastPurchased" => "2024-03-05"
];

$prod3 = [
    "id" => "1234-5680",
    "productName" => "gear",
    "vendor" => "Bob's Widgets",
    "vendorPhone" => "661-555-5555",
    "quantity" => 30,
    "lastPurchased" => "2024-03-05"
];
$prod4 = [
    "id" => "1234-5681",
    "productName" => "gear",
    "vendor" => "Bob's Widgets",
    "vendorPhone" => "661-555-5555",
    "quantity" => 30,
    "lastPurchased" => "2024-03-05"
];

addProduct($prod1);
echo "PRODUCT ADDED\n";
addProduct($prod2);
echo "PRODUCT ADDED\n";
addProduct($prod3);
echo "PRODUCT ADDED\n";
addProduct($prod4);
echo "PRODUCT ADDED\n";

//removeProduct($prod["id"]);
echo "PRODUCT REMOVED\n";

//dumpProducts();
//echo "All Products dumped\n";

echo "Here are the products: \n";
*/
$products = getProducts();
foreach ($products as $product)
{
    echo "Id: " . $product['id'] . "\n";
    echo "Name: " . $product['name'] . "\n";;
    echo "Vendor: " . $product['vendor'] . "\n";
    echo "Vendor Phone: " . $product['vendorPhone'] . "\n";
    echo "Quantity: " . $product['quantity'] . "\n";
    echo "Last Purchased: " . $product['lastPurchased'] . "\n";
    echo "\n";
}

if (!uniqueID('1234-5678'))
{
   echo "Id: 1234-5678 is not a unique ID";
}else{
   echo "Id: 1234-5678 is a unique ID";
}

if (!uniqueID('1234-5682'))
{
    echo "Id: 1234-5682 is not a unique ID";
}else{
 
    echo "Id: 1234-5682 is a unique ID";
}

?>
