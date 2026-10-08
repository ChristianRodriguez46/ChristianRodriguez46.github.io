<?php
require_once "sql/sqlTools.php";
require_once('./validate.php');

date_default_timezone_set("America/Los_Angeles");
ini_set('error_log', 'error.log');
ini_set('display_errors', 1);

$postTarget = htmlspecialchars($_SERVER['PHP_SELF']);

$order = [];
$errors = [];

if ($_SERVER["REQUEST_METHOD"] == "POST"){
    
    foreach ($errors as $key => $value) {
        $errors[$key] = []; 
    }
    // $errors = [];
    //clean all fields from any bad data
    $order = $_POST;
    if(!validateOrder($order)){
        $errors['order'] = "<h5 id='S-error'>You must select at least one service!</h5>";
    }

    foreach($_POST as $key => $value){
        if($value){
            if(is_array($value)){
                foreach($value as $aKey => $aValue){
                    $value[$aKey] = cleanData($aValue);
                }
            }else{
                $order[$key] = cleanData($value);
            }
        }
    }

    if(!validFname($order['fname'])){
        $errors['fname'] = "<p>Invalid first name</p>";
    }
    if(!validLname($order['lname'])){
        $errors['lname'] = "<p>Invalid last name</p>";
    }
    if(!validEmail($order['email'])){
        $errors['email'] = "<p>Invalid email</p>";
    }
    if(!validAddress($order['address'])){
        $errors['address'] = "<p>Invalid address</p>";
    }
    if(!validCity($order['city'])){
        $errors['city'] = "<p>Invalid address</p>";
    }
    if(!validZip($order['zip'])){
        $errors['Zip'] = "<p>Invalid zip code</p>";
    }
    if(!validPnum($order['phone'])){
        $errors['phone'] = "<p>Invalid phone number</p>";
    }
    if(!validMake($order['make'])){
        $errors['make'] = "<p>Select a make</p>";
    }
    if(!validModel($order['model'])){
        $errors['model'] = "<p>Select a model</p>";
    }
    if(!validYear($order['year'])){
        $errors['year'] = "<p>Invalid year</p>";
    }
    if(!validDate($order['date'])){
        $errors['date'] = "<p>Select a date</p>";
    }
    if(!validTime($order['time'])){
        $errors['time'] = "<p>select a time</p>";
    }

    if(empty($errors)){
      $orderNumber = addOrder($order);
    }
}

?>

