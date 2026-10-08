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
        if(filter_var($email, FILTER_VALIDATE_EMAIL))   //soft check
        {
            return preg_match("/^[\w\.]+@[\w]+\.+[\w]{2,4}$/", $email);  //hard check
        }
        else {
            return false;
        }
        
    }

    // Function to validate address
    function validAddress($address)
    {
        // Check if the address contains only letters, numbers, spaces, and commas using regular expression
        return preg_match("/^[a-zA-Z0-9\s,]+$/", $address);
    }

    // Function to validate address
    function validCity($city)
    {
        // Check if the address contains only letters, numbers, spaces, commas, hash, period, and hyphen using regular expression
        return preg_match("/^[a-zA-Z]+$/", $city);
    }
    // Function to validate address
    function validZip($zip)
    {
        // Check if the address contains only numbers using regular expression
        return preg_match("/^[0-9]{5}+$/", $zip);
    }
    // Function to validate phone number
    function validPnum($phone)
    {
        // Check if the phone number is in the format XXX-XXX-XXXX using regular expression
        return preg_match("/^\d{3}-\d{3}-\d{4}$/", $phone);
    }

    function validMake($make)
    {
        return $make !== "" ? true : false;
    }

    function validModel($model)
    {
        return $model !== "" ? true : false;
    }

    function validYear($year)
    {
        return preg_match("/^[0-9]{4}+$/", $year);
    }

    // Function to validate date
    function validDate($date)
    {
        // Check if the date is in the format YYYY-MM-DD using regular expression
       return $date !== "" ? true : false;
    }

    function validTime($time)
    {

        if($time !== "")
        { 
            // Create a DateTime object with the input time
            $time_obj = DateTime::createFromFormat('H:i', $time);

            // Format the time in 12-hour format with AM/PM
            $converted_time = $time_obj->format('g:ia');  
            
            $time = $converted_time;
            
            return $time;
        }
        else 
        {
            return false;
        }
    }

    function validateOrder($order) {
        $requiredFields = ['package', 'I_services', 'E_services'];

        foreach ($requiredFields as $field) {
            if (isset($order[$field]) && !empty($order[$field])) {
                return true;
            }
        }

        return false;
    }
?>
