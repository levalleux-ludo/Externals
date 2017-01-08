$(document).ready(function()
{
	var t;
	var isanimated = false;
	var isvisible = false;
	var popup = $("#bubble",this);
	
	$("section").slideDown();
	
	$("#avatar").mouseover(function()
	{
		if (t) clearTimeout(t);
		if (!isvisible && !isanimated)
		{
			isanimated = true;
			popup.css({opacity:0,display:"block",marginTop:15}).animate({marginTop:0,opacity:1},500, function(){isanimated=false;isvisible=true;});
		}
		else
		{
			return;
		}
	}).mouseout(function()
	{
		if (t) clearTimeout(t);
		if (!isanimated && isvisible)
		{
			t = setTimeout(function(){isanimated=true;popup.animate({marginTop:-10,opacity:0},500, function(){popup.css({display:"none"});isvisible=false;isanimated=false;});}, 500);
		}
		else
		{
			return;
		}
	});
});