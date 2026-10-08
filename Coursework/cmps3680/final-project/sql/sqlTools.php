<?php 
require_once('config.php');


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

function closeConnection($conn){
    if(mysqli_close($conn)){
        return true;
    }else{
        echo "UNABLE TO CLOSE DATABASE!";
        die();
    }
}

//generate a random order number
function generateRandomString($length = 10) {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[random_int(0, $charactersLength - 1)];
    }
    return $randomString;
}


function addOrder($order)
{
    // Generate a unique order number
    $ordernumber = generateRandomString();

    // Extract exterior services and interior services from the order array
    $exterior_services = isset($order['E_services'])? json_encode($order['E_services']) : null;
    $interior_services = isset($order['I_services'])? json_encode($order['I_services']) : null;

    // Insert appointment and service data into the database
    $result = insertOrderData($ordernumber, $order, $exterior_services, $interior_services);

    // Return a response object indicating whether the order was added successfully or not
    if ($result) {
        
        // If the order was added successfully, add the generated order number to the order array
         $order['ordernumber'] = $ordernumber;

         return $order['ordernumber'];
    } else {
        
        // If the order was not added successfully, return a response object with an error message
        return (object) [
            'success' => false, // Indicates that the order was not added successfully
            'message' => 'Error adding order' // Error message
        ];
    }
}

function insertOrderData($ordernumber, $order, $exterior_services, $interior_services)
{
    $conn = getConnection();
    $sql = <<< SQL
        INSERT INTO appointments
        (ordernumber, fname, lname, email, address, city, zip, phone, make, model, year, date, time, package, exterior_services, interior_services)
        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
    SQL;

    $stmt = mysqli_prepare($conn, $sql);
    mysqli_stmt_bind_param(
        $stmt,
        'ssssssssssssssss',
        $ordernumber,
        $order['fname'],
        $order['lname'],
        $order['email'],
        $order['address'],
        $order['city'],
        $order['zip'],
        $order['phone'],
        $order['make'],
        $order['model'],
        $order['year'],
        $order['date'],
        $order['time'],
        $order['package'],
        $exterior_services,
        $interior_services
    );

    if (!mysqli_stmt_execute($stmt)) {
        error_log(mysqli_stmt_error($stmt));
        return false;
    }

    closeConnection($conn);
    return true;
}


// For User, gets all of the users orders

function getUserOrder($email)
{
    // Connect to the database
    $conn = getConnection();

    // Query to fetch all orders
    $sql = "SELECT * FROM appointments WHERE email = ?";
    
    // Prepare the statement
    $stmt = mysqli_prepare($conn, $sql);
    
    // Bind parameters
    mysqli_stmt_bind_param($stmt, 's', $email);
    
    // Execute the statement
    mysqli_stmt_execute($stmt);

    // Check for errors
    if(mysqli_stmt_errno($stmt)) {
        throw new Exception("Error: Unable to execute statement. " . mysqli_stmt_error($stmt));
    }

    // Store the fetched orders in an associative array
    $orders = [];
    mysqli_stmt_bind_result($stmt, $ordernumber, $fname, $lname, $email, $address, $city, $zip, $phone, $make, $model, $year, $date, $time, $package, $exterior_services, $interior_services);
    while (mysqli_stmt_fetch($stmt))
    {
        // Decode JSON strings for exterior_services and interior_services
        $exterior_services = isset($exterior_services) ? json_decode($exterior_services, true) : [];
        $interior_services = isset($interior_services) ? json_decode($interior_services, true) : [];

        // Add order details to the array
        $orders[] = [
            'ordernumber' => $ordernumber,
            'fname' => $fname,
            'lname' => $lname,
            'email' => $email,
            'address' => $address,
            'city' => $city,
            'zip' => $zip,
            'phone' => $phone,
            'make' => $make,
            'model' => $model,
            'year' => $year,
            'date' => $date,
            'time' => $time,
            'package' => $package,
            'E_services' => $exterior_services,
            'I_services' => $interior_services
        ];
    }

    // Close the statement
    mysqli_stmt_close($stmt);

    // Close the database connection
    closeConnection($conn);

    // Return the array of orders
    return $orders;
}


