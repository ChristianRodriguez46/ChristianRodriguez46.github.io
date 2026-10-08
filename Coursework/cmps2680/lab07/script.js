//wait for the page to load
window.addEventListener("load", function(){
    document.getElementById("userInput").addEventListener("keyup", generateMultiples)
});

function generateMultiples(){
    let multiplesDiv = document.getElementById("multiples");
    
    let error;
    let className;
    
    if(this.value === "" || isNaN(this.value)){
        //made p tag have class b 
        className = 'b'
        //gave the assign error text to error varible
        error  = "PLEASE ENTER A VALID NUMBER";
        //concatenate everything together then assign to 'multiples' div
      multiplesDiv.innerHTML = '<p class= "'+ className +'" >' + error + '</p>'; 
        return;
    }

    let base = parseInt(this.value);
    let nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12];

    //clears previous content (if else statement)
    document.getElementById("multiples").innerHTML = '';

    let html = '';
    for(let i = 0; i < nums.length; i++){
        let multiple = base * nums[i];
        //make div box alternate from a to b

        if( i % 2 == 0){
            className = 'a';
        }else{
            className = 'b';
        }

        html += '<p class= "'+ className +'" >' + multiple + '</p>'; 
    }
    multiplesDiv.innerHTML = html;
    console.log("It works");
}
