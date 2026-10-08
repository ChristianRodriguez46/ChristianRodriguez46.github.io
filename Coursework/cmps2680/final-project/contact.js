$(document).ready(function() {
    $('#submitForms').on('click', function() {
        // Get values from personalInfoForm
        const fName = $('#fname').val();
        const email = $('#email').val();
        const message = $('#message').val();

        //validate inputs
        if (fName === '' || email === '' || message === ''){
            alert('please fill in all fields.');
            return;
        }else{

            // Display values in the output div
            $('#c_output').html(`
          <p>Thank you for your message ${fName}!</p>
          <p>Our team will get back to you shortly at ${email}</p>
        `);
        };
    });
});
