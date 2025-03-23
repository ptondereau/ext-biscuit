<?php
// Create a key pair for signing
$kp = new BiscuitKeyPair();
var_dump($kp instanceof BiscuitKeyPair);

// Create a token with context
$builder = new BiscuitBuilder();
var_dump($builder instanceof BiscuitBuilder);

// Set context and add facts
$builder->setContext('{"env": "production", "service": "api"}');
$builder->addFact('user("1234")');
$builder->addFact('right("read")');

$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

// Create an authorizer and test context-based rules
$authorizer = $token->authorizer();
var_dump($authorizer instanceof BiscuitAuthorizer);

// Add context-based rules
$authorizer->addRule('prod_user($user) <- user($user), context("env", "production")');
$authorizer->addRule('api_access($user) <- prod_user($user), context("service", "api")');

// Add policies that require context
$authorizer->addPolicy('allow if api_access($user)');

// Test authorization with context
var_dump($authorizer->authorize());

// Create a new block with different context
$blockBuilder = new BiscuitBlockBuilder();
$blockBuilder->addFact('context("env", "staging")');

$newToken = $token->appendBlock($blockBuilder);
var_dump($newToken instanceof BiscuitToken);

// Test authorization with modified context
$authorizer = $newToken->authorizer();
$authorizer->addRule('prod_user($user) <- user($user), context("env", "production")');
$authorizer->addRule('api_access($user) <- prod_user($user), context("service", "api")');
$authorizer->addPolicy('allow if api_access($user)');

// Should fail due to env being staging
var_dump($authorizer->authorize());
?>
