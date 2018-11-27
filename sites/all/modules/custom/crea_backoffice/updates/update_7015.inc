<?php 
// activation du module User registration password
module_enable(array('user_registrationpassword'));

variable_set('user_register', true);
variable_set('user_email_verification', 'with-pass');
