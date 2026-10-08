<?php

date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

function htmlError($error){
    http_response_code(400);
    die($error);
}

function htmlRes($title, $body){
    header('Content-Type: text/html; charset=utf-8');
    http_response_code(200);

    $res  = "<html><head><title>$title</title></head>";
    $res .= "<body><p>$body</p></body></html>";

    die($res);
}

?>