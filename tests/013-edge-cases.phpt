--TEST--
Biscuit edge cases test
--SKIPIF--
<?php
if (!extension_loaded('biscuit')) die('skip');
?>
--FILE--
<?php
// Test empty seed
$kp = new BiscuitKeyPair("");
var_dump($kp instanceof BiscuitKeyPair);

// Test very large seed
$largeSeed = str_repeat("A", 1024);
try {
    $kp = new BiscuitKeyPair($largeSeed);
    var_dump(false);
} catch (Exception $e) {
    var_dump(true);
}

// Test empty context
$builder = new BiscuitBuilder();
var_dump($builder->setContext("") === true);

// Test invalid JSON context
var_dump($builder->setContext("{invalid json}") === false);

// Test empty fact
var_dump($builder->addFact("") === false);

// Test empty rule
var_dump($builder->addRule("") === false);

// Test empty check
var_dump($builder->addCheck("") === false);

// Test token with no facts or rules
$kp = new BiscuitKeyPair();
$builder = new BiscuitBuilder();
$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

// Test authorizer with no policies
$authorizer = $token->authorizer();
var_dump($authorizer->authorize() === false);

// Test block builder with no content
$blockBuilder = new BiscuitBlockBuilder();
$newToken = $token->appendBlock($blockBuilder);
var_dump($newToken instanceof BiscuitToken);

// Test maximum fact length
$longFact = 'test("' . str_repeat("A", 1024) . '")';
var_dump($builder->addFact($longFact) === false);

// Test maximum rule length
$longRule = 'test("x") <- test("' . str_repeat("A", 1024) . '")';
var_dump($builder->addRule($longRule) === false);

// Test nested rules
$builder = new BiscuitBuilder();
$builder->addFact('level0("test")');
$builder->addRule('level1($x) <- level0($x)');
$builder->addRule('level2($x) <- level1($x)');
$builder->addRule('level3($x) <- level2($x)');
$token = $builder->build($kp);
$authorizer = $token->authorizer();
$authorizer->addPolicy('allow if level3("test")');
var_dump($authorizer->authorize() === true);

// Test circular rules
$builder = new BiscuitBuilder();
$builder->addRule('a($x) <- b($x)');
$builder->addRule('b($x) <- a($x)');
$token = $builder->build($kp);
$authorizer = $token->authorizer();
$authorizer->addFact('a("test")');
$authorizer->addPolicy('allow if b("test")');
var_dump($authorizer->authorize() === true);

// Test multiple blocks with same facts
$builder = new BiscuitBuilder();
$builder->addFact('test("value")');
$token = $builder->build($kp);

$blockBuilder = new BiscuitBlockBuilder();
$blockBuilder->addFact('test("value")');
$token = $token->appendBlock($blockBuilder);

$authorizer = $token->authorizer();
$authorizer->addPolicy('allow if test("value")');
var_dump($authorizer->authorize() === true);

// Test null byte in strings
try {
    $builder->addFact("test(\"\0\")");
    var_dump(false);
} catch (Exception $e) {
    var_dump(true);
}

// Test Unicode characters
$builder = new BiscuitBuilder();
$builder->addFact('test("🔒")');
$token = $builder->build($kp);
$authorizer = $token->authorizer();
$authorizer->addPolicy('allow if test("🔒")');
var_dump($authorizer->authorize() === true);

// Test multiple policies with same name
$authorizer = $token->authorizer();
$authorizer->addPolicy('allow if true');
$authorizer->addPolicy('allow if true');
var_dump($authorizer->authorize() === true);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(false)
bool(false)
bool(false)
bool(false)
bool(true)
bool(false)
bool(true)
bool(false)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true) 