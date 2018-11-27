(function($, w, d) {
	$(d).ready(function() {
		var taxon_tree = Drupal.settings.CreaTaxonsGroupes.taxon_tree;
		var groups_name = Drupal.settings.CreaTaxonsGroupes.groups_name;
        var espece = Drupal.settings.CreaTaxonsGroupes.espece;
		
		if ($('#edit-protocole').length){
			$('#edit-protocole input').change(function(){
				var current_protocole = $(this).val();
				var currentTree = taxon_tree[current_protocole];
				
				$('#edit-taxon optgroup').hide();
				
				$.each(currentTree, function(index, value){
					var group_name = groups_name[index];
					$('#edit-taxon optgroup[label="' + group_name + '"]').show();
				});
			});
			// quand on est en mode edition
			if(espece != null){
                protocole = '';
                for(var groupe in taxon_tree.faune){
                	for(var i in taxon_tree.faune[groupe]) {
                        if (i == espece) {
                            protocole = 'faune';
                            break;
                        }
                    }
				}
                for(var groupe in taxon_tree.flore){
                    for(var i in taxon_tree.flore[groupe]) {
                        if (i == espece) {
                            protocole = 'flore';
                            break;
                        }
                    }
                }
                if(protocole != ''){
                	$('#edit-protocole-'+protocole).attr('checked', 'checked');
                }
			}
		}
	});
	
})(jQuery, window, document);