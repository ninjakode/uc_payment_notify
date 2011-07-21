<?php

/**
 * @file
 * Defines settings pages and forms for the UC Payment Notify module.
 */

/**
 * UC Payment Notify settings form.
 */
function uc_payment_notify_settings_form(&$form_state) {
  
  $form['automated'] = array(
    '#type' => 'fieldset',
    '#title' => t('Automated sending'),
  );
  
  $form['automated']['uc_payment_notify_automated'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send payment notifications automatically'),
    '#default_value' => variable_get('uc_payment_notify_automated', 0),
  );
  
  $form['automated']['uc_payment_notify_automated_days'] = array(
    '#type' => 'textfield',
    '#title' => t('Send after # days of no payment received'),
    '#description' => t('Emails are sent when cron runs.'),
    '#size' => 5,
    '#default_value' => variable_get('uc_payment_notify_automated_days', 5),
  );
  
  $form['automated']['uc_payment_notify_automated_num'] = array(
    '#type' => 'textfield',
    '#title' => t('# of notifications to send'),
    '#size' => 5,
    '#default_value' => variable_get('uc_payment_notify_automated_num', 1),
  );
  
  $payment_methods = array();
  foreach (_payment_method_list() as $method) {
    $payment_methods[$method['id']] = $method['name'];
  }
  
  $form['automated']['uc_payment_notify_methods'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable automatic sending for payment methods'),
    '#description' => t('If no methods are selected, sending will be enabled for all methods.'),
    '#options' => $payment_methods,
    '#default_value' => variable_get('uc_payment_notify_methods', array()),
  );
  
  $form['message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Message'),
  );
  
  $form['message']['uc_payment_notify_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Default subject'),
    '#default_value' => variable_get('uc_payment_notify_subject', ''),
    '#required' => TRUE,
  );
  
  $form['message']['uc_payment_notify_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Default message'),
    '#default_value' => variable_get('uc_payment_notify_message', ''),
    '#required' => TRUE,
  );
  
  $form['message']['tokens'] = array(
    '#value' => theme('token_tree', array('global', 'order')),
  );
  
  return system_settings_form($form);
}
