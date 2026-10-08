//An array of images for image board
let images = ['./images/mPic1.png',
    './images/mPic2.png',
    './images/mPic3.png'];

var i = 0;

//defining the function
function change(){
    //gets the image from the img board
    //then changes image according to index
    document.getElementById("main_img").src = images[i];

    // if the image is mPic4 then restart array
    if(i == 2){
        i = 0;
    }else{ 
        i++; 
    }

    setTimeout(change, 6000);
}
//calls the function
change();

