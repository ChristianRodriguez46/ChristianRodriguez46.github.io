<?php
// echo phpversion();

header('Content-Type: application/json; charset=utf-8');

$data = [
    'name' => "bob",
    'pet' => "cat",
];

$joutput = json_encode($data);
die($joutput);
?>
