<?php

/**
 * @file
 * Defines settings pages and forms for the UC Payment Notify module.
 */

/**
 * UC Payment Notify settings form.
 */
function uc_payment_notify_settings_form(&$form_state) {
  $form['uc_payment_notify_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Default subject'),
    '#default_value' => variable_get('uc_payment_notify_subject', ''),
    '#required' => TRUE,
  );
  
  $form['uc_payment_notify_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Default message'),
    '#default_value' => variable_get('uc_payment_notify_message', ''),
    '#required' => TRUE,
  );
  
  $form['tokens'] = array(
    '#value' => theme('token_tree', array('global', 'order')),
  );
  
  $payment_methods = array();
  foreach (_payment_method_list() as $method) {
    $payment_methods[$method['id']] = $method['name'];
  }
  
  $form['uc_payment_notify_methods'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable for payment types'),
    '#description' => t('If no methods are selected, it will be enabled for all types.'),
    '#options' => $payment_methods,
    '#default_value' => variable_get('uc_payment_notify_methods', array()),
  );
  
  $form = system_settings_form($form);
  $form['#submit'][] = 'uc_payment_notify_settings_submit';
  
  return $form;
}

function uc_payment_notify_settings_submit($form, &$form_state) {
  
  // Save uc_payment_notify_methods in a 1-d array instead
  $methods = array();
  foreach ($form_state['values']['uc_payment_notify_methods'] as $method => $value) {
    if ($value) {
      $methods[] = $method;
    }
  }
  
  variable_set('uc_payment_notify_methods', $methods);
}
