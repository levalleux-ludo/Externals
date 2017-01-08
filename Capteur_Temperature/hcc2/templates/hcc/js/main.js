$(document).ready(function(){


	$('.temperature').each(function(i,elem){
		setInterval(function(){
			$('span',elem).load('action.php',{'action':'GET_ENGINE_STATE','engine':$(elem).attr('alt')});
		},3000);
	});
	
	$('#myTab a').click(function (e) {
		e.preventDefault();
		$(this).tab('show');
    })
	
});

	