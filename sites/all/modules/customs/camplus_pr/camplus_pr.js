 jQuery(function($){ // select change show notice.
 			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('tr').find('input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  		// $(this).parents('.fieldset-wrapper').prepend('<div id="op-notice" class="messages warning" style="display: block; ">* Please click \'Filter\' to see your changes, and if the filter button is not here: Please click \'Refine\' to see your changes.</div>');
			  		
			  	}
			});
 			$('#edit-field-pr-sole-supplier-und').change(function() {
			     if(this.checked) {
			         // do something when checked
			        $('#fgm_node_purchase_request_form_group_referenced-add-more-wrapper').slideUp();
			     }else {
			     	$('#fgm_node_purchase_request_form_group_referenced-add-more-wrapper').slideDown();
			     }
			 });
	Drupal.behaviors.pr = {
		attach: function(context, settings) {
			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('tr').find('input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  	}
			});

			$(".field-name-field-chosen-price input").attr("disabled","disabled");
			countTotalBI();
			function countTotalBInoblur() {
				$('#fgm-node-purchase-request-form-group-budgets-values input').each(function(){
					total = 0;
					$('#fgm-node-purchase-request-form-group-budgets-values input').each(function(){
						total += parseFloat($(this).val());
					});
					total += parseFloat($('#edit-field-payment-from-students input').val());
					$('.multiple-field-chosen-price input').val(total);
				});
			}

			$('#edit-field-payment-from-students input').blur(function(){
				countTotalBInoblur();
			});
			$('input[value=Save]').click(function(e){
				// e.preventDefault();
				countTotalBInoblur();
			});
			
			$('#edit-fgm-node-purchase-request-form-group-referenced-add-more').click(function(){
				$('#field-multiple-bi-reason-add-more-wrapper').slideDown();
			});
				
		}
	}
	
	$(".field-name-field-chosen-price input").attr("disabled","disabled");
	function countTotalBI() {
		$('#fgm-node-purchase-request-form-group-budgets-values input').blur(function(){
			total = 0;
			$('#fgm-node-purchase-request-form-group-budgets-values input').each(function(){
				total += parseFloat($(this).val());
			});
			total += parseFloat($('#edit-field-payment-from-students input').val());
			$('.multiple-field-chosen-price input').val(total);
		});
	}
	countTotalBI();
	function countTotalBInoblur() {
		$('#fgm-node-purchase-request-form-group-budgets-values input').each(function(){
			total = 0;
			$('#fgm-node-purchase-request-form-group-budgets-values input').each(function(){
				total += parseFloat($(this).val()) || 0;
			});
			total += parseFloat($('#edit-field-payment-from-students input').val());
			$('.multiple-field-chosen-price input').val(total);
		});
	}

	$('#edit-field-payment-from-students input').blur(function(){
		countTotalBInoblur();
	});
	$('input[value=Save]').click(function(e){
		// e.preventDefault();
		countTotalBInoblur();
	});

	$('#field-multiple-bi-reason-add-more-wrapper').hide();

});