$('.container').each(function() {
    const $container = $(this);
    $container.find('.slider').on('input', function(e) {
      $container.css('--position', `${e.target.value}%`);
    });
  });