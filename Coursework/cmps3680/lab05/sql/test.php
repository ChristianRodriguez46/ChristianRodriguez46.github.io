<?php
require_once('sqlTools.php');

$db = getConnection();
echo "CONNECTION ESTABLISHED!\n";

closeConnection($db);
echo "CONNECTION CLOSED!\n";
?>
