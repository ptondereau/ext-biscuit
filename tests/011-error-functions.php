<?php
// Test initial error state
var_dump(biscuit_error_message() === "");
var_dump(biscuit_error_kind() === BISCUIT_ERROR_NONE);
var_dump(biscuit_error_check_count() === 0);

// Create a token with a check that will fail
$kp = new BiscuitKeyPair();
$builder = new BiscuitBuilder();

$builder->addFact('user("1234")');
$builder->addCheck('check if false'); // This check will always fail

$token = $builder->build($kp);
$authorizer = $token->authorizer();

// Test authorization with failing check
var_dump($authorizer->authorize() === false);

// Test error state after failed check
var_dump(biscuit_error_message() !== "");
var_dump(biscuit_error_kind() !== BISCUIT_ERROR_NONE);
var_dump(biscuit_error_check_count() === 1);

// Test with invalid datalog
$builder = new BiscuitBuilder();
var_dump($builder->addFact("invalid datalog syntax") === false);

// Test error state after invalid datalog
var_dump(biscuit_error_message() !== "");
var_dump(biscuit_error_kind() !== BISCUIT_ERROR_NONE);

// Test with multiple failing checks
$builder = new BiscuitBuilder();
$builder->addFact('user("1234")');
$builder->addCheck('check if false');
$builder->addCheck('check if 1 == 2');

$token = $builder->build($kp);
$authorizer = $token->authorizer();

var_dump($authorizer->authorize() === false);
var_dump(biscuit_error_check_count() === 2);

// Test error state reset
$builder = new BiscuitBuilder();
$builder->addFact('user("1234")');
$token = $builder->build($kp);
$authorizer = $token->authorizer();
$authorizer->addPolicy('allow if user($user)');

var_dump($authorizer->authorize() === true);
var_dump(biscuit_error_message() === "");
var_dump(biscuit_error_kind() === BISCUIT_ERROR_NONE);
var_dump(biscuit_error_check_count() === 0);
?>
