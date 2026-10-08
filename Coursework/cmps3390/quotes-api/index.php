<?php
date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
// ini_set('display_errors', 1);

// WHITELIST
$categories = ["book", "movie", "game"];

//JSON ERROR/RESPONSE
function jsonErr($msg) {
    header('Content-Type: application/json');
    http_response_code(400);
    $res = json_encode(["error" => $msg]);
    die($res);
}
function jsonRes($quote) {
    header('Content-Type: application/json');
    http_response_code(200);
    $res = json_encode($quote);
    die($res);
}

//VALIDATION
if(!isset($_GET) || empty($_GET['category'])) {
    jsonErr("No category provided");
} elseif (!in_array($_GET['category'], $categories)) {
    jsonErr("Invalid category provided");
}

// COMPLETE API COMPLETE
$category = $_GET['category'];
$qdata = file_get_contents("docs/$category.json");
$qjson = json_decode($qdata, true);
$i = rand(0, count($qjson) - 1);

jsonRes($qjson[$i]);

/*
echo json_encode($qjson[$i]);
echo "<br>";
print_r($qjson[$i]);
*/
?>