<?php 
require_once "./scripts/mail.php";   //validate functions
require_once "./sql/sqlTools.php";

$mail_To= 'crodriguez4643@gmail.com';

$mail_message = "";
$error = "";

// Sanitize and process form data
foreach ($_POST as $key => $value ) 
{
    // Clean data
    $value = cleanData($value);
    
    // Check for specific keys and handle accordingly
    if ($key == "pnum") 
    {
        if(!empty($value))
        {
            if(validPnum($value)) 
            {
                $mail_message .= "Phone Number: $value\n";
            } else {
                $error .= "Invalid phone number <br>";
            }
        }
    } 
    if ($key == "orderNumber") 
    {
        if(isset($key) && !empty($value))
        {
            if (validOrderNumber($value)) 
            {
                if (checkOrderNumber($value)) {
                    $mail_message .= "Order Number: $value\n";
                } else {
                    $error .= "There is no appointment with the order number: $value<br>";
                }
            }
            else {
                $error .= "Invalid order number input<br>";
            }

        }
    }
    if ($key == "fname") 
    {
        if (!empty($value) && validFname($key)) 
        {
            $mail_message .= "First Name: $value \n";
        } else {
            $error .= "Invalid first name<br>";
        }
    } 
    if ($key == "lname") {
        if (!empty($value) && validLname($key)) {
            $mail_message .= "Last Name: $value\n";
        } else {
            $error .= "Invalid last name<br>";
        }
    }
    if ($key == "email") {
        if (!empty($value) && validEmail($value)) {
            $mail_message .= "Email: $value\n";
        } else {
            $error .= "Invalid email address<br>";
        }
    }
    if ($key == "message") {
        if (!empty($value)) {
            $mail_message .= "Message: $value\n";
        } else {
            $error .= "Message cannot be empty<br>";
        }
    }
}



// If there are no errors, send the email
if (empty($error)) {
    $mail_subject = 'Contact Form from: ' . $_POST['fname'] . ' ' . $_POST['lname'];
    $mail_header = [
        'From' => $_POST['email'],
        'Reply-To' => $_POST['email'],
        'X-Mailer' => 'PHP/' . phpversion()
    ];
    
    // Send email
    mail($mail_To, $mail_subject, $mail_message, $mail_header);
}
?>

<!doctype html>
<html>
    <head>
        <title>Contact</title>
        <!--bootstrap-->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet"> 
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>

        <!--Jquery-->
        <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
        <!--scipt and Css-->
        <!-- <script src="./scripts/contact.js"></script> -->
        <link rel='stylesheet' type='text/css' href="./styles/contact.css">
    </head>

    <body>
        <nav class="navbar naxvbar-expand-sm bg-dark navbar-dark">
            <div class="container-fluid" id="navContainer">
                <a class="navbar-brand" href="./home.html">Wise Choice Detailing</a>
                <button class="navbar-toggler collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#xx" style="cursor:pointer" fdprocessedid="kwg44" aria-expanded="false">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="navbar-collapse collapse" id="xx">
                    <ul class="navbar-nav" id="navList">

                        <li class="nav-item">
                            <a class="nav-link" href="./home.html">Home</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./service.html">Services</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./booking.php">Book your detailing</a>
                        </li>    

                        <li class="nav-item">
                            <a class="nav-link" href="./gallery.html">Gallery</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./contact.html">Contact Us</a>
                        </li>
                    </ul>

                    <form role="search">
                        <input class="form-control" type="search" placeholder="Search" aria-label="Search">
                    </form>
                </div>
            </div>
        </nav>
        <h1 id="c-header"> CONTACT US</h1>
        <div id="container">
            <div id="form">
                <?php
                    if (!empty($error))
                    { 
                        echo $error;
                    }
                    else 
                    {
                        echo "<p>Thank you for your message ". $_POST['fname'] ."!</p>";
                        echo "<p>Our team will get back to you shortly at " . $_POST['email'] . "</p>";
                    }
                ?>
            </div>
        </div>

        <footer class="py-3 my-4">
            <ul class="nav justify-content-center border-bottom pb-3 mb-3">
                <li class="nav-item"><a href="./home.html" class="nav-link px-2 text-body-secondary">Home</a></li>
                <li class="nav-item"><a href="./service.html" class="nav-link px-2 text-body-secondary">Services</a></li>
                <li class="nav-item"><a href="./booking.php" class="nav-link px-2 text-body-secondary">Booking</a></li>
                <li class="nav-item"><a href="./gallery.html" class="nav-link px-2 text-body-secondary">Gallery</a></li>
                <li class="nav-item"><a href="./contact.html" class="nav-link px-2 text-body-secondary">Contact Us</a></li>
            </ul>

            <p class="text-center text-body-secondary"> &copy; 2023 Wise Choice Detailing. All rights reserved.</p>

        </footer>
    </body>
</html>