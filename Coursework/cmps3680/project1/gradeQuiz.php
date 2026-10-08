<?php
date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

require_once "./quizTools.php";


if(!isset($_GET['q']) || !preg_match('/^[a-z]{3}$/', $_GET['q']))
{
    echo "YOU MUST SET A QUIZ TYPE";
    die(); 
}
//$q = $_GET['q']; 
$quiz = getQuiz($_GET['q']);

$answers = $_POST;

/*if(!isset($answers)){
    echo "Post answers are not grabbed from post";
    die();
}else
{
    foreach($answers as $answer)
    {
        echo $answer;
    }
}*/ // ^debug function to to see if $annswer has post data and if so print the values
if(empty($answers))
{
    
    echo "Please answer all quiestions.";
       die();
}else{
    foreach ($answers as $answer){
        if ($answer == ''){
            echo "Please answer all quiestions.";
            die();
        }
    }
}
?>
<head>
<title>Project 1</title>
<link type="text/css" rel="stylesheet" href="./styles/result.css">
</head>
<div id="container">

<header>
<h1><?=$quiz['name']?> Results</h1>
</header>

<div class="f-container">

<?php
foreach($answers as $key => $value)
{
    $question = getQuestion($key, $quiz['questions']);  //$quiz['questions'] goes 
                                                        //into questions array
                                                        // question['answer'] looks at the answer in questions array
    
    if($question['answer'] == $value){
        echo "<h2>" . $key . ": CORRECT!</h2>";
    }else{
        echo "<h2>" . $key .". INCORRECT</h2>";
    }

    echo "<p> Your answer is: " .  $value . "</p>";
    echo "<p> The correct answer is: " . $question['answer'] . "</p>";
}

?>
</div>
</div>
