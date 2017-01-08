$(document).ready(function()
{
	$("#avatar").bind("webkitAnimationEnd mozAnimationEnd animationEnd", function(){
		$(this).removeClass("swing");
	});

	$('#avatar').hover(function()
	{
  		$(this).addClass("swing");
	});

	$('#avatar').click(function()
	{
		$("#bubble").animate({marginTop:-10,opacity:0},500);
        $(this).addClass('circle-label-rotate');
        $(this).animate({"bottom":"50px"},200).animate({"bottom":"0px"}, 150, function()
		{
			$('#avatar').animate({"opacity":"0","margin-left":"900px"}, 1000, 'linear');
			$('#pageContent').animate({"opacity":"0","margin-top":"1000px"}, 1500, function(){			
				$("#bubble").remove();
				$("#avatar").remove();
				document.location="./a-propos-de-moi";
			});
		});
    });

    $(".theme i").bind("webkitAnimationEnd mozAnimationEnd animationEnd", function(){
		$(this).removeClass("swing");
	});

	$('.theme i').hover(function()
	{
  		$(this).addClass("swing");
	});
});