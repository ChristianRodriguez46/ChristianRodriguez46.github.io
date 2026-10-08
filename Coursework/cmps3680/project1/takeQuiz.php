<?php
date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

require_once "./quizTools.php";


if(!isset($_GET['q']) || !preg_match('/^[a-z]{3}$/', $_GET['q']))
{
    echo "YOU MUST SET A QUIZ TYPE<br>";
    echo "in URL put ?q=  mus, geo, or mov";
    die(); 
}

$q = $_GET['q'];

$quiz = getQuiz($q);


?>
<head>
<title>Project 1</title>
<link type="text/css" rel="stylesheet" href="./styles/<?=$q?>.css">
</head>

<header>
<h1><?=$quiz['name']?></h1>
</header>


<div class="f-container">
<form method="post" action="gradeQuiz.php?q=<?=$q?>">
<?php

    foreach($quiz['questions'] as $question)
    {
       echo questionHTML($question);
    }
?>
<br>
<input type="submit" value="Submit">
</form>
<div>


