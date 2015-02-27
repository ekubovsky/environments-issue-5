<?php

/**
 * @file
 * Export interface plugin for Environment Task Bundles.
 */

$module_path = drupal_get_path('module', 'environments');

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'environments_bundles', // As defined in hook_schema().
  'access' => 'administer environments', // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/config/development',
    'menu item' => 'environments-bundles',
    'menu title' => 'Environments Bundles',
    'menu description' => 'Manage environment task bundles.',

    // Add extra menu items.
    'items' => array(
      // Manage Tasks form.
      'tasks' => array(
        'path' => 'list/%ctools_export_ui/tasks',
        'title' => 'Manage Tasks',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('environments_task_form', 5),
        'access arguments' => array('administer environments'),
        'file' => 'environments.admin.inc',
        'file path' => $module_path,
        'type' => MENU_LOCAL_TASK,
        'weight' => -5,
      ),
      // Add new task form.
      'task add' => array(
        'path' => 'list/%ctools_export_ui/tasks/add',
        'title' => 'Add Task',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('environments_task_form_edit', 5),
        'access arguments' => array('administer environments'),
        'file' => 'environments.admin.inc',
        'file path' => $module_path,
        'type' => MENU_LOCAL_ACTION,
      ),
      // Edit task form.
      'task edit' => array(
        'path' => 'list/%ctools_export_ui/tasks/%/edit',
        'title' => 'Edit Task',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('environments_task_form_edit', 5, 7),
        'access arguments' => array('administer environments'),
        'file' => 'environments.admin.inc',
        'file path' => $module_path,
      ),
      // Delete task form.
      'task delete' => array(
        'path' => 'list/%ctools_export_ui/tasks/%/delete',
        'title' => 'Delete Task',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('environments_task_form_delete', 5, 7),
        'access arguments' => array('administer environments'),
        'file' => 'environments.admin.inc',
        'file path' => $module_path,
      ),
    ),
  ),

  // Define user interface texts.
  'title singular' => t('Task bundle'),
  'title plural' => t('Task bundles'),
  'title singular proper' => t('Task Bundle'),
  'title plural proper' => t('Task Bundles'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'environments_ctools_export_ui_form_bundles',
    'submit' => 'environments_ctools_export_ui_form_bundles_submit',
  ),

  // Override the UI handler.
  'handler' => array(
    'class' => 'environments_bundles_ctools_export_ui_handler',
    'parent' => 'ctools_export_ui',
  ),

  // Add an extra operation.
  'allowed operations' => array(
    'tasks'  => array('title' => t('Manage Tasks')),
  ),

);

/**
 * Export UI form
 */
function environments_ctools_export_ui_form_bundles(&$form, &$form_state) {
  // Load the admin form include.
  module_load_include('inc', 'environments_bundles', 'environments_bundles.admin');

  // Make environment reference in form_state.
  $form_state['bundle'] = &$form_state['item'];

  // Load the configuration form.
  $form = drupal_retrieve_form('environments_bundles_form_edit', $form_state);
}

/**
 * Submit handler.
 *
 * @see environments_form_edit()
 */
function environments_ctools_export_ui_form_bundles_submit(&$form, &$form_state) {
  // Edit the reference to $form_state['bundle'] which will in turn
  // reference $form_state['item'] which is what CTools is looking for.
  $bundle = &$form_state['bundle'];
  $bundle->description = $form_state['values']['description'];
}