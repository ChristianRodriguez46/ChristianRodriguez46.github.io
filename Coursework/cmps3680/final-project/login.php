<?php
    require_once "./sql/sqlTools.php";
    require_once "./validate.php";

    $db = getConnection();
    
    $postTarget = htmlspecialchars($_SERVER['PHP_SELF']);

    $Signup = [];
    $login = [];

    $L_errors = [];
    $S_errors = [];

    
    if ($_SERVER["REQUEST_METHOD"] == "POST"){

        // Login logic
         //if (isset($_POST['login']) && empty($_POST['login']) 
         if (isset($_POST['login'])) 
         {
            
             foreach($L_errors as $key){
                 $L_errors[$key] = [];
             }

             foreach($_POST as $key => $value){
                 $login[$key] = cleanData($value);
             }


             if(!uniqueUsername($_POST['Username'])){
                 $username = $login['Username'];
             }else{
                 $L_errors['username'] = "There is no username does not exist";
             }

             if (PasswordCheck($login['Username'], $login['password'])) {
                 $L_errors['password'] = "There is no user with " . $login['password'];
             }else{
                 $password = $login['password'];
             }

             if (empty($L_errors)) {
                 session_start();
            
                 $stmt = $db->prepare("SELECT username, email, password FROM users WHERE username = ?");
                 $stmt->bind_param("s", $username);
                 $stmt->execute();
                 $result = $stmt->get_result();
                 $user = $result->fetch_assoc();

                 if ($user && password_verify($password, $user['password'])) {
                     $_SESSION['username'] = $user['username'];
                     $_SESSION['email'] = $user['email'];
                     // Redirect to orders page or wherever you want
                     header("Location: orders.php");
                     exit();
                 } 
             }
             else 
             {
                 echo "Invalid username or password";
             }
            
         }


        // Registration logic
         if (isset($_POST['register'])) 
         {
            
             foreach($S_errors as $key){
                 $S_errors[$key] = [];
             }


             $Signup = $_POST;

             foreach($Signup as $key => $value){
                 $Signup[$key] = cleanData($value);
             }
           
             if(!uniqueUsername($Signup['Username'])){
                 $S_errors['username'] = "This username is already taken.";
             }

             if(!validEmail($_POST['email'])){
                 $S_errors['email'] = "Invalid email";
             }

             $password = password_hash($Signup['password'], PASSWORD_DEFAULT);

             if(empty($S_errors)){
                 echo "before the add User";
                 addUser($Signup, $password);
                 //header("Location: login.php");
                 //exit();
             }

         }
     }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="./styles/User.css">
    <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
    <title>Sign Up</title>
</head>
<body>
    <div class="container">
        <div class="form-box">
            <h1 id="title">Sign Up</h1>
            <form method="POST" action="<?= $postTarget ?>" >
                <div class="input-group">
                    <div class="input-field" id="emailField">
                        <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="#000000" viewBox="0 0 256 256">
                            <path d="M224,48H32a8,8,0,0,0-8,8V192a16,16,0,0,0,16,16H216a16,16,0,0,0,16-16V56A8,8,0,0,0,224,48ZM203.43,64,128,133.15,52.57,64ZM216,192H40V74.19l82.59,75.71a8,8,0,0,0,10.82,0L216,74.19V192Z"></path>
                        </svg>                    
                        <input type="email" placeholder="Email" name="email">
                        <?= $S_errors['email'] ?? " "?>
                    </div>
                    <div class="input-field" id="UsernameField">
                        <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="#000000" viewBox="0 0 256 256">
                            <path d="M128,24A104,104,0,1,0,232,128,104.11,104.11,0,0,0,128,24ZM74.08,197.5a64,64,0,0,1,107.84,0,87.83,87.83,0,0,1-107.84,0ZM96,120a32,32,0,1,1,32,32A32,32,0,0,1,96,120Zm97.76,66.41a79.66,79.66,0,0,0-36.06-28.75,48,48,0,1,0-59.4,0,79.66,79.66,0,0,0-36.06,28.75,88,88,0,1,1,131.52,0Z"></path>
                        </svg>                
                        <input type="text" placeholder="Username" name="Username">
                        <?= $S_errors['username'] ?? " " ?>
                        <?= $L_errors['username'] ?? " "?>
                    </div>
                    <div class="input-field">
                        <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="#000000" viewBox="0 0 256 256">
                            <path d="M48,56V200a8,8,0,0,1-16,0V56a8,8,0,0,1,16,0Zm92,54.5L120,117V96a8,8,0,0,0-16,0v21L84,110.5a8,8,0,0,0-5,15.22l20,6.49-12.34,17a8,8,0,1,0,12.94,9.4l12.34-17,12.34,17a8,8,0,1,0,12.94-9.4l-12.34-17,20-6.49A8,8,0,0,0,140,110.5ZM246,115.64A8,8,0,0,0,236,110.5L216,117V96a8,8,0,0,0-16,0v21l-20-6.49a8,8,0,0,0-4.95,15.22l20,6.49-12.34,17a8,8,0,1,0,12.94,9.4l12.34-17,12.34,17a8,8,0,1,0,12.94-9.4l-12.34-17,20-6.49A8,8,0,0,0,246,115.64Z"></path></svg>
                        <input type="password" placeholder="Password" name="password">
                        <?= $L_errors['password'] ?? " "?>
                    </div>
                    <p>Lost password <a href="#">Click Here!</a></p>
                </div>
                <div class="btn-field">
                    <button type="button" name="register" id="signupBtn">Sign Up</button>
                    <button type="button" name="login" id="signinBtn" class="disable">Sign In</button>
                </div>
            </form>
        </div>
    </div>
    <script>
        $(document).ready(function() {
            let signupBtn = $("#signupBtn");
            let signinBtn = $("#signinBtn");
            let emailField = $("#emailField");
            let title = $("#title");

            // Function to handle changes in button type
            function handleButtonType(btn) {
                if (btn.hasClass("disable")) {
                    btn.prop("type", "button");
                } else {
                    btn.prop("type", "submit");
                }
            }

                // Event handler for signinBtn click
            signinBtn.on("click", function(){
                emailField.css("max-height", "0");
                title.text("Sign In");
                handleButtonType(signinBtn); // Adjust button type
                signinBtn.removeClass("disable");
                signupBtn.addClass("disable");
                $("title").text("Sign In");
            });

            // Event handler for signupBtn click
            signupBtn.on("click", function(){
                emailField.css("max-height", "60px");
                title.text("Sign Up");
                handleButtonType(signupBtn); // Adjust button type
                signupBtn.removeClass("disable");
                signinBtn.addClass("disable");
                $("title").text("Sign Up");
            });
        });
    </script>
</body>
</html>
