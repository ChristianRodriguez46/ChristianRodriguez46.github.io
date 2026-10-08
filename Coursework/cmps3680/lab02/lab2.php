<?php
date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);


define("TITLE", "Lab 2");
define("CSS", "./style.css");

$firstName = "Christian";

//Define a function to generate a multiplication table
function generateMultiplicationTable(){

    //loop through the rows of the table
    for($i = 1; $i <= 10; $i++){
        //start a new row
        echo "<tr>";
        
        //loop through the columuns of the current row
        for($j = 1; $j <= 10; $j++){
            //add a cell to the current with the product of the current row and column numbers
            echo "<td>" . ($i * $j) . "</td>"; //
        }
        //end the current row
        echo "</tr>";
    }
}
?>

<html>
<head>
  <title><?= TITLE ?></title>
  <link rel="stylesheet" type="text/css" href="<?= CSS ?>">
</head>
<body>
<h1><?= TITLE ?></h1>
<?php
if(isset($firstName) && isset($lastName))
{
    echo "<h2>" . "</h2>";
}else{
    error_log("One variable is not defined");
}
?>
<div id="container">
<table>
<?php 
generateMultiplicationTable(); // call the function to display table
?> 
</table>
</div>
<div id="lorem">
<?php
$loremText = file_get_contents("lorem.txt");
echo nl2br($loremText);
?>
</div>
</body>
</html>
