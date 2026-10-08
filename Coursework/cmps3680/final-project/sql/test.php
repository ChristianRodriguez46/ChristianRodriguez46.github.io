<?php
require_once('./sqlTools.php');
require_once('../validate.php');

//require_once('sqlTools .php');


//echo "random string " . generateRandomString();

//echo "\n";

// // Create an order
// $order1 = [
//     'fname' => 'John',
//     'lname' => 'Doe',
//     'email' => 'john@example.com',
//     'address' => '123 Main St',
//     'car' => 'Toyota Camry',
//     'phone' => '123-456-7890',
//     'date' => '2024-05-05 10:00:00',
//     'package' => 'Gold',
//     'E_services' => ['Full Service Hand Wash', 'Wheel Clean & Shine', 'Engine Bay'],
//     'I_services' => ['Vaccum & Clean', 'Leather Clean & Condition', 'Door, Dash & Plastic Condition']
// ];
// // Create an order
// $order2 = [
//     "fname" => "bob",
//     "lname" => "Doe",
//     "email" => "bobdoe@example.com",
//     "address" => "123 Main St",
//     "car" => "Toyota Camry",
//     "phone" => "555-123-4567",
//     "date" => "2024-05-01",
//     "package" => "Gold",
//     "E_services" => ['Wash', 'Wax', 'condition'],
//     "I_services" => ['Vacuum', 'Detailing', 'steaming']
// ];

// // Add the order
// addOrder($order1);
// echo "order added";

// // Add the order
// addOrder($order2);
// echo "order added";

/*
if(validFname("bob")){
    echo  "bob is a valid first name\n"; 
}else{
    echo "bob is not a valid first name\n";
}

if(validFname("b0b")){
    echo "b0b is a valid first name\n"; 
}else{
    echo "b0b is not a valid first name\n";
}


if(validFname("123")){
    echo "123 is a valid first name\n"; 
}else{
    echo "123 is not a valid first name\n";
}

if(validFname("1?3")){
    echo "1?3 is a valid first name\n"; 
}else{
    echo "1?3 is not a valid first name\n";
}

if(validLname("Martin")){
    echo "Martin is a valid last name\n"; 
}else{
    echo "Martin is not a valid last name\n";
}

if(validLname("Rob")){
    echo "Rob is a valid last name\n"; 
}else{
    echo "Rob is not a valid last name\n";
}

if(validLname("R?23#b")){
    echo "R?23#b is a valid last name\n"; 
}else{
    echo "R?23#b is not a valid last name\n";
}

if(validLname("134fd")){
    echo "134fd is a valid last name\n"; 
}else{
    echo "134fd is not a valid last name\n";
}

if(validEmail("rob")){
    echo "Rob is a valid email\n"; 
}else{
    echo "Rob is not a valid email\n";
}

if(validEmail("rob@example.com")){
    echo "Rob@example.com is a valid email\n"; 
}else{
    echo "Rob@example.com is not a valid email\n";
}

if(validEmail("rob1342@example.com")){
    echo "Rob1342@example.com is a valid email\n"; 
}else{
    echo "Rob1342@example.com is not a valid email\n";
}

if(validEmail("rob@gmail")){
    echo "Rob@gmail is a valid email\n"; 
}else{
    echo "Rob@gmail is not a valid email\n";
}
*/
//removeOrder("Q492e2mrcr");
//dumpOrders();


//test for printing order
echo "Got a unique order <br>";
getUniqueOrder("Fl8Q1ztP9i");
echo "<br>";





// Get the orders from the database
echo "<h1>Got all orders</h1>";
$orders = getOrder();


// Check if there are any orders
if (empty($orders)) {
    echo "No orders found.";
} else {
    echo "<div id = 'container'>";
    // Loop through each order and print its details
    foreach ($orders as $order) {
        echo "<div id='information'>";
        
        echo "Order Number: " . $order['ordernumber'] . "<br>";
        echo "First Name: " . $order['fname'] . "<br>";
        echo "Last Name: " . $order['lname'] . "<br>";
        echo "Email: " . $order['email'] . "<br>";
        echo "Address: " . $order['address'] . "<br>";
        echo "Phone: " . $order['phone'] . "<br>";
        echo "Date: " . $order['date'] . "<br>";
        echo "Package: " . $order['package'] . "<br>";
        
        echo "</div>";
        
        // Print exterior services
        // if(isset($order['E_services']) && isset($order['I_services'])) {
        if(!empty($order['E_services']) || !empty($order['I_services'])) {

            echo "<div id = 'services'>";
            
            if(!empty($order['E_services'])){
                echo "Exterior Services: <br>";
                foreach ($order['E_services'] as $exterior_service) {
                    echo "- " . $exterior_service . "<br>";
                }
            }

            // Print interior services
            if(count($order['I_services']) !== 0){
                echo "Interior Services: <br>";
                foreach ($order['I_services'] as $interior_service) {
                    echo "- " . $interior_service . "<br>";
                }
            }
        
            echo "</div>";
            echo "<br>";
        }
    }
    echo "</div>";
}
 
?>
