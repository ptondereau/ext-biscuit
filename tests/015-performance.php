<?php
// Helper function to measure execution time
function measureTime($callback) {
    $start = microtime(true);
    $result = $callback();
    $end = microtime(true);
    return [
        'result' => $result,
        'time' => ($end - $start) * 1000 // Convert to milliseconds
    ];
}

// Test key pair generation performance
$keyPairTimes = [];
for ($i = 0; $i < 100; $i++) {
    $result = measureTime(function() {
        $kp = new BiscuitKeyPair();
        return $kp instanceof BiscuitKeyPair;
    });
    $keyPairTimes[] = $result['time'];
}
$avgKeyPairTime = array_sum($keyPairTimes) / count($keyPairTimes);
var_dump($avgKeyPairTime < 100); // Should be less than 100ms

// Test token building performance
$kp = new BiscuitKeyPair();
$tokenBuildTimes = [];
for ($i = 0; $i < 100; $i++) {
    $result = measureTime(function() use ($kp) {
        $builder = new BiscuitBuilder();
        $builder->addFact("user({$i})");
        $builder->addFact('right("read")');
        $builder->addRule('allow($user) <- user($user)');
        return $builder->build($kp) instanceof BiscuitToken;
    });
    $tokenBuildTimes[] = $result['time'];
}
$avgTokenBuildTime = array_sum($tokenBuildTimes) / count($tokenBuildTimes);
var_dump($avgTokenBuildTime < 100); // Should be less than 100ms

// Test block append performance
$token = new BiscuitBuilder();
$token = $token->build($kp);
$blockAppendTimes = [];
for ($i = 0; $i < 100; $i++) {
    $result = measureTime(function() use ($token, $i) {
        $blockBuilder = new BiscuitBlockBuilder();
        $blockBuilder->addFact("block{$i}(\"test\")");
        return $token->appendBlock($blockBuilder) instanceof BiscuitToken;
    });
    $blockAppendTimes[] = $result['time'];
}
$avgBlockAppendTime = array_sum($blockAppendTimes) / count($blockAppendTimes);
var_dump($avgBlockAppendTime < 100); // Should be less than 100ms

// Test authorization performance with increasing complexity
$authTimes = [];
for ($complexity = 1; $complexity <= 5; $complexity++) {
    $builder = new BiscuitBuilder();
    
    // Add facts and rules based on complexity
    for ($i = 0; $i < $complexity; $i++) {
        $builder->addFact("fact{$i}(\"test\")");
        $builder->addRule("rule{$i}(\$x) <- fact{$i}(\$x)");
    }
    
    $token = $builder->build($kp);
    
    // Add blocks based on complexity
    for ($i = 0; $i < $complexity; $i++) {
        $blockBuilder = new BiscuitBlockBuilder();
        $blockBuilder->addFact("block_fact{$i}(\"test\")");
        $blockBuilder->addRule("block_rule{$i}(\$x) <- block_fact{$i}(\$x)");
        $token = $token->appendBlock($blockBuilder);
    }
    
    $result = measureTime(function() use ($token, $complexity) {
        $authorizer = $token->authorizer();
        
        // Add policies based on complexity
        for ($i = 0; $i < $complexity; $i++) {
            $authorizer->addPolicy("allow if rule{$i}(\"test\")");
            $authorizer->addPolicy("allow if block_rule{$i}(\"test\")");
        }
        
        return $authorizer->authorize();
    });
    
    $authTimes[$complexity] = $result['time'];
    var_dump($result['time'] < 100 * $complexity); // Should scale roughly linearly
}

// Test serialization performance
$token = new BiscuitBuilder();
$token = $token->build($kp);
$serializationTimes = [];
for ($i = 0; $i < 100; $i++) {
    $result = measureTime(function() use ($token) {
        $serialized = $token->serialize();
        return BiscuitToken::deserialize($serialized) instanceof BiscuitToken;
    });
    $serializationTimes[] = $result['time'];
}
$avgSerializationTime = array_sum($serializationTimes) / count($serializationTimes);
var_dump($avgSerializationTime < 100); // Should be less than 100ms

// Memory usage test
$memoryStart = memory_get_usage();

// Create multiple tokens with blocks
$tokens = [];
for ($i = 0; $i < 100; $i++) {
    $builder = new BiscuitBuilder();
    $builder->addFact("test{$i}(\"value\")");
    $token = $builder->build($kp);
    
    for ($j = 0; $j < 3; $j++) {
        $blockBuilder = new BiscuitBlockBuilder();
        $blockBuilder->addFact("block{$j}(\"value\")");
        $token = $token->appendBlock($blockBuilder);
    }
    
    $tokens[] = $token;
}

$memoryEnd = memory_get_usage();
$memoryUsage = ($memoryEnd - $memoryStart) / 1024 / 1024; // Convert to MB
var_dump($memoryUsage < 10); // Should use less than 10MB

// Cleanup
unset($tokens);
?>
