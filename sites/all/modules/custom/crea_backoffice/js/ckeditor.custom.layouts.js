require:'basewidget';

var definition = {
    template: _template,
    extend: {
        init: function () {

        }
    },
    configuration: {
        init: {
            blockEvents: false,
            configToolbar: {
                defaultButtons: {
                    edit: {
                        onClick: function () {
                            this.editor.layoutmanager.selectedWidget = this;

                            this.editor.execCommand('managelayout', this);
                        }
                    }
                }
            },
            onDestroy: function () {

            }
        }
    },
    editables: _editables,
    upcast: _upcast,
    allowedContent: _allowedContent
};

CKEDITOR.basewidget.addWidget(editor, 'layout manager', definition);