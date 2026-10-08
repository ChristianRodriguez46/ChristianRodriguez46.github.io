// GLOBAL VARIABLE TO STORE RANDOM NUMBER
let number = null;

// HELPER FUNCTION TO GENERATE A RANDOM NUMBER
function genRandom(min, max) {
    return Math.floor(Math.random() * (max - min) ) + min;
}

// TODO #2: Define startGame() and playGame() functions here
function startGame(){
    number = genRandom(-10,10);

    let element = document.getElementById('clues');
    element.innerHTML = "";
    let clues = "";

    if(number >= -5  && number <= 5){
        clues += "Number is in between -5 and 5<br>" 
    }else{
        clues += "Number is less than -5 greater than 5<br>"
    };
    if((number % 2) == 0 ){
        clues += "Number is even<br>"
        clues += "Number is divisble by 2<br>"
    }else{
        clues += "Number is odd<br>"
        clues += "Number is not divisble by 2<br>"
    };
    if(number > 0 ){
        clues += "Number is positive<br>"
    }else{
        clues += "Number is negative<br>"
    };

    element.innerHTML += clues;
    console.log("INSIDE START GAME FUNCTION");
}

function playGame() {
    //If New Game was not pressed prompt an alert
    if(number == null){
        window.alert('You must click "New Game"');
        return;
    }

    let guess = window.prompt("Enter your guess: ");

    //If else to determine if guess is correct or wrong
    if(guess == number) {
        window.alert("Congratulations! You won! The number was: " + number)
    }else{
        window.alert("Sorry, you lost. The number was: "+ number);
    };

    number = null;
    console.log("INSIDE PLAY GAME FUNCTION");
}

// WAIT FOR THE PAGE TO LOAD BEFORE ADDING LISTENERS
window.addEventListener("load", function(){

    // TODO #1: Set listeners for buttons here

    document.getElementById("newGame").addEventListener("click", startGame);
    document.getElementById("guessNumber").addEventListener("click", playGame);
});
