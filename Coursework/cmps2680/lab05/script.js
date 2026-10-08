function showImage(image){
    let path = "./images/" + image + ".png";
    let target = document.getElementById("fullview");
    
    target.src = path;
}
