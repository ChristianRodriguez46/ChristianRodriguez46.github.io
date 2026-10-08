<?php

$data = @file_get_contents('products.json'); // the address symbol supresses warning

$data = json_decode($data, true);

//sort the data
uasort($data, function($a, $b){
    return $a['details']['quantity'] <=> $b['details']['quantity']; 
});

foreach($data as $key => $product){
    echo "
    <div class='product-card'>
        <div class='product-image'>
            <img src = '{$product['details']['image']}' 
                 alt= '{$product['details']['name']}'>
        </div>
        <div class='product-info'>
            <div class='product-name'>
                 Name: {$product['details']['name']}
            </div>
            
            <div class='product-vendor'>
                 vendor: {$product['details']['vendor']}
            </div>
            
            <div class='product-quantity'>
                 Quantity: {$product['details']['quantity']}
            </div>

            <div class='product-price'>
                 price: {$product['details']['price']}
            </div>
        </div>
            <div class='product-description'>
                 Decription:{$product['details']['description']}
            </div>
    </div>
    ";
}
?>
