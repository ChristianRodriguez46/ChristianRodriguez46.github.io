<?php 

    function cleanData($data){
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }


    // Function to validate first name
    function validFname($fname)
    {
        // Check if the first name contains only letters using regular expression
        return preg_match("/^[a-zA-Z]+$/", $fname);
    }


    // Function to validate last name
    function validLname($lname)
    {
        // Check if the last name contains only letters using regular expression
        return preg_match("/^[a-zA-Z]+$/", $lname);
    }

    // Function to validate email
    function validEmail($email)
    {
        // Use the built-in filter_var function to validate email address
        if(filter_var($email, FILTER_VALIDATE_EMAIL) )
        { 
            return preg_match("/^[\w\.]+@([\w]+\.)+[\w]{2,4}$/", $email);
        }
        else {
            return false;
        }

        //preg match check if it has any character alphanumeric with  - or . 
        // it must include a @
    }

    // Function to validate phone number
    function validPnum($phone)
    {
        // Check if the phone number is in the format XXX-XXX-XXXX using regular expression
        return preg_match("/^\d{3}-\d{3}-\d{4}$/", $phone);
    }

    function validOrderNumber($orderNumber)
    {
        return preg_match("/^[0-9a-zA-Z]{10}+$/", $orderNumber);
    }

?>