<?php
// Test KeyPair creation with no parameters - should throw exception
try {
    $keypair = new BiscuitKeyPair();
} catch (BiscuitException $e) {
    var_dump($e->getMessage() === "Invalid key data length");
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
$pubkey = $keypair2->public();
var_dump($pubkey instanceof BiscuitPublicKey);

// Test serialization
$serialized = $keypair2->serialize();
var_dump(is_string($serialized));
var_dump(strlen($serialized) === 32);

// Test deserialization
$deserialized = BiscuitKeyPair::deserialize($serialized);
var_dump($deserialized instanceof BiscuitKeyPair);

?>
