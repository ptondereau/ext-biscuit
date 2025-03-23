<?php
// Create a key pair for signing
$kp = new BiscuitKeyPair();
var_dump($kp instanceof BiscuitKeyPair);

// Create a token with some facts
$builder = new BiscuitBuilder();
var_dump($builder instanceof BiscuitBuilder);

$builder->addFact('user("1234")');
$builder->addFact('right("read")');

$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

// Create an authorizer builder
$authBuilder = new BiscuitAuthorizerBuilder();
var_dump($authBuilder instanceof BiscuitAuthorizerBuilder);

// Add facts and rules
$authBuilder->addFact('resource("file1.txt")');
$authBuilder->addRule('allow($user, $right, $resource) <- user($user), right($right), resource($resource)');

// Build the authorizer with the token
$authorizer = $authBuilder->build($token);
var_dump($authorizer instanceof BiscuitAuthorizer);

// Test authorization
var_dump($authorizer->authorize());

// Test with deny policy
$authBuilder = new BiscuitAuthorizerBuilder();
$authBuilder->addFact('resource("file1.txt")');
$authBuilder->addPolicy('deny if true');

$authorizer = $authBuilder->build($token);
var_dump($authorizer->authorize());
?>
