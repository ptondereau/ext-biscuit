--TEST--
Biscuit token creation and manipulation test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) {
    echo 'skip';
}
?>
--FILE--
<?php
// Create a key pair for signing
$seed = random_bytes(32);
$keypair = new BiscuitKeyPair($seed);

// Create a token builder
$builder = new BiscuitBuilder();
var_dump($builder instanceof BiscuitBuilder);

// Add some facts and rules
$builder->setContext("test context")
    ->addFact("right(\"file1\", \"read\")")
    ->addRule("allow(\"read\") <- right(\"file1\", \"read\")")
    ->addCheck("check if right(\"file1\", \"read\")");

// Build the token
$token = $builder->build($keypair, $seed);
var_dump($token instanceof BiscuitToken);

// Test token serialization
$serialized = $token->serialize();
var_dump(is_string($serialized));

// Create an authorizer
$authorizer = $token->createAuthorizer();
var_dump($authorizer instanceof BiscuitAuthorizer);

// Test authorization
var_dump($authorizer->authorize());

// Test token block operations
var_dump($token->blockCount() === 1);
var_dump(is_string($token->blockContext(0)));

// Create a new block
$block = new BiscuitBlockBuilder();
var_dump($block instanceof BiscuitBlockBuilder);

// Add facts to the block
$block->setContext("block2 context")
    ->addFact("right(\"file2\", \"write\")");

// Append the block to the token
$newToken = $token->appendBlock($block, $keypair);
var_dump($newToken instanceof BiscuitToken);
var_dump($newToken->blockCount() === 2);

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)