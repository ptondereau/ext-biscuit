--TEST--
Biscuit error handling test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test error handling functions
var_dump(biscuit_error_message() === "");
var_dump(biscuit_error_kind() === BISCUIT_ERROR_NONE);
var_dump(biscuit_error_check_count() === 0);

// Test invalid key pair deserialization
try {
    BiscuitKeyPair::deserialize("invalid data");
    var_dump(false); // Should not reach here
} catch (Exception $e) {
    var_dump(true);
    var_dump($e->getMessage() === "Invalid key data length");
}

// Test invalid token deserialization
try {
    BiscuitToken::deserialize("invalid token data");
    var_dump(false); // Should not reach here
} catch (Exception $e) {
    var_dump(true);
}

// Test invalid fact syntax
$builder = new BiscuitBuilder();
var_dump($builder->addFact("invalid fact") === false);

// Test invalid rule syntax
var_dump($builder->addRule("invalid rule") === false);

// Test invalid check syntax
var_dump($builder->addCheck("invalid check") === false);

// Test building token without key pair
try {
    $builder->build(null);
    var_dump(false); // Should not reach here
} catch (TypeError $e) {
    var_dump(true);
}

// Test authorizer with invalid policy
$kp = new BiscuitKeyPair();
$token = $builder->build($kp);
$auth = $token->authorizer();
var_dump($auth->addPolicy("invalid policy") === false);
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