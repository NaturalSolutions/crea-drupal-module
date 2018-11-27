// Register a template definition set named "default".
CKEDITOR.addTemplates( 'default',
{
	imagesPath : CKEDITOR.getUrl( Drupal.settings.crea_backoffice.ckeditor_templates_images),
    // Template definitions.
    templates :
    [
      {
        title: Drupal.settings.crea_backoffice.trombinoscope.title,
        description: Drupal.settings.crea_backoffice.trombinoscope.description,
        image: Drupal.settings.crea_backoffice.trombinoscope.image,
        html: Drupal.settings.crea_backoffice.trombinoscope.template
      },
        {
            title: Drupal.settings.crea_backoffice.partners.title,
            description: Drupal.settings.crea_backoffice.partners.description,
            image: Drupal.settings.crea_backoffice.partners.image,
            html: Drupal.settings.crea_backoffice.partners.template
        },
			{
			    title: Drupal.settings.crea_backoffice.one_column.title,
			    description: Drupal.settings.crea_backoffice.one_column.description,
			    image: Drupal.settings.crea_backoffice.one_column.image,
			    html: Drupal.settings.crea_backoffice.one_column.template
			},
      {
          title: Drupal.settings.crea_backoffice.two_columns.title,
          description: Drupal.settings.crea_backoffice.two_columns.description,
          image: Drupal.settings.crea_backoffice.two_columns.image,
          html: Drupal.settings.crea_backoffice.two_columns.template
      },
      {
          title: Drupal.settings.crea_backoffice.two_columns_66_33.title,
          description: Drupal.settings.crea_backoffice.two_columns_66_33.description,
          image: Drupal.settings.crea_backoffice.two_columns_66_33.image,
          html: Drupal.settings.crea_backoffice.two_columns_66_33.template
      },
      {
          title: Drupal.settings.crea_backoffice.two_columns_33_66.title,
          description: Drupal.settings.crea_backoffice.two_columns_33_66.description,
          image: Drupal.settings.crea_backoffice.two_columns_33_66.image,
          html: Drupal.settings.crea_backoffice.two_columns_33_66.template
      },
      {
        title: Drupal.settings.crea_backoffice.three_columns.title,
          description: Drupal.settings.crea_backoffice.three_columns.description,
          image: Drupal.settings.crea_backoffice.three_columns.image,
          html: Drupal.settings.crea_backoffice.three_columns.template
      },
      {
          title: Drupal.settings.crea_backoffice.four_columns.title,
          description: Drupal.settings.crea_backoffice.four_columns.description,
          image: Drupal.settings.crea_backoffice.four_columns.image,
          html: Drupal.settings.crea_backoffice.four_columns.template
      }
    ]
});