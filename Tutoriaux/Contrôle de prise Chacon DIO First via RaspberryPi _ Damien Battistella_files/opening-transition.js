$(document).ready(function()
{
	$('footer').hide();
	//$('section img').hide();

    $('#pageContent').css({"margin-top":"-2000px", "position":"absolute"}).show();
    
	$('#pageContent').animate({"margin-top":"80px"}, 800, function()
	{
		$(this).animate({"margin-top":"50px"}, 800, function()
		{
			$(this).animate({"margin-top":"60px"}, 800, function()
			{
				$(this).css({"position":"relative"});
				$('footer').slideDown();
			});
		});
	});
	
	$('.box').css({"margin-top":"-1000px"}).show();
	
	$('.box').animate({"margin-top":"20px"}, 800, function()
	{
		$(this).animate({"margin-top":"-10px"}, 800, function()
		{
			$(this).animate({"margin-top":"0"}, 800, function()
			{
				$(this).css({"position":"relative"});
				$('footer').slideDown();
			});
		});
	});

	window.setTimeout( function(){
		$(".social").fadeIn("slow");
	}, 5000);

//	$('section img').load(function(){
//		$(this).slideDown(800);
//	});
});