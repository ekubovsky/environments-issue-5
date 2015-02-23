<?php

/**
 * @file
 * Definition of the "module_disable" Env Task.
 */

$plugin = array(
	'admin_title' => t('Disable modules'),
	'task_callback' => 'env_task_module_disable',
	'settings' => array(
		'modules' => array(),
		'disable_dependents' => TRUE,
	),
	'settings_callback' => 'env_task_module_disable_settings',
);

/**
 * Form callback.
 *
 * Returns the settings form for this task.
 *
 * This is not a typical form callback in that we don't get a $form or
 * $form_state.
 *
 * @param stdClass
 *   The current environment.
 * @param array
 *   The current task.
 *
 * @return array
 *   A Form API array of task settings.
 */
function env_task_module_disable_settings($environment, $task = NULL) {
	$form = array();

	$form['modules'] = array(
		'#name' => 'settings[modules]',
		'#type' => 'select',
		'#title' => t('Modules'),
		'#multiple' => TRUE,
		'#options' => _env_get_modules(),
		'#empty_option' => t(' -Select some modules- '),
		'#default_value' => isset($task['settings']['modules']) ? $task['settings']['modules'] : array(),
	);

	$form['disable_dependents'] = array(
		'#name' => 'settings[disable_dependents]',
		'#type' => 'checkbox',
		'#title' => t('Disable dependents'),
		'#description' => t('If TRUE, dependent modules will automatically be disabled in the correct order.'),
		'#default_value' => isset($task['settings']['disable_dependents']) ? $task['settings']['disable_dependents'] : TRUE,
	);

	return $form;
}

/**
 * Task callback.
 *
 * @param array
 *   An array of settings for the task.
 * @param array
 *   $context is an array that will contain information about the
 *   status of the batch. The values in $context will retain their
 *   values as the batch progresses.
 */
function env_task_module_disable($settings, &$context) {
	$modules = $settings['modules'];
	$disable_dependents = $settings['disable_dependents'];

	// Filter already-disabled modules.
	$messages = array();
	$modules_filtered = array();

	foreach ($modules as $module) {
		if (!module_exists($module)) {
			$messages[] = t('Can\'t disable module %module, it\'s not enabled.', array('%module' => $module));
		}
		else {
			$modules_filtered[] = $module;
		}
	}

	// Disable modules.
	if (!empty($modules_filtered)) {
		module_disable($modules_filtered, $disable_dependents);

		// Display this message before all others.
		array_unshift($messages, t('Disabled modules: %modules.', array('%module' => implode(', ', array_values($modules_filtered)))));
	}

	// Display messages.
	$context['message'] = implode("\n", $messages);
}