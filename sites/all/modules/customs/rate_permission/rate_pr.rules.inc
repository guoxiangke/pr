<?php
//del also before ,we need after rate,use js to ajax.
/**
 * @file Includes any rules integration provided by the module.
 */
 /**
 * implementation of hook_rules_condition_info()
 */
function rate_pr_rules_condition_info() {
  return array(
    'rate_pr_condition_all_approved' => array(
      'label' => t('If all approved the pr.'),
      'arguments' => array(
        'new_answer' => array('type' => 'node', 'label' => t('The vote node.')),
      ),
      'module' => 'rate_pr',
      'group' => t('Customs'),
    ),
  );
}
/**
 * Condition rate_pr_condition_all_approved
 */
function rate_pr_condition_all_approved($node) {
  $widget = _camplus_pr_get_approve_rate($node);
  if(!isset($widget->id)) return FALSE;
  $approve_status = _rate_pr_check_permissions($node,$widget);
  global $debug;
  if($debug) watchdog('ooooo1', ''.print_r($approve_status,TRUE), $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL);
  //oh no ,didn't work. should do this after done.
  //http://drupal.org/project/voting_rules
  if($approve_status['workflow_status'] == 'approved') {  
    return TRUE;
  }
  return FALSE;
}