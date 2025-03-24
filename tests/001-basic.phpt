--TEST--
Basic Biscuit extension test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) {
    echo 'skip';
}
?>
--FILE--
<?php
// Test KeyPair creation with no parameters - should throw exception
try {
    $keypair = new BiscuitKeyPair();
} catch (BiscuitException $e) {
    var_dump($e->getMessage());
    var_dump($e->getCode());
}

// Test error handling functions
var_dump(biscuit_error_message());
var_dump(biscuit_error_kind());
var_dump(biscuit_error_check_count());

// Test KeyPair with seed
$seed = random_bytes(32);
$keypair2 = new BiscuitKeyPair($seed, BISCUIT_ALGORITHM_ED25519);
var_dump($keypair2 instanceof BiscuitKeyPair);

// Test PublicKey derivation
$pubkey = $keypair2->getPublicKey();
var_dump($pubkey instanceof BiscuitPublicKey);

// Test serialization
$serialized = $keypair2->serialize();
var_dump(is_string($serialized));
var_dump(strlen($serialized) === 32);

// Test deserialization
$deserialized = BiscuitKeyPair::deserialize($serialized);
var_dump($deserialized instanceof BiscuitKeyPair);

?>
--EXPECT--
string(29) "Invalid key: invalid argument"
int(1)
string(16) "invalid argument"
int(1)
int(0)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
