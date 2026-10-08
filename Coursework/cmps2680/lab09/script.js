window.addEventListener("load", function(){

    const queryString = window.location.search;
    //ostring means output string
    let html = "";

    if(queryString != ""){
        const urlParams = new URLSearchParams(queryString);
        
        //grabs values from forms
        const fName = urlParams.get('fName');
        const lName = urlParams.get('lName');
        const email = urlParams.get('email');
        const birthday = urlParams.get('birthday');
        
        //build an output string
        html += "First Name: " + fName + "<br>"
        html += "Last Name: " + lName + "<br>"
        html += "Email: " + email + "<br>"
        html += "Birthday: " + birthday + "<br>";
        
        //writes 'output string' to the "output div"
        document.getElementById("Output").innerHTML = html;

    };
});
