<?php
// Create a key pair for signing
$kp = new BiscuitKeyPair();
var_dump($kp instanceof BiscuitKeyPair);

// Create a token with initial facts
$builder = new BiscuitBuilder();
var_dump($builder instanceof BiscuitBuilder);

$builder->addFact('user("1234")');
$builder->addFact('right("read")');

$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

// Create a block builder
$blockBuilder = new BiscuitBlockBuilder();
var_dump($blockBuilder instanceof BiscuitBlockBuilder);

// Add facts and rules to the block
$blockBuilder->addFact('resource("file1.txt")');
$blockBuilder->addRule('allow($user, "write", $resource) <- user($user), resource($resource)');

// Append the block to the token
$newToken = $token->appendBlock($blockBuilder);
var_dump($newToken instanceof BiscuitToken);

// Create an authorizer to test the appended block
$authorizer = $newToken->authorizer();
var_dump($authorizer instanceof BiscuitAuthorizer);

// Add a policy that requires both read and write rights
$authorizer->addPolicy('allow if right("read")');
$authorizer->addPolicy('allow if allow($user, "write", $resource)');

// Test authorization
var_dump($authorizer->authorize());

// Test with a block that adds a deny rule
$blockBuilder = new BiscuitBlockBuilder();
$blockBuilder->addRule('deny($user) <- user($user)');

$finalToken = $newToken->appendBlock($blockBuilder);
var_dump($finalToken instanceof BiscuitToken);

$authorizer = $finalToken->authorizer();
$authorizer->addPolicy('allow if right("read")');
$authorizer->addPolicy('deny if deny($user)');

// Should fail due to deny rule
var_dump($authorizer->authorize());
?>
