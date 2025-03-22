--TEST--
Biscuit algorithm support test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test Ed25519 algorithm (default)
$kp = new BiscuitKeyPair();
var_dump($kp instanceof BiscuitKeyPair);

$serialized = $kp->serialize();
$deserialized = BiscuitKeyPair::deserialize($serialized);
var_dump($deserialized instanceof BiscuitKeyPair);

// Test with explicit Ed25519 algorithm
$kp = new BiscuitKeyPair(null, Ed25519);
var_dump($kp instanceof BiscuitKeyPair);

$serialized = $kp->serialize();
$deserialized = BiscuitKeyPair::deserialize($serialized, Ed25519);
var_dump($deserialized instanceof BiscuitKeyPair);

// Test with seed
$seed = random_bytes(32);
$kp = new BiscuitKeyPair($seed);
var_dump($kp instanceof BiscuitKeyPair);

$serialized = $kp->serialize();
$deserialized = BiscuitKeyPair::deserialize($serialized);
var_dump($deserialized instanceof BiscuitKeyPair);

// Test public key with algorithm
$publicKey = $kp->public();
var_dump($publicKey instanceof BiscuitPublicKey);

$serialized = $publicKey->serialize();
$deserialized = BiscuitPublicKey::deserialize($serialized, Ed25519);
var_dump($deserialized instanceof BiscuitPublicKey);

// Test token creation with different key pairs
$builder = new BiscuitBuilder();
$builder->addFact('test("algorithm")');

$token1 = $builder->build($kp);
var_dump($token1 instanceof BiscuitToken);

$kp2 = new BiscuitKeyPair(null, Ed25519);
$token2 = $builder->build($kp2);
var_dump($token2 instanceof BiscuitToken);

// Verify that tokens can be serialized and deserialized
$serialized1 = $token1->serialize();
$deserialized1 = BiscuitToken::deserialize($serialized1);
var_dump($deserialized1 instanceof BiscuitToken);

$serialized2 = $token2->serialize();
$deserialized2 = BiscuitToken::deserialize($serialized2);
var_dump($deserialized2 instanceof BiscuitToken);
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