// For Admin
function getOrder()
{
    // Connect to the database
    $conn = getConnection();

    // Query to fetch all orders
    $sql = "SELECT * FROM appointments;";

    // Execute the query
    $result = mysqli_query($conn, $sql);

    // Check for errors
    if(!$result)
    {
        echo "Error: Unable to get orders";
        closeConnection($conn);
        die();
    }

    // Store the fetched orders in an associative array
    $orders = [];
    while ($row = mysqli_fetch_assoc($result))
    {
        // Decode JSON strings for exterior_services and interior_services
        $exterior_services = isset($row['exterior_services']) ? json_decode($row['exterior_services'], true) : [];
        $interior_services = isset($row['interior_services']) ? json_decode($row['interior_services'], true) : [];

        // Add order details to the array
        $orders[] = [
            'ordernumber' => $row['ordernumber'],
            'fname' => $row['fname'],
            'lname' => $row['lname'],
            'email' => $row['email'],
            'address' => $row['address'],
            'city' => $row['city'],
            'zip' => $row['zip'],
            'phone' => $row['phone'],
            'make' => $row['make'],
            'model' => $row['model'],
            'year' => $row['year'],
            'date' => $row['date'],
            'time' => $row['time'],
            'package' => $row['package'],
            'E_services' => $exterior_services,
            'I_services' => $interior_services
        ];
    }

    // Close the database connection
    closeConnection($conn);

    // Return the array of orders
    return $orders;
}

function uniqueOrderNumber($ordernumber)
{
    $conn = getConnection();

    // Prepare a statement to check if any product has the given ordernumber
    $sql = "SELECT * FROM appointments WHERE ordernumber = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 's', $ordernumber);
    
    mysqli_stmt_execute($stmt);

    // Store the result
    mysqli_stmt_store_result($stmt);

    // Check if any row is found
    $isUnique = mysqli_stmt_num_rows($stmt) === 0;

    closeConnection($conn);

    return $isUnique;
}

// Added for the contact form
function checkOrderNumber($ordernumber)
{
    $conn = getConnection();

    // Prepare a statement to check if any product has the given ordernumber
    $sql = "SELECT * FROM appointments WHERE ordernumber = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 's', $ordernumber);
    
    mysqli_stmt_execute($stmt);

    // Store the result
    mysqli_stmt_store_result($stmt);

    // Check if any row is found
    $exist = mysqli_stmt_num_rows($stmt) === 1;

    closeConnection($conn);

    return $exist;
}


function getUniqueOrder($ordernumber)
{
    // Connect to the database
    $conn = getConnection();

    // Prepare a statement to check if any product has the given ordernumber
    $sql = "SELECT * FROM appointments WHERE ordernumber = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 's', $ordernumber);
    
    mysqli_stmt_execute($stmt);

    // Get the result
    $result = mysqli_stmt_get_result($stmt);
    
    // Store the fetched order details in an associative array
    $order = mysqli_fetch_assoc($result);

    // Close the statement
    mysqli_stmt_close($stmt);

    // Close the database connection
    closeConnection($conn);

    // Print the unique order
    printUniqueOrder($order);
}

