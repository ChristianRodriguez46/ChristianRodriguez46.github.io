<?php
require_once("lib.php");

$required = ["find", "replace", "text"];

$raw = file_get_contents('php://input');
$data = json_decode($raw, true);

if (!isset($data)) {
    htmlError("NO POST DATA");
}

foreach ($required as $r) {
    if (empty($data[$r])) {
        htmlError("$r NOT SET");
    }
}

$q = '/\b' . preg_quote($data['find']) . '\b/i';
$r = $data['replace'];
$output = preg_replace_callback(
    $q,
    fn() => "<span style='background-color: yellow'>$r</span>",
    $data["text"]
);

htmlRes("SEARCH RESULTS", nl2br($output));

?>