<?php

function getQuiz($q){
    $filename = "quizzes/". $q . "_quiz.json";

    $data = @file_get_contents($filename);

    if(!$data){
        echo "INVALID FILE";
        die();
    }

    $data = json_decode($data, true);
    if($data == null){
        echo "FILE WAS INVALID JSON";
        die();

    }
    return $data;
}

function questionHTML($question){

    $output = "<label>" . $question['text'] . "</label><br>";
    $output .= "<select name='" . $question['id'] . "' required>";
    foreach($question['options'] as $o)
    {
        $output .= "<option value='" . $o . "'>" . $o . "</option>"; 
    }
    $output .= "</select><br>";
    return $output;
}

function getQuestion($id, $questions)
{
    foreach($questions as $question)
    {
        if($question['id'] == $id)
        {
            return $question;
        }
    }

    echo "answer all questions";
    die();
}

?>