function printUniqueOrder($order)
{
        // Check if there are any orders
    if(empty($order)) {
        echo "No orders found.";
    }else{
        // Loop through each order and print its details
        echo "<div id='output' class='col-md'>";
        echo "<h6>Inside personal info</h6>";
        echo "Order Number: " . $order['ordernumber'] . "<br>";
        echo "First Name: " . $order['fname'] . "<br>";
        echo "Last Name: " . $order['lname'] . "<br>";
        echo "Email: " . $order['email'] . "<br>";
        echo "Address: " . $order['address'] . "<br>";
        echo "City: " . $order['city'] . "<br>";
        echo "Zip Code: " . $order['zip'] . "<br>";
        echo "Phone: " . $order['phone'] . "<br>";
        echo "Date: " . $order['date'] . "<br>";
        echo "Time: " . $order['time'] . "<br>";
        if (isset($order['package'])) {
            echo "Package: " . $order['package'] . "<br>";
        }
        echo "</div>";
        echo "<br>";

            // Print exterior services


        if(isset($order['exterior_services']) || isset($order['interior_services'])) 
        {
            echo "<div id='Is_container' class = 'col-md'>";
            echo "<h6>Individual services</h6>";
            echo "<ul>";

            if (isset($order['exterior_services'])) 
            {

                $exterior_service = json_decode($order['exterior_services'], true);
                
                echo "Exterior Services: <br>";
                foreach ($exterior_service as $key => $value)
                {
                    echo "<li>- ". $value . "</li>";
                }
            }

            if (isset($order['interior_services'])) 
            {
                $interior_service = json_decode($order['interior_services'], true);
                
                echo "Interior Services: <br>";
                foreach ($interior_service as $key => $value ) 
                {
                    echo "<li>- ". $value . "</li>";
                }
            }
            echo "</ul>";
            echo "</div>";
            echo "<br>";
        }else
        {
            echo "failed first check";
        };
        
    }

}

function removeOrder($ordernumber)
{
    $conn = getConnection();

    $sql = "DELETE FROM appointments WHERE ordernumber = ?";

    $stmt = mysqli_prepare($conn, $sql);

    if(!$stmt){
        echo "STATEMENT NOT PREPARED";
        die();
    }

    mysqli_stmt_bind_param(
        $stmt,
        's',
        $ordernumber
    );

    if(!mysqli_stmt_execute($stmt)){
        echo "remove appointment failed";
        die();
    }

    closeConnection($conn);
}

function dumpOrders()
{
    $conn = getConnection();

    $stmt = 'DELETE FROM appointments;';

    if(!mysqli_query($conn, $stmt))
    {
        echo "appointments NOT ABLE TO DUMP\n";
        die();
    }

    closeConnection($conn);
}


// login page

function uniqueUsername($Username)
{
    $conn = getConnection();

    // Prepare a statement to check if any product has the given ordernumber
    $sql = "SELECT * FROM users WHERE Username = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 's', $Username);
    
    mysqli_stmt_execute($stmt);

    // Store the result
    mysqli_stmt_store_result($stmt);

    // Check if any row is found
    $isUnique = mysqli_stmt_num_rows($stmt) === 0;

    closeConnection($conn);

    return $isUnique;
}

//A check to so if there
function PasswordCheck($username, $password)
{
    $conn = getConnection();

    // Prepare a statement to check if any product has the given ordernumber
    $sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    
    $stmt = mysqli_prepare($conn, $sql);
    
    mysqli_stmt_bind_param($stmt, 'ss', $username, $password);
    
    mysqli_stmt_execute($stmt);

    // Store the result
    mysqli_stmt_store_result($stmt);

    // Check if any row is found
    $isUnique = mysqli_stmt_num_rows($stmt) === 0;

    closeConnection($conn);

    return $isUnique;
}


function addUser($Signup, $password)
{
    $conn = getConnection();
    $sql = <<< SQL
        INSERT INTO users
        (username, email, password)
        VALUES (?,?,?)
    SQL;

    $stmt = mysqli_prepare($conn, $sql);
    mysqli_stmt_bind_param(
        $stmt,
        'sss',
        $Signup = ['username'],
        $Signup = ['email'],
        $password
    );

    if (!mysqli_stmt_execute($stmt)) {
        error_log(mysqli_stmt_error($stmt));
        echo "failed to add user";
        return false;
    }

    closeConnection($conn);
    return true;
}


?> 
