 jQuery(function($){ // select change show notice.
 			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('.multiple-inline-element').find('.multiple-field-budget-items-amount input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  		// $(this).parents('.fieldset-wrapper').prepend('<div id="op-notice" class="messages warning" style="display: block; ">* Please click \'Filter\' to see your changes, and if the filter button is not here: Please click \'Refine\' to see your changes.</div>');
			  		
			  	}
			});

	Drupal.behaviors.pr = {
		attach: function(context, settings) {
			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('.multiple-inline-element').find('.multiple-field-budget-items-amount input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  	}
			});

			$(".field-name-field-chosen-price input").attr("disabled","disabled");
			countTotalBI();
			function countTotalBInoblur() {
				$('.multiple-field-budget-items-amount input').each(function(){
					total = 0;
					$('.multiple-field-budget-items-amount input').each(function(){
						total += parseFloat($(this).val());
					});
					total += parseFloat($('#edit-field-payment-from-students input').val());
					$('.field-name-field-chosen-price input').val(total);
				});
			}

			$('#edit-field-payment-from-students input').blur(function(){
				countTotalBInoblur();
			});
			$('input[value=Save]').click(function(e){
				// e.preventDefault();
				countTotalBInoblur();
			});
			
		}
	}
	
	$(".field-name-field-chosen-price input").attr("disabled","disabled");
	function countTotalBI() {
		$('.multiple-field-budget-items-amount input').blur(function(){
			total = 0;
			$('.multiple-field-budget-items-amount input').each(function(){
				total += parseFloat($(this).val());
			});
			total += parseFloat($('#edit-field-payment-from-students input').val());
			$('.field-name-field-chosen-price input').val(total);
		});
	}
	countTotalBI();
	function countTotalBInoblur() {
		$('.multiple-field-budget-items-amount input').each(function(){
			total = 0;
			$('.multiple-field-budget-items-amount input').each(function(){
				total += parseFloat($(this).val());
			});
			total += parseFloat($('#edit-field-payment-from-students input').val());
			$('.field-name-field-chosen-price input').val(total);
		});
	}

	$('#edit-field-payment-from-students input').blur(function(){
		countTotalBInoblur();
	});
	$('input[value=Save]').click(function(e){
		// e.preventDefault();
		countTotalBInoblur();
	});
});