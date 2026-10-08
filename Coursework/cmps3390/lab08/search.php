<?php
require_once("lib.php");

$required = ["search", "text"];

$raw = file_get_contents('php://input');
$data = json_decode($raw, true);

if(!isset($data)){
    htmlError("NO POST DATA");
}

foreach ($required as $r) {
    if(empty($data[$r])){
        htmlError("$r NOT SET");
    }
}

$q = '/\b' . preg_quote($data['search']) . '\b/i'; 

$output = preg_replace_callback(
    $q, 
    fn($match) => "<span style='background-color: yellow'>$match[0]</span>",
    $data["text"]
);


// $words = explode(' ', $data['text']);

// $output = '';
// foreach($words as $word){
//     if($word == $data['search']){
//         $output .= " <span style='background-color: yellow'>$word</span> ";
//     }else{
//         $output .= " $word ";
//     }
// }

htmlRes("SEARCH RESULTS", nl2br($output));

?>
