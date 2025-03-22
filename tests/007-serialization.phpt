--TEST--
Biscuit serialization test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test KeyPair serialization
$kp = new BiscuitKeyPair();
$serializedKp = $kp->serialize();
var_dump(strlen($serializedKp) === 32);

$deserializedKp = BiscuitKeyPair::deserialize($serializedKp);
var_dump($deserializedKp instanceof BiscuitKeyPair);

// Test PublicKey serialization
$publicKey = $kp->public();
$serializedPk = $publicKey->serialize();
var_dump(strlen($serializedPk) === 32);

$deserializedPk = BiscuitPublicKey::deserialize($serializedPk);
var_dump($deserializedPk instanceof BiscuitPublicKey);

// Test Token serialization
$builder = new BiscuitBuilder();
$builder->addFact('user("1234")');
$builder->addFact('right("read")');
$builder->addRule('allow($user, $right) <- user($user), right($right)');

$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

$serializedToken = $token->serialize();
var_dump(strlen($serializedToken) > 0);

$deserializedToken = BiscuitToken::deserialize($serializedToken);
var_dump($deserializedToken instanceof BiscuitToken);

// Test that deserialized token works
$authorizer = $deserializedToken->authorizer();
$authorizer->addPolicy('allow if allow($user, $right)');
var_dump($authorizer->authorize());

// Test that deserialized key pair can sign
$newBuilder = new BiscuitBuilder();
$newBuilder->addFact('test("success")');
$newToken = $newBuilder->build($deserializedKp);
var_dump($newToken instanceof BiscuitToken);

// Test that deserialized public key is valid
$newPublicKey = $deserializedKp->public();
$serializedNewPk = $newPublicKey->serialize();
var_dump($serializedNewPk === $serializedPk);
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