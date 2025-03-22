--TEST--
Biscuit stub file test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test class existence and inheritance
var_dump(class_exists('BiscuitKeyPair'));
var_dump(class_exists('BiscuitPublicKey'));
var_dump(class_exists('BiscuitBuilder'));
var_dump(class_exists('BiscuitToken'));
var_dump(class_exists('BiscuitBlockBuilder'));
var_dump(class_exists('BiscuitAuthorizer'));
var_dump(class_exists('BiscuitAuthorizerBuilder'));

// Test method signatures
$reflectionKeyPair = new ReflectionClass('BiscuitKeyPair');
var_dump($reflectionKeyPair->hasMethod('__construct'));
var_dump($reflectionKeyPair->hasMethod('public'));
var_dump($reflectionKeyPair->hasMethod('serialize'));
var_dump($reflectionKeyPair->hasMethod('deserialize'));

$reflectionBuilder = new ReflectionClass('BiscuitBuilder');
var_dump($reflectionBuilder->hasMethod('setContext'));
var_dump($reflectionBuilder->hasMethod('addFact'));
var_dump($reflectionBuilder->hasMethod('addRule'));
var_dump($reflectionBuilder->hasMethod('addCheck'));
var_dump($reflectionBuilder->hasMethod('build'));

// Test constant definitions
var_dump(defined('Ed25519'));
var_dump(defined('BISCUIT_ERROR_NONE'));

// Test function existence
var_dump(function_exists('biscuit_error_message'));
var_dump(function_exists('biscuit_error_kind'));
var_dump(function_exists('biscuit_error_check_count'));

// Test method parameter types
$method = $reflectionKeyPair->getMethod('__construct');
$params = $method->getParameters();
var_dump(count($params) === 2);
var_dump($params[0]->getName() === 'seed');
var_dump($params[0]->allowsNull());
var_dump($params[1]->getName() === 'algorithm');
var_dump($params[1]->isOptional());

$method = $reflectionBuilder->getMethod('build');
$params = $method->getParameters();
var_dump(count($params) === 2);
var_dump($params[0]->getClass()->getName() === 'BiscuitKeyPair');
var_dump($params[1]->getName() === 'seed');
var_dump($params[1]->allowsNull());

// Test return types
var_dump($reflectionKeyPair->getMethod('public')->hasReturnType());
var_dump($reflectionKeyPair->getMethod('public')->getReturnType()->getName() === 'BiscuitPublicKey');

var_dump($reflectionBuilder->getMethod('build')->hasReturnType());
var_dump($reflectionBuilder->getMethod('build')->getReturnType()->getName() === 'BiscuitToken');

// Test static methods
var_dump($reflectionKeyPair->getMethod('deserialize')->isStatic());
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true) 