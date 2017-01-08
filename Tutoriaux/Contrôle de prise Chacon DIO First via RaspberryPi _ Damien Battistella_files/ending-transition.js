$(document).ready(function()
{
	$("a").click(function(e)
	{
        if($(this).attr("href")) {
            e.preventDefault();
            linkLocation = this.href;        

        	$('#pageContent').animate({"opacity":"0","margin-top":"1000px"}, 1500, function()
    		{
        		window.location = linkLocation;
    		});
        	
        	$('.box').animate({"opacity":"0","margin-top":"1000px"}, 1500, function()
    		{
        		window.location = linkLocation;
    		});
        }
    });
});