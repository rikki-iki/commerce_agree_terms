<?php

/**
 * @file
 * Defines settings form and checkbox for checkout pane
 */

/**
 * Implements base_settings_form().
 */
function commerce_agree_terms_pane_settings_form($checkout_pane) {
  $form = array();

  $form['commerce_agree_terms_pane_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Pane title'),
    '#default_value' => variable_get('commerce_agree_terms_pane_title', t('Terms and Conditions')),
    '#required' => TRUE,
  );
  $form['commerce_agree_terms_checkbox_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkbox label'),
    '#default_value' => variable_get('commerce_agree_terms_checkbox_label', t('I agree with the %terms')),
    '#description' => t('%terms is the link (opening in a new tab) with the pane title as the link text'),
    '#required' => TRUE,
  );
  $form['commerce_agree_terms_pane_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Terms and Conditions path'),
    '#default_value' => variable_get('commerce_agree_terms_pane_node'),
    '#description' => t('The internal Drupal path to your terms and conditions node (or an external URL)'),
    '#required' => TRUE,
  );
  $form['commerce_agree_terms_new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open the link in a new window'),
    '#default_value' => variable_get('commerce_agree_terms_new_window', 1),
  );

  return $form;
}

/**
 * Implements base_checkout_form().
 */
function commerce_agree_terms_pane_checkout_form($form, $form_state, $checkout_pane, $order) {

  $title = variable_get('commerce_agree_terms_pane_title');
  $link_url = variable_get('commerce_agree_terms_pane_node');

  // Build the link, in the same window or a new one.
  if (variable_get('commerce_agree_terms_new_window') == 0) {
    $link = l($title, $link_url);
  }
  else {
    $link = l($title, $link_url, array(
      'attributes' => array(
        'target' => '_blank',
      ),
    ));
  }
  // Position the link in the label using the %terms placeholder.
  $label = strtr(variable_get('commerce_agree_terms_checkbox_label'), array('%terms' => $link));

  // Create the checkbox.
  $checkout_form['commerce_agree_terms_pane_field_display'] = array(
    '#markup' => variable_get('commerce_agree_terms_pane_field', ''),
  );
  $checkout_form['commerce_agree_terms_pane_field'] = array(
    '#type' => 'checkbox',
    '#title' => $label,
    '#required' => TRUE,
  );
  return $checkout_form;
}
