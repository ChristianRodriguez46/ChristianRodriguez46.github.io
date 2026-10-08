//wait for the page to load
window.addEventListener("load", function(){
    //if button is click call "addTodo" function
    document.getElementById("submit").addEventListener("click", addTodo);
    //If the "enter" key is pressed then call "addTodo" function
    document.getElementById("todo").addEventListener("keypress", function(event){
        //This to check if user pressed the enter key
        if (event.key == "Enter" ){
            addTodo();
        };
    });
});

function addTodo(){
    let value = document.getElementById("todo").value;
    let listItem = document.createElement("div");
    listItem.setAttribute("class","listItem");
    listItem.innerHTML = value;
    listItem.addEventListener("click", listItem.remove);
    document.getElementById("list").appendChild(listItem);
    document.getElementById("todo").value = "";
    console.log("addTodo function works!");
    
}
