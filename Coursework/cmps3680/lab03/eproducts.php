<?php

date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

$data = @file_get_contents('products.json'); // the address symbol supresses warning

$data = json_decode($data, true);

//sort the data
uasort($data, function($a, $b){
    return $a['details']['quantity'] <=> $b['details']['quantity']; 
});

echo "<div id= 'container'>";
foreach($data as $key => $product){
    $pic = <<<CARD
     <div class='product-card'>
        <div class ='d-info'>
            <div class='product-image'>
            <img src = " {$product['details']['image']}" 
                 alt= '{$product['details']['name']}'>
            </div>
CARD;

    $info = <<<INFO

            <div class = 'product-info'>
                Name: {$product['details']['name']} <br>

                vendor: {$product['details']['vendor']} <br>

                Quantity: {$product['details']['quantity']} <br>

                price: {$product['details']['price']} <br>
            </div>
        </div>
     <hr> 

INFO;

    $desc = <<<DESCRIPTION
         <div class='product-description'>
             Decription:{$product['details']['description']}
         </div>
    </div>
DESCRIPTION;

    echo $pic;
    echo $info;
    echo $desc;
}
echo "</div>";
?>
