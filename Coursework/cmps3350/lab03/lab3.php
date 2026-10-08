<?php
$param = $_GET['param'];

echo "param is: " . $param . "<br>";

if ($param == "hello") {
    echo "Hello student!<br>";
} else {
    $num = $param*3+4;
    echo "number:" . $num . "<br>";
}

echo "<br>";
echo "<img src=\"mydiagram8.gif\" style=width:600px;height:auto;/>";
?>