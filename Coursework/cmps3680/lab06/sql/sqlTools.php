<?php
require_once('./config.php');


function getConnection(){

    $mysqli = mysqli_connect(
        $GLOBALS['servername'], 
        $GLOBALS['username'], 
        $GLOBALS['password'], 
        $GLOBALS['dbname']
    );

    if($mysqli){
        return $mysqli;
    }else{
        echo "INVALID DATABASE CREDENTIALS";
        die();
    }
}

function addProduct($product)
{
    $conn = getConnection();

    $sql = <<<SQL
        INSERT INTO product
        (internalId, productName, vendor, vendorPhone, quantity, lastPurchased)
        VALUES (?,?,?,?,?,?)
    SQL;

    $stmt = mysqli_prepare($conn, $sql);

    mysqli_stmt_bind_param(
        $stmt,
        'ssssis',
        $product['id'], 
        $product['productName'],
        $product['vendor'],
        $product['vendorPhone'],
        $product['quantity'],
        $product['lastPurchased']
    );

    mysqli_stmt_execute($stmt);

    closeConnection($conn);
}

function removeProduct($id)
{
    $conn = getConnection();

    $sql = "DELETE FROM product WHERE internalId = ?";

    $stmt = mysqli_prepare($conn, $sql);

    if(!$stmt){
        echo "STATEMENT NOT PREPARED";
        die();
    }

    mysqli_stmt_bind_param(
        $stmt,
        's',
        $id
    );

    if(!mysqli_stmt_execute($stmt)){
        echo "remove Products failed";
        die();
    }

    closeConnection($conn);
}

function dumpProducts()
{
    $conn = getConnection();

    $stmt = 'DELETE FROM product;';

    if(!mysqli_query($conn, $stmt))
    {
        echo "Products NOT ABLE TO DUMP\n";
        die();
    }

    closeConnection($conn);
}

function getProducts()
{
    //use get_result & fetch_assoc
    $conn = getConnection();

    $sql = "SELECT * FROM product;";

    // prepare and excute a query to fetch all products from database
    $result = mysqli_query($conn, $sql);

    if(!$result)
    {
        echo "Error: Unable to get products";
        closeConnection($conn);
        die();
    }

    //store the fetch products in an assoc array
    $products = [];
    while ($row = mysqli_fetch_assoc($result))
    {
        $products[] = [
            'id' => $row['internalId'],
            'name' => $row['productName'],
            'vendor' => $row['vendor'],
            'vendorPhone' => $row['vendorPhone'],
            'quantity' => $row['quantity'],
            'lastPurchased' => $row['lastPurchased']
        ];
    }

    closeConnection($conn);

    return $products;
}

function uniqueID($id)
{
    $conn = getConnection();

    // Prepare a statement to check if any product has the given internalId
    $sql = "SELECT * FROM product WHERE internalId = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 's', $id);
    
    mysqli_stmt_execute($stmt);

    // Store the result
    mysqli_stmt_store_result($stmt);

   // Check if any row is found
    if (mysqli_stmt_num_rows($stmt) > 0) {
        closeConnection($conn);
        return false;
    } else {
        closeConnection($conn);
        return true;
    }
}


function closeConnection($conn){
    if(mysqli_close($conn)){
        return true;
    }else{
        echo "UNABLE TO CLOSE DATABASE!";
        die();
    }
}
?>
