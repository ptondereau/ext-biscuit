--TEST--
Biscuit memory management test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test object creation and destruction
function testObjectLifecycle() {
    // Create objects
    $kp = new BiscuitKeyPair();
    $builder = new BiscuitBuilder();
    $builder->addFact('user("1234")');
    $token = $builder->build($kp);
    
    // Get public key
    $publicKey = $kp->public();
    
    // Create block builder
    $blockBuilder = new BiscuitBlockBuilder();
    $blockBuilder->addFact('resource("file1.txt")');
    
    // Append block
    $newToken = $token->appendBlock($blockBuilder);
    
    // Create authorizer
    $authorizer = $newToken->authorizer();
    $authorizer->addPolicy('allow if true');
    
    // Let objects go out of scope
    unset($authorizer);
    unset($newToken);
    unset($blockBuilder);
    unset($publicKey);
    unset($token);
    unset($builder);
    unset($kp);
    
    return true;
}

// Run multiple cycles of object creation and destruction
for ($i = 0; $i < 5; $i++) {
    var_dump(testObjectLifecycle());
}

// Test serialization memory management
function testSerializationMemory() {
    $kp = new BiscuitKeyPair();
    $serialized = $kp->serialize();
    
    // Create multiple deserialized copies
    $copies = [];
    for ($i = 0; $i < 5; $i++) {
        $copies[] = BiscuitKeyPair::deserialize($serialized);
    }
    
    // Let copies go out of scope
    unset($copies);
    unset($serialized);
    unset($kp);
    
    return true;
}

var_dump(testSerializationMemory());

// Test token building with multiple blocks
function testTokenBuilding() {
    $kp = new BiscuitKeyPair();
    $builder = new BiscuitBuilder();
    $token = $builder->build($kp);
    
    // Add multiple blocks
    for ($i = 0; $i < 5; $i++) {
        $blockBuilder = new BiscuitBlockBuilder();
        $blockBuilder->addFact("fact{$i}(\"test\")");
        $token = $token->appendBlock($blockBuilder);
        unset($blockBuilder);
    }
    
    // Create and destroy multiple authorizers
    for ($i = 0; $i < 5; $i++) {
        $authorizer = $token->authorizer();
        $authorizer->addPolicy("allow if fact{$i}(\"test\")");
        var_dump($authorizer->authorize());
        unset($authorizer);
    }
    
    return true;
}

var_dump(testTokenBuilding());

// Test error handling memory management
function testErrorHandling() {
    $builder = new BiscuitBuilder();
    
    // Generate some errors
    for ($i = 0; $i < 5; $i++) {
        $builder->addFact("invalid syntax {$i}");
        var_dump(biscuit_error_message() !== "");
    }
    
    return true;
}

var_dump(testErrorHandling());

// Force garbage collection
gc_collect_cycles();
var_dump(true);
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
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true) 