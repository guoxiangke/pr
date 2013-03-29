<?php
/**
 * return a form setting of PR roles involved.
 */
function camplus_pr_roles_involved_settings_form($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  $count = 0;
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  $default_value = 0;
	foreach ($roles as $key => $role_name) {
		if (in_array($role_name, array('administrator'))) continue;

    if($camplus_pr_approvable_role_involved){
      $default_value =  $camplus_pr_approvable_role_involved[$role_name];
    }
    $form['involved'][$role_name] =  array(
        '#type' => 'checkbox',
        '#title' => $role_name,
        '#default_value' => $default_value,
      );
    $count++;
	}
  $form['a_help'] = array('#markup' => t('注意:一经设置，不可取消,可添加不可删减,请管理员慎重操作!'));
  if(!$count) {
  	$form['empty_text'] = array('#markup' => t('没有可用的角色！请为相关角色'.l('添加权限','admin/people/permissions').'“Camplus Purchase Request approvable”'));
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
      $camplus_pr_approvable_role_involved[$role_name] = $value;
    }
  }
  variable_set('camplus_pr_approvable_role_involved',$camplus_pr_approvable_role_involved);
}

function camplus_pr_roles_weight_settings_form($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  $count = 0;
  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $default_value = 'NULL';
  foreach ($roles as $key => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
      if($camplus_pr_approvable_role_weight){
        $default_value =  $camplus_pr_approvable_role_weight[$role_name];
      }
    $form[$role_name]['approvable_role_weight'][$role_name] = array(
      '#type' => 'textfield',
      '#size' => 20, 
      '#default_value' => $default_value,
    );
    $count++;
  }

  if(!$count) {
    $form['empty_text'] = array('#markup' => t('没有可用的角色！请为相关角色'.l('添加权限','admin/people/permissions').'“Camplus Purchase Request approvable”'));
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

function camplus_pr_roles_weight_settings_form_submit($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  foreach ($form_state['values'] as $role_name => $value) {
    if(in_array($role_name, $roles)) {
      $camplus_pr_approvable_role_weight[$role_name] = $value;
    }
  }
  variable_set('camplus_pr_approvable_role_weight', $camplus_pr_approvable_role_weight);
}
/**
 * Returns HTML
 */
function theme_camplus_pr_roles_weight_settings_form($variables) {
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
  $warning = '<div class="messages warning">The first role(Min number weight) must be The Department specific role. </div>';
  return $warning . $output;
}

function camplus_pr_range_settings_form() {
   $i=0;
   $range = variable_get('camplus_pr_settings_range', '5');
   $range_settings = variable_get('camplus_pr_range_settings', ''); 
   while($i<$range){
      $form[$i]['range']["pr_range_begin_$i"] = array(
        '#type' => 'textfield',
        '#default_value' =>$range_settings[$i]["begin"],
        '#prefix' => 'HK$',
        '#size' => 20, 
      );
      $form[$i]['range']["pr_range_end_$i"] = array(
        '#type' => 'textfield',
        '#default_value' =>$range_settings[$i]["end"],
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
  $pattern = '/\d+/';
  $return = array();

  foreach ($form_state['values'] as $key => $value) {
    $subject = $key;
    if(strstr($key, 'pr_range_begin')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match($pattern, $subject, $matches);
      $range_settings[$matches[0]]['begin'] = $form_state['values'][$key];
    }elseif(strstr($key, 'pr_range_end')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match($pattern, $subject, $matches);
      $range_settings[$matches[0]]['end'] = $form_state['values'][$key];
    }
  }

  dpm($range_settings,'$range_settings');
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
  $form['camplus_pr_financial_year_begin'] = array(
    '#type' => 'textfield',
    '#title' => t('FINANCIAL YEAR Begin'),
    '#default_value' => variable_get('camplus_pr_financial_year_begin', '09-01'),
    '#required' => TRUE,
  );  
  $form['camplus_pr_financial_year_end'] = array(
    '#type' => 'textfield',
    '#title' => t('FINANCIAL YEAR ENd'),
    '#default_value' => variable_get('camplus_pr_financial_year_end', '08-31'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

function camplus_pr_approve_settings_form() {

  $count_rows =  variable_get('camplus_pr_settings_range', '5');
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    if(!$camplus_pr_approvable_role_involved[$role_name]) continue;
    $weight = $camplus_pr_approvable_role_weight[$role_name];
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);

  $workflow_settings = variable_get('camplus_pr_workflow_settings', '');
  dpm($workflow_settings);
  for($i = 0; $i < $count_rows; $i++) {
    foreach ($order as $key => $role) {
      $default_value = 0;
      if(isset($workflow_settings[$i][$role['rid']])) {
        $default_value = $workflow_settings[$i][$role['rid']];
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
  // foreach ($form_state['values'] as $key => $value) {
  //   if(strstr($key, '-workflow-')) {
  //     $workflow_settings[$key] = $form_state['values'][$key];
  //   }
  // }

  foreach ($form_state['values'] as $key => $value) {
    $subject = $key;
    if(strstr($key, '-workflow-')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match('/\d+-/', $subject, $matches);
      $index = str_replace('-', '', $matches[0]);
      preg_match('/-\d+/', $subject, $matches);
      $rid = str_replace('-', '', $matches[0]);
      $workflow_settings[$index][$rid] = $form_state['values'][$key];
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

  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    if(!$camplus_pr_approvable_role_involved[$role_name]) continue;
    $weight = $camplus_pr_approvable_role_weight[$role_name];
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);  

 $range_settings =  variable_get('camplus_pr_range_settings');

  for($i = 0; $i < $count_rows; $i++) {
    $row = array();
    $row[] = $range_settings[$i]["begin"] .'--'. $range_settings[$i]["end"];
    foreach ($order as $key => $role) {
      $row[] = drupal_render($form[$i][$i.'-workflow-'.$role['rid']]);
    }
    $row = array('data' => $row);
    $rows[] = $row;
  }
  $header[] = 'Range'.'(HK$)';
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