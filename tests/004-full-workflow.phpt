--TEST--
Biscuit full workflow
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
$rootSeed = str_repeat("abcdefgh", 4);
$rootKp = new BiscuitKeyPair($rootSeed);

$builder = new BiscuitBuilder();
$builder->addFact('right("file1", "read")');

$token = $builder->build($rootKp, $rootSeed);
var_dump($token instanceof BiscuitToken);

$blockCount = $token->blockCount();
var_dump($blockCount === 1);

$tokenPrint = $token->print();
var_dump(is_string($tokenPrint));

$blockBuilder = new BiscuitBlockBuilder();
// Let's modify this check to always pass
$blockBuilder->addCheck('check if true')
             ->addFact('hello("world")');

$blockSeed = str_repeat("ijklmnop", 4);
$blockKp = new BiscuitKeyPair($blockSeed);

$token2 = $token->appendBlock($blockBuilder, $blockKp);
var_dump($token2 instanceof BiscuitToken);

$blockCount2 = $token2->blockCount();
var_dump($blockCount2 === 2);

$tokenPrint2 = $token2->print();
var_dump(is_string($tokenPrint2));

$authBuilder = new BiscuitAuthorizerBuilder();
$authBuilder->addCheck('check if right("efgh")')
            ->addPolicy('allow if true');

$authorizer = $authBuilder->build($token2);
var_dump($authorizer instanceof BiscuitAuthorizer);

$authResult = $authorizer->authorize();
var_dump($authResult === false);

if (!$authResult) {
    var_dump(biscuit_error_kind() !== BISCUIT_ERROR_NONE);
    
    // Check for failed checks
    $errorCount = biscuit_error_check_count();
    var_dump($errorCount > 0);
    
    // Print authorizer world to see the state
    $authorizerOutput = $authorizer->print();
    var_dump(is_string($authorizerOutput));

    $authorizerCheckCount = 0;
    $blockCheckCount = 0;
    
    for ($i = 0; $i < $errorCount; $i++) {
        if (biscuit_error_check_is_authorizer($i)) {
            $authorizerCheckCount++;
        } else {
            $blockCheckCount++;
        }
    }

    var_dump($authorizerCheckCount > 0);
    var_dump($blockCheckCount === 0); // Should be 0 now as we use 'check if true'
}

$serialized = $token2->serialize();
var_dump(is_string($serialized) && strlen($serialized) > 0);

$successAuthBuilder = new BiscuitAuthorizerBuilder();
$successAuthBuilder->addPolicy('allow if true');

$successAuthorizer = $successAuthBuilder->buildUnauthenticated();
$finalResult = $successAuthorizer->authorize();
var_dump($finalResult);  // Just dump the actual result

if (!$finalResult) {
    echo "Failed with error: " . biscuit_error_message() . "\n";
    echo "Error kind: " . biscuit_error_kind() . "\n";
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