<!DOCTYPE html>
<html>
    <head>
        <title>Booking</title>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>

        <script src="./scripts/booking.js"></script>
        <!-- Jquery Cdn -->
        <script src="https://code.jquery.com/jquery-3.7.1.js" integrity="sha256-eKhayi8LEQwp4NKxN+CfCh+3qOVUtJn3QNZ0TciWLP4=" crossorigin="anonymous"></script>
        <!-- Jquery UI Cdn -->
        <script src="https://code.jquery.com/ui/1.13.3/jquery-ui.js"></script>

        <link rel="stylesheet" type="text/css" href="./styles/booking.css">
        <style>
          @media screen and (max-width:425px) {
            #form {
                    margin:0px;
                 }
            #output{
                margin-bottom: 21px;
            }
          }
        </style>
    </head>
    <body data-new-gr-c-s-check-loaded="14.1143.0" data-gr-ext-installed="">
        <nav class="navbar naxvbar-expand-sm bg-dark navbar-dark">
            <div class="container-fluid" id="navContainer">
                <a class="navbar-brand" href="./home.html">Wise Choice Detailing</a>
                <button class="navbar-toggler collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#xx" style="cursor:pointer" fdprocessedid="kwg44" aria-expanded="false">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="navbar-collapse collapse" id="xx" style="">
                    <ul class="navbar-nav" id="navList">

                        <li class="nav-item">
                            <a class="nav-link" href="./home.html">Home</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./service.html">Services</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./booking.php">Book your detailing</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./gallery.html">Gallery</a>
                        </li>

                        <li class="nav-item">
                            <a class="nav-link" href="./contact.html">Contact Us</a>
                        </li>
                    </ul>

                    <form role="search">
                        <input class="form-control" type="search" placeholder="Search" aria-label="Search">
                    </form>
                </div>
            </div>
        </nav>

        <!--Form Container-->
        <div id="container">
            <div id="form">       
                <form id="b-form" class="needs-validation" novalidate="" method="post" action="<?= $postTarget ?>">
                    <!--Personal Infomation div-->
                    <div id="Per-info">
                        <div class="row g-3">
                        <h4>Personal information </h4>
                            <div class="col-sm-6">
                                <label for="fname" class="form-label">First Name</label>
                                <input type="text" class="form-control" id="fname" name="fname" placeholder="First name" required="" fdprocessedid="1whtgc">
                                    <?= $errors['fname'] ?? "" ?>
                                    <!-- First Name is required. -->    
                            </div>
                            <div class="col-sm-6">

                                <label for="lname" class="form-label">Last Name</label>
                                <input type="text" class="form-control" id="lname" name="lname" placeholder="Last name" required="" fdprocessedid="glu9y">

                                <?= $errors['lname'] ?? "" ?>
                                <!-- Last Name is required. -->
                            </div>

                            <div class="col-12">
                                <label for="email" class="form-label">Email </label>
                                <input type="email" class="form-control" id="email" name="email" placeholder="you@example.com" required="" fdprocessedid="3lvcbn">

                                <?= $errors['email'] ?? "" ?>
                                <!-- Please enter a valid email address for service. -->
                            </div>

                            <div class="col-12">
                                <label for="address" class="form-label">Address</label>
                                <input type="text" class="form-control" id="address" name="address" placeholder="1234 Main St" required="" fdprocessedid="l4xhga">

                                <?= $errors['address'] ?? "" ?>
                                <!-- Please enter your address. -->
                            </div>
                            <div class="col-md-6">
                                <label for="city" class="form-label">City</label>
                                <input type="text" class="form-control" id="city" name="city" placeholder="Enter city name" required="" fdprocessedid="jpj65c">
                                
                                <?= $errors['city'] ?? "" ?>
                                <!-- City is required. -->

                            </div>

                            <div class="col-md-6">
                                <label for="zip" class="form-label">Zip</label>
                                
                                <input type="text" class="form-control" id="zip" name="zip" placeholder="" required="" fdprocessedid="evs2jd">
                                
                                <?= $errors['zip'] ?? "" ?>
                                <!-- Zip code required. -->
                            </div>
                            <div class="col-md-6">
                                <label for="phone" class="form-label">Enter your phone number: </label>
                                <input type="tel" class="form-control" id="phone" name="phone" pattern="[0-9]{3}-[0-9]{3}-[0-9]{4}" placeholder="123-456-7890" size="11" required="" fdprocessedid="wpspp">
                                    <?= $errors['phone'] ?? "" ?>               
                                    <!-- Invalid phone number. -->
                            </div>

                            <h4>Car information</h4>
                            <div class="col-sm-5">
                                <label for="make" class="form-label">Make:</label>
                                    <select class="form-select" id="make" name="make" required="" fdprocessedid="0mpbw">
                                        <option value="" disabled="" selected="">Select Make</option>
                                        <option value="Toyota">Toyota</option>
                                        <option value="Honda">Honda</option>
                                        <option value="Ford">Ford</option>
                                        <option value="Chevrolet">Chevrolet</option>
                                        <option value="Nissan">Nissan</option>
                                        <option value="BMW">BMW</option>
                                        <option value="Mercedes-Benz">Mercedes-Benz</option>
                                        <option value="Audi">Audi</option>
                                        <option value="Volkswagen">Volkswagen</option>
                                        <option value="Hyundai">Hyundai</option>
                                        <!-- Add more options for other car brands -->
                                    </select>
                                    <div class="invalid-feedback">
                                        <?= $errors['make'] ?? "" ?>
                                    </div>
                            </div>
                            <div class="col-md-4">
                                <label for="model" class="form-label">Model:</label>
                                    <select class="form-select" id="model" name="model" required="" fdprocessedid="ofex1p">
                                        <option value="" disabled="" selected="">Select Model</option>
                                        <!-- Options for Toyota -->
                                        <optgroup label="Toyota">
                                            <option value="Camry">Camry</option>
                                            <option value="Corolla">Corolla</option>
                                            <option value="Rav4">Rav4</option>
                                            <option value="Highlander">Highlander</option>
                                            <option value="Tacoma">Tacoma</option>
                                            <option value="Sienna">Sienna</option>
                                            <option value="Prius">Prius</option>
                                            <!-- Add more Toyota models as needed -->
                                        </optgroup>
                                        <!-- Options for Honda -->
                                        <optgroup label="Honda">
                                            <option value="Civic">Civic</option>
                                            <option value="Accord">Accord</option>
                                            <option value="CR-V">CR-V</option>
                                            <option value="Pilot">Pilot</option>
                                            <option value="Odyssey">Odyssey</option>
                                            <option value="Fit">Fit</option>
                                            <option value="HR-V">HR-V</option>
                                            <!-- Add more Honda models as needed -->
                                        </optgroup>
                                        <!-- Options for Ford -->
                                        <optgroup label="Ford">
                                            <option value="F-150">F-150</option>
                                            <option value="Mustang">Mustang</option>
                                            <option value="Explorer">Explorer</option>
                                            <option value="Escape">Escape</option>
                                            <option value="Focus">Focus</option>
                                            <option value="Edge">Edge</option>
                                            <option value="Fusion">Fusion</option>
                                            <!-- Add more Ford models as needed -->
                                        </optgroup>
                                        <!-- Options for Chevrolet -->
                                        <optgroup label="Chevrolet">
                                            <option value="Silverado">Silverado</option>
                                            <option value="Equinox">Equinox</option>
                                            <option value="Malibu">Malibu</option>
                                            <option value="Camaro">Camaro</option>
                                            <option value="Tahoe">Tahoe</option>
                                            <option value="Traverse">Traverse</option>
                                            <option value="Suburban">Suburban</option>
                                            <!-- Add more Chevrolet models as needed -->
                                        </optgroup>
                                        <!-- Options for Nissan -->
                                        <optgroup label="Nissan">
                                            <option value="Altima">Altima</option>
                                            <option value="Sentra">Sentra</option>
                                            <option value="Rogue">Rogue</option>
                                            <option value="Pathfinder">Pathfinder</option>
                                            <option value="Titan">Titan</option>
                                            <option value="Versa">Versa</option>
                                            <option value="Maxima">Maxima</option>
                                            <!-- Add more Nissan models as needed -->
                                        </optgroup>
                                        <!-- Options for BMW -->
                                        <optgroup label="BMW">
                                            <option value="3 Series">3 Series</option>
                                            <option value="5 Series">5 Series</option>
                                            <option value="X3">X3</option>
                                            <option value="X5">X5</option>
                                            <option value="7 Series">7 Series</option>
                                            <option value="i3">i3</option>
                                            <option value="X1">X1</option>
                                            <!-- Add more BMW models as needed -->
                                        </optgroup>
                                        <!-- Options for Mercedes-Benz -->
                                        <optgroup label="Mercedes-Benz">
                                            <option value="C-Class">C-Class</option>
                                            <option value="E-Class">E-Class</option>
                                            <option value="S-Class">S-Class</option>
                                            <option value="GLC">GLC</option>
                                            <option value="GLE">GLE</option>
                                            <option value="GLA">GLA</option>
                                            <option value="CLA">CLA</option>
                                            <!-- Add more Mercedes-Benz models as needed -->
                                        </optgroup>
                                        <!-- Options for Audi -->
                                        <optgroup label="Audi">
                                            <option value="A4">A4</option>
                                            <option value="A6">A6</option>
                                            <option value="Q5">Q5</option>
                                            <option value="Q7">Q7</option>
                                            <option value="A3">A3</option>
                                            <option value="Q3">Q3</option>
                                            <option value="A5">A5</option>
                                            <!-- Add more Audi models as needed -->
                                        </optgroup>
                                        <!-- Options for Volkswagen -->
                                        <optgroup label="Volkswagen">
                                            <option value="Jetta">Jetta</option>
                                            <option value="Passat">Passat</option>
                                            <option value="Tiguan">Tiguan</option>
                                            <option value="Atlas">Atlas</option>
                                            <option value="Golf">Golf</option>
                                            <option value="Arteon">Arteon</option>
                                            <option value="ID.4">ID.4</option>
                                            <!-- Add more Volkswagen models as needed -->
                                        </optgroup>
                                        <!-- Options for Hyundai -->
                                        <optgroup label="Hyundai">
                                            <option value="Elantra">Elantra</option>
                                            <option value="Sonata">Sonata</option>
                                            <option value="Tucson">Tucson</option>
                                            <option value="Santa Fe">Santa Fe</option>
                                            <option value="Kona">Kona</option>
                                            <option value="Palisade">Palisade</option>
                                            <option value="Veloster">Veloster</option>
                                            <!-- Add more Hyundai models as needed -->
                                        </optgroup>
                                        <!-- Add more optgroups for other car brands -->
                                    </select>
                                        <?= $errors['model'] ?? "" ?>
                            </div>

                            <div class="col-md-3">
                                <label for="year" class="form-label">Year</label>
                                <input type="number" class="form-control" id="year" name="year" required="" fdprocessedid="sxxs7e">
                               
                                <?= $errors['year'] ?? "" ?>
                                <!-- Year is required. -->
                            </div>

                            <h4>Select a date and time</h4>
                            
                            <div class="col-md-6">
                                <label for="date" class="form-label">Date</label>
                                <input type="date" class="form-control" id="date" name="date" required="">                                
                                
                                <?= $errors['date'] ?? "" ?>
                                <!-- select a date. -->
                            </div>

                            <div class="col-md-6">
                                <label for="time" class="form-label">Time</label>
                                <input type="time" id="time" class="form-control" name="time" required="">
                                
                                <?= $errors['time'] ?? "" ?>
                                <!-- Please select a date and time. -->
                            </div>
                            
                            <?= $errors['model'] ?? "" ?>

                        </div>
                    </div>
                    <div id="service-container">
                        <hr class="my-4">
                        
                        <?=$errors['order'] ?? "" ?>

                        <!--package div-->
                        <div class="p-form">
                            <legend>Packages:</legend>

                            <input type="radio" id="bronze" class="form-check-input" name="package" value="Bronze">
                            <label class="form-check-label" for="bronze">BRONZE</label><br>

                            <input type="radio" id="silver" class="form-check-input" name="package" value="Silver">
                            <label class="form-check-label" for="silver">SILVER</label><br>

                            <input type="radio" id="Gold" class="form-check-input" name="package" value="Gold">
                            <label class="form-check-label" for="Gold">GOLD</label><br>
                        </div>

                        <hr class="my-4">

                        <!--Service div-->
                        <div id="s-form">
                            <!--Exterior services-->
                            <div id="ex-form">
                                <legend>Exterior Individual Services:</legend>

                                <input type="checkbox" id="s1" class="form-check-input" name="E_services[]" value="Full Service Hand Wash">
                                <label class="form-check-label" for="s1">FULL SERVICE HAND WASH</label>
                                <br>
                                <input type="checkbox" id="s2" class="form-check-input" name="E_services[]" value="WHEEL CLEAN & SHINE">
                                <label class="form-check-label" for="s2">WHEEL CLEAN &amp; SHINE</label>
                                <br>
                                <input type="checkbox" id="s3" class="form-check-input" name="E_services[]" value="PLASTIC RESTORE">
                                <label class="form-check-label" for="s3">PLASTIC RESTORE</label>
                                <br>

                                <input type="checkbox" id="s4" class="form-check-input" name="E_services[]" value="ENGINE BAY">
                                <label class="form-check-label" for="s4">ENGINE BAY</label>
                                <br>

                                <input type="checkbox" id="s5" class="form-check-input" name="E_services[]" value="HAND WAX">
                                <label class="form-check-label" for="s5">HAND WAX</label>
                                <br>

                            </div>

                            <hr class="my-4">

                            <!--Interior Services-->
                            <div id="in-form">
                                <legend>Interior Individual Services:</legend>

                                <input type="checkbox" id="s6" class="form-check-input" name="I_services[]" value="VACCUM & CLEAN">
                                <label class="form-check-label" for="s6">VACCUM &amp; CLEAN</label>
                                <br>

                                <input type="checkbox" id="s7" class="form-check-input" name="I_services[]" value="LEATHER CLEAN & CONDITION">
                                <label class="form-check-label" for="s7">LEATHER CLEAN &amp; CONDITION</label>
                                <br>

                                <input type="checkbox" id="s8" class="form-check-input" name="I_services[]" value="DOOR, DASH, & PLASTIC CONDITION">
                                <label class="form-check-label" for="s8">DOOR, DASH, &amp; PLASTIC CONDITION</label>
                                <br>

                                <input type="checkbox" id="s9" class="form-check-input" name="I_services[]" value="CARPET & UPHOLSTERY SHAMPOO">
                                <label class="form-check-label" for="s9">CARPET &amp; UPHOLSTERY SHAMPOO</label>
                            </div>
                        </div>
                        <hr class="my-4">
                        
                    </div>
                    <div class="button_container">
                        <button id="button" type="submit" fdprocessedid="6lypor">Book</button>
                    </div>

                </form>
                     
                <div id="output_container" class = "row">
                    <!-- <div id="output"></div>            
                    <div id="Is_container"></div>-->
                    <?php
                        if ($_SERVER["REQUEST_METHOD"] == "POST"){
                            if(isset($orderNumber) && $orderNumber != NULL){
                                echo getUniqueOrder($orderNumber);
                                //echo printUniqueOrder($orderNumber);
                            }
                        } 
                    ?>
                </div>
            </div>
        </div>

        <footer class="py-3 my-4">
            <ul class="nav justify-content-center border-bottom pb-3 mb-3">
                <li class="nav-item"><a href="./home.html" class="nav-link px-2 text-body-secondary">Home</a></li>
                <li class="nav-item"><a href="./service.html" class="nav-link px-2 text-body-secondary">Services</a></li>
                <li class="nav-item"><a href="./booking.php" class="nav-link px-2 text-body-secondary">Booking</a></li>
                <li class="nav-item"><a href="./gallery.html" class="nav-link px-2 text-body-secondary">Gallery</a></li>
                <li class="nav-item"><a href="./contact.html" class="nav-link px-2 text-body-secondary">Contact Us</a></li>
            </ul>
            <p class="text-center text-body-secondary"> © 2023 Wise Choice Detailing. All rights reserved.</p>
        </footer>
        <script>
            $(document).ready(function() {
                var width = $('#output_container').width();

                if (width <= 200) {
                    $('#output_container').css('display', 'initial'); // or 'initial'
                    $('#output').css('padding-bottom', '25px');
                }
            });
        </script>
        <script>
            //bootstrap validation for personal information

            // Example starter JavaScript for disabling form submissions if there are invalid fields
            (() => {
                'use strict'

                // Fetch all the forms we want to apply custom Bootstrap validation styles to
                const forms = document.querySelectorAll('.needs-validation')

                // Loop over them and prevent submission
                Array.from(forms).forEach(form => {
                    form.addEventListener('submit', event => {
                        if (!form.checkValidity()) {
                            event.preventDefault()
                            event.stopPropagation()
                        }

                        form.classList.add('was-validated')
                    }, false)
                })
            })()
        </script>
    </body>
</html>
