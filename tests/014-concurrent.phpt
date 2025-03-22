--TEST--
Biscuit concurrent operations test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test concurrent token creation and validation
function worker($id) {
    $kp = new BiscuitKeyPair();
    $builder = new BiscuitBuilder();
    
    $builder->addFact("worker({$id})");
    $builder->addFact('right("read")');
    
    $token = $builder->build($kp);
    
    $blockBuilder = new BiscuitBlockBuilder();
    $blockBuilder->addFact("task({$id})");
    
    $token = $token->appendBlock($blockBuilder);
    
    $authorizer = $token->authorizer();
    $authorizer->addPolicy("allow if worker({$id}), task({$id})");
    
    return $authorizer->authorize();
}

// Run multiple workers
$results = [];
for ($i = 0; $i < 5; $i++) {
    $results[] = worker($i);
}

foreach ($results as $result) {
    var_dump($result);
}

// Test concurrent key pair operations
function keyWorker($id) {
    $kp = new BiscuitKeyPair();
    $serialized = $kp->serialize();
    $deserialized = BiscuitKeyPair::deserialize($serialized);
    
    $publicKey = $kp->public();
    $serializedPk = $publicKey->serialize();
    $deserializedPk = BiscuitPublicKey::deserialize($serializedPk);
    
    return true;
}

$results = [];
for ($i = 0; $i < 5; $i++) {
    $results[] = keyWorker($i);
}

foreach ($results as $result) {
    var_dump($result);
}

// Test concurrent authorizer operations
function authWorker($id) {
    $kp = new BiscuitKeyPair();
    $builder = new BiscuitBuilder();
    
    for ($i = 0; $i < 3; $i++) {
        $builder->addFact("fact{$i}({$id})");
    }
    
    $token = $builder->build($kp);
    
    $authorizers = [];
    for ($i = 0; $i < 3; $i++) {
        $authorizer = $token->authorizer();
        $authorizer->addPolicy("allow if fact{$i}({$id})");
        $authorizers[] = $authorizer->authorize();
    }
    
    return count(array_filter($authorizers)) === 3;
}

$results = [];
for ($i = 0; $i < 5; $i++) {
    $results[] = authWorker($i);
}

foreach ($results as $result) {
    var_dump($result);
}

// Test concurrent block operations
function blockWorker($id) {
    $kp = new BiscuitKeyPair();
    $builder = new BiscuitBuilder();
    $builder->addFact("base({$id})");
    
    $token = $builder->build($kp);
    
    for ($i = 0; $i < 3; $i++) {
        $blockBuilder = new BiscuitBlockBuilder();
        $blockBuilder->addFact("block{$i}({$id})");
        $token = $token->appendBlock($blockBuilder);
    }
    
    $authorizer = $token->authorizer();
    $authorizer->addPolicy("allow if base({$id})");
    
    for ($i = 0; $i < 3; $i++) {
        $authorizer->addPolicy("allow if block{$i}({$id})");
    }
    
    return $authorizer->authorize();
}

$results = [];
for ($i = 0; $i < 5; $i++) {
    $results[] = blockWorker($i);
}

foreach ($results as $result) {
    var_dump($result);
}
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