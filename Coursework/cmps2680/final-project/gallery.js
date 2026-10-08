
//Function to enlarge thumbnail

function showEnlargedThumbnail(src){
    // selects name of the attribute to be modified ('src')

    // then assign new value for the attribute (passed)
    $('#enlarged-image').attr('src', src);
    $('#enlarged-thumbnail').fadeIn();

    $('#enlarged-thumbnail').css('display', 'flex'); //makes div's css display to flex instead of block

    $('.btn-view').addClass('disabled');
}

//Function hides enlarged thumbnail
function hideEnlargedThumbnail(){
    $('#enlarged-thumbnail').fadeOut();
    $('.enlarge-thumbnail').css('display', 'none')
    $('.btn-view').removeClass('disabled')
}

//when view button is click this function is called
$('.btn-view').click(function(){
    if($(this).hasClass('disabled')){
        return;
    }


    var thumbnailSrc = $(this).closest('.card').find('image').attr('href');

    /* $(this).closest('.card') finds the closest ancestor with the class 'card'.

        find('image') then searches for the <image> element within that card.

        .attr('href') extracts the value of the href attribute from the <image> element, representing the thumbnail source. */

    showEnlargedThumbnail(thumbnailSrc);
});

//attach click event to close button in enlarged image
$('#enlarged-thumbnail').click(function(){
    hideEnlargedThumbnail();
});


//prevents large thumbnail from closing if clicked
$('#enlarged-image').click(function(event){
    event.stopPropagation();
});
