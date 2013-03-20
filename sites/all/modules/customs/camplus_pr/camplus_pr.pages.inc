<?php
/**
 * return a form setting of PR roles involved.
 */
function camplus_pr_roles_involved_settings_form($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

	foreach ($roles as $key => $role_name) {
		if (in_array($role_name, array('administrator'))) continue;
		// $form[$key]['role_name'] = array('#markup' => check_plain($role_name));
    $form[$role_name]['approvable_role_weight'][$role_name] = array(
      '#type' => 'textfield',
      '#size' => 20, 
      '#default_value' => variable_get('approvable_role_weight_'.$role_name, '1'),
    );
	}
  if(!count($roles)){
  	$form['empty_text'] = array('#markup' => t('没有可用的角色！请为相关角色添加权限“Camplus Purchase Request approvable”'));
  	return $form;
  }
	// Add the buttons.
	$form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
	return  $form;
}

function camplus_pr_roles_involved_settings_form_submit($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  foreach ($form_state['values'] as $role_name => $value) {
    if(in_array($role_name, $roles)) {
      variable_set('approvable_role_weight_'.$role_name, $value);
    }
  }
}

/**
 * Returns HTML
 */
function theme_camplus_pr_roles_involved_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  foreach (element_children($form) as $role_name) { //dpm($key);
    if (isset($form[$role_name]['approvable_role_weight'])) {
      $row = array();
      $row[] = $role_name;
      $row[] = drupal_render($form[$role_name]['approvable_role_weight']);
      $row = array('data' => $row);
      $rows[] = $row;
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
	$rows[] = array(array('data' => drupal_render($form['name']) .drupal_render($form['add']), 'colspan' => 4));
  $header = array(t('Role'), t('Weight for approvable role'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);

  return $output;
}

function camplus_pr_range_settings_form() {
   $i=0;
   $range = variable_get('camplus_pr_settings_range', '5');
   $range_settings = variable_get('camplus_pr_range_settings', ''); 
   while($i<$range){
      $form[$i]['range']["pr_range_begin_$i"] = array(
        '#type' => 'textfield',
        '#default_value' =>$range_settings["pr_range_begin_$i"],
        '#prefix' => 'HK$',
        '#size' => 20, 
      );
      $form[$i]['range']["pr_range_end_$i"] = array(
        '#type' => 'textfield',
        '#default_value' =>$range_settings["pr_range_end_$i"],
        '#prefix' => 'HK$',
        '#size' => 20, 
      );
      $i++;
    }
      // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return  $form;
}

function camplus_pr_range_settings_form_submit($form, &$form_state) {
  dpm($form_state['values']);
  foreach ($form_state['values'] as $key => $value) {
    if(strstr($key, 'pr_range_')) {
      $range_settings[$key] = $form_state['values'][$key];
    }
  }
  variable_set('camplus_pr_range_settings', $range_settings);
}

function theme_camplus_pr_range_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  foreach (element_children($form) as $i) { //dpm($key);
    if (isset($form[$i]['range'])) {
      $row = array();
      $row[] = $i+1;
      $row[] = drupal_render($form[$i]['range']["pr_range_begin_$i"]);
      $row[] = drupal_render($form[$i]['range']["pr_range_end_$i"]);
      $row = array('data' => $row);
      $rows[] = $row;
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
  $rows[] = array(array('data' => drupal_render($form['name']) .drupal_render($form['add']), 'colspan' => 4));
  $header = array(t('No'), t('Begin'), t('End'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);

  return $output;
}

function camplus_pr_settings_form() {
  $form['camplus_pr_settings_range'] = array(
    '#type' => 'textfield',
    '#title' => t('Range Number'),
    '#default_value' => variable_get('camplus_pr_settings_range', '5'),
    '#description' => 'how many group of settings',
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

function camplus_pr_approve_settings_form() {

  $count_rows =  variable_get('camplus_pr_settings_range', '5');
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    $weight = variable_get('approvable_role_weight_'.$role_name);
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);  


  $workflow_settings = variable_get('camplus_pr_workflow_settings', '');
  for($i = 1; $i <= $count_rows; $i++) {
    foreach ($order as $key => $role) {
      $default_value = 0;
      if(isset($workflow_settings[$i.'-workflow-'.$role['rid']])){
        $default_value =  $workflow_settings[$i.'-workflow-'.$role['rid']];
      }
      $form[$i][$i.'-workflow-'.$role['rid']] = array(
        '#type' => 'checkbox',
        '#default_value' => $default_value,
      );
    }
  }


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return  $form;
}

function camplus_pr_approve_settings_form_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    if(strstr($key, '-workflow-')) {
      $workflow_settings[$key] = $form_state['values'][$key];
    }
  }
  variable_set('camplus_pr_workflow_settings', $workflow_settings);
}

function theme_camplus_pr_approve_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  $count_rows =  variable_get('camplus_pr_settings_range', '5');
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    $weight = variable_get('approvable_role_weight_'.$role_name);
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);  

 $range_settings =  variable_get('camplus_pr_range_settings');

  for($i = 1; $i <= $count_rows; $i++) {
    $row = array();
    $j = $i-1;
    $row[] = $range_settings["pr_range_begin_$j"] .'--'. $range_settings["pr_range_end_$j"];
    foreach ($order as $key => $role) {
      $row[] = drupal_render($form[$i][$i.'-workflow-'.$role['rid']]);
    }
    $row = array('data' => $row);
    $rows[] = $row;
  }
  $header[] = 'Range';
  foreach ($order as $key => $role) {
    $header[] = $role['name'];
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);

  return $output;
}