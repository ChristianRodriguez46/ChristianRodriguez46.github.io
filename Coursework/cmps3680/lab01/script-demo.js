    function validateForm(event){
        // Gets all form elements on the page
        let form = document.forms["contactForm"];
        var valid_form = true;

        // This function that checks if required fields is input
        function handleInvalidField(field){
            field.classList.add('error');
            valid_form = false;
        }

        var elements = contactForm.elements;
        for(var i = 0; i < elements.length; i++){
            elements[i].classList.remove('error');
        }

        // Defining an array of required fields
        var requiredFields =['fName', 'lName', 'email', 'comments'];

        // Iterate over the required fields
        requiredFields.forEach(function(fieldName){

            // Get the current field
            console.log('inside the for loop')
            var field = form[fieldName];

            // Check if the field value is empty or invalid
            if (!field.value.trim()) {
                console.log('check 1 F')
                handleInvalidField(field);
            } else {
                console.log('check 1 T')
            }
            // checks if field is email and if the value is invalid
            // checks if email has @ and . 
            if (fieldName === 'email'){ 
                if (!field.value.includes('@') || !field.value.includes('.')){   
                    console.log("check 2 F")
                    // If it is call function
                    handleInvalidField(field);
                }else{
                    console.log('check 2 T')
                }
            }
        });

        //log whether the form was submitted
        console.log("Form submitted successfully: " + valid_form);

        return valid_form;
    }
