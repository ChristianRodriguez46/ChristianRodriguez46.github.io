// Wait for the DOM content to be fully loaded before executing the script
document.addEventListener("DOMContentLoaded", function () {
    
    // Get the query string from the URL
    const queryString = window.location.search;

    // Check if there are query parameters in the URL
    if (queryString !== "") {
        
        // Parse the query string into a URLSearchParams object
        const urlParams = new URLSearchParams(queryString);

        // Build an output string based on the retrieved values
        let html = "";
        html += displayPersonalInfo(urlParams);

        // Display the output string in the "output" div
        document.getElementById("output").innerHTML = html;

        // Call the unified function to display checked values
        displayCheckedValues(urlParams);
    }
});

// Function to check form conditions before submission
function submitForm() {
    
    // Check if the form is valid
    if (validateForm()) {
    
        // Continue with your existing form submission logic
        return true;  // Allow form submission
    
    } else {
        
        // Stop form submission if validation fails
        return false;
    }
}

// Function to validate the form before submission
function validateForm() {

    // Get the selected package radio button
    const p_service = document.querySelector('input[name="p_service"]:checked');

    // Get all selected checkboxes for individual services
    const selectedCheckboxes = document.querySelectorAll('input[name="I_serv"]:checked');

    // Check if a package and at least one checkbox are selected
    if (!p_service && selectedCheckboxes.length === 0) {
    
        // Display an alert if validation fails
        window.alert("Select a service");
        return false;
    }

    // Return true if validation passes
    return true;
}

// Unified function to display personal information
function displayPersonalInfo(urlParams) {
    
    let html = "";
    
    const fname = urlParams.get('fname');
    const email = urlParams.get('email');
    const address = urlParams.get('address');
    const car = urlParams.get('car');
    const date = urlParams.get('date');
    const p_service = urlParams.get('p_service');

    if (fname) {
        html += "Name: " + fname + "<br>";
    }

    if (email) {
        html += "Email: " + email + "<br>";
    }

    if (address) {
        html += "Address: " + address + "<br>";
    }

    if(car){
        html += "car: " + car + "<br>";
    }

    if (date) {
        // Format the date and time
        const formattedDate = formatDateTime(date);
        html += "Date: " + formattedDate + "<br>";
    }

    if (p_service) {
        html += "Package: " + p_service + "<br>";
    }

    return html;
}

// Function to format date and time
function formatDateTime(dateTimeString) {
    
    const options = {
        year: 'numeric',
        month: '2-digit',
        day: '2-digit',
        hour: 'numeric',
        minute: '2-digit',
        hour12: true
    };

    // Parse the input dateTimeString and format it
    const formattedDateTime = new Date(dateTimeString).toLocaleString('en-US', options);

    return formattedDateTime.replace(',', ' T:');
}

// Unified function to display checked checkboxes and individual services
function displayCheckedValues(urlParams) {

    // Initialize an array to store the values of checked checkboxes and individual services
    let selectedValues = [];

    // Get all checkboxes on the page
    let checkboxes = document.querySelectorAll('input[type="checkbox"]');

    // Loop through each checkbox
    checkboxes.forEach(function (checkbox) {
    
        // Check if the checkbox is checked
        if (checkbox.checked) {
            // Add the value of the checked checkbox to the array
            selectedValues.push(checkbox.value);
        }
    });

    // Additional block for displaying individual services
    const selectedIndividualServices = urlParams.getAll('I_serv');
    
    if (selectedIndividualServices.length > 0) {
        selectedValues = selectedValues.concat(selectedIndividualServices);
    }

    // Check if there are selected values
    if (selectedValues.length > 0) {
        
        // Build an HTML list based on the selected values
        let output = '<h6>Individual Services:</h6> <ul>';
        
        selectedValues.forEach(function (value) {
            output += '<li>' + value + '</li>';
        });
        output += '</ul>';

        // Display the HTML list in the "output" div
        document.getElementById("Is_container").innerHTML = output;
    
    } else {
        // Display an alert if no checkboxes or individual services are selected
        window.alert("Select a service");
    }
}
