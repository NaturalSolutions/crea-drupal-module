(function($) {
CKEDITOR.plugins.add( 'map', {
	init: function( editor )
	{
		editor.addCommand( 'map_insert_command', {
			exec : function( editor ) {
				//here is where we tell CKEditor what to do.
				editor.insertHtml( '||{"type":"map","style":""}||' );
			}
		});
  
		editor.ui.addButton( 'map_insert_button', {
			label: 'Insert the sensor map', //this is the tooltip text for the button
			command: 'map_insert_command',
			icon: this.path + 'images/icon.gif'
		});
	}
});
})();