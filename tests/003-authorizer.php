<?php
// Create a key pair and a basic token
$keypair = new BiscuitKeyPair();
$builder = new BiscuitBuilder();
$builder->addFact("user(\"alice\")");
$builder->addFact("right(\"file1\", \"read\")");
$token = $builder->build($keypair);

// Create an authorizer builder
$authBuilder = new BiscuitAuthorizerBuilder();
var_dump($authBuilder instanceof BiscuitAuthorizerBuilder);

// Add facts, rules and policies
var_dump($authBuilder->addFact("resource(\"file1\")"));
var_dump($authBuilder->addRule("allowed(\"read\") <- user(\"alice\"), right(\"file1\", \"read\")"));
var_dump($authBuilder->addPolicy("allow if allowed(\"read\")"));

// Build the authorizer with token
$authorizer = $authBuilder->build($token);
var_dump($authorizer instanceof BiscuitAuthorizer);

// Test authorization
var_dump($authorizer->authorize());

// Test authorizer output
$output = $authorizer->print();
var_dump(is_string($output));
var_dump(strlen($output) > 0);

// Test unauthenticated authorizer
$unauthBuilder = new BiscuitAuthorizerBuilder();
$unauthBuilder->addFact("resource(\"file2\")");
$unauthBuilder->addPolicy("deny if true");
$unauthAuthorizer = $unauthBuilder->buildUnauthenticated();
var_dump($unauthAuthorizer instanceof BiscuitAuthorizer);

// This should fail because of the deny policy
var_dump($unauthAuthorizer->authorize() === false);

?>
