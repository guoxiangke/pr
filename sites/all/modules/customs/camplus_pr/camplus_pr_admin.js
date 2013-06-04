jQuery(function($){ 
	console.log('added!');
	$('#edit-camplus-pr-enable-mixable-key').click(function(){

		if(!$('#edit-camplus-pr-enable-mixable-key').is(":checked")) {
			$('#edit-camplus-pr-email-notification-enable').attr('disabled','disabled');
			$('.form-item-camplus-pr-email-notification-addr input').attr("disabled","disabled");
			$('.form-item-camplus-pr-email-notification-addr input').css("background-color","#999");
			$('#edit-camplus-pr-lock-function-enable').attr("disabled","disabled");

		}else{ 
			console.log('123');
			$('#edit-camplus-pr-email-notification-enable').removeAttr('disabled');
			$('#edit-camplus-pr-lock-function-enable').removeAttr('disabled');
			if($('#edit-camplus-pr-email-notification-enable').is(":checked")) {
				$('.form-item-camplus-pr-email-notification-addr input').removeAttr('disabled');
				$('.form-item-camplus-pr-email-notification-addr input').css("background-color","");
			}
		}

	});

	$('#edit-camplus-pr-email-notification-enable').click(function(){

		if(!$('#edit-camplus-pr-email-notification-enable').is(":checked")) {
			$('.form-item-camplus-pr-email-notification-addr input').attr("disabled","disabled");
			$('.form-item-camplus-pr-email-notification-addr input').css("background-color","#999");

		}else{ 
			console.log('456');
			$('.form-item-camplus-pr-email-notification-addr input').removeAttr('disabled');
			$('.form-item-camplus-pr-email-notification-addr input').css("background-color","");
		}

	});

	if(!$('#edit-camplus-pr-enable-mixable-key').is(":checked")) {
		$('#edit-camplus-pr-email-notification-enable').attr('disabled','disabled');
		$('.form-item-camplus-pr-email-notification-addr input').attr("disabled","disabled");
		$('.form-item-camplus-pr-email-notification-addr input').css("background-color","#999");
		$('#edit-camplus-pr-lock-function-enable').attr("disabled","disabled");
	}

	if(!$('#edit-camplus-pr-email-notification-enable').is(":checked")) {
			$('.form-item-camplus-pr-email-notification-addr input').attr("disabled","disabled");
			$('.form-item-camplus-pr-email-notification-addr input').css("background-color","#999");

		}

});
