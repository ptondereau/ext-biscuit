<?php
// Create a key pair for signing
$kp = new BiscuitKeyPair();
var_dump($kp instanceof BiscuitKeyPair);

// Create a token with initial facts and rules
$builder = new BiscuitBuilder();
var_dump($builder instanceof BiscuitBuilder);

// Set up a user with roles and permissions
$builder->addFact('user("1234")');
$builder->addFact('role("1234", "admin")');
$builder->addFact('role("1234", "user")');
$builder->addRule('user_role($user, $role) <- user($user), role($user, $role)');

$token = $builder->build($kp);
var_dump($token instanceof BiscuitToken);

// Add a block with resource permissions
$blockBuilder = new BiscuitBlockBuilder();
$blockBuilder->addFact('resource("file1.txt", "confidential")');
$blockBuilder->addFact('resource("file2.txt", "public")');
$blockBuilder->addRule('can_read($user, $resource) <- user_role($user, "user"), resource($resource, "public")');
$blockBuilder->addRule('can_read($user, $resource) <- user_role($user, "admin"), resource($resource, $_)');
$blockBuilder->addRule('can_write($user, $resource) <- user_role($user, "admin"), resource($resource, $_)');

$token = $token->appendBlock($blockBuilder);
var_dump($token instanceof BiscuitToken);

// Add a block with time-based restrictions
$blockBuilder = new BiscuitBlockBuilder();
$blockBuilder->addFact('time_restriction("business_hours", "09:00", "17:00")');
$blockBuilder->addRule('during_business_hours($current_time) <- time_restriction("business_hours", $start, $end), $current_time >= $start, $current_time <= $end');

$token = $token->appendBlock($blockBuilder);
var_dump($token instanceof BiscuitToken);

// Create an authorizer with complex policies
$authorizer = $token->authorizer();
var_dump($authorizer instanceof BiscuitAuthorizer);

// Add current time fact
$authorizer->addFact('current_time("14:30")');

// Test various authorization scenarios

// 1. Admin can read confidential files during business hours
$authorizer->addPolicy('allow if can_read($user, "file1.txt"), during_business_hours("14:30")');
var_dump($authorizer->authorize());

// 2. Regular user can read public files
$authorizer->addPolicy('allow if can_read($user, "file2.txt")');
var_dump($authorizer->authorize());

// 3. Admin can write to any file
$authorizer->addPolicy('allow if can_write($user, "file1.txt")');
var_dump($authorizer->authorize());

// 4. Test with after-hours time
$authorizer = $token->authorizer();
$authorizer->addFact('current_time("18:00")');
$authorizer->addPolicy('allow if can_read($user, "file1.txt"), during_business_hours("18:00")');
var_dump($authorizer->authorize());

// 5. Test complex policy combining multiple rules
$authorizer = $token->authorizer();
$authorizer->addFact('current_time("14:30")');
$authorizer->addPolicy('allow if can_read($user, $resource), during_business_hours("14:30"), user_role($user, "admin")');
var_dump($authorizer->authorize());

// 6. Test deny policy overriding allow
$authorizer->addPolicy('deny if resource($resource, "confidential"), user_role($user, "user")');
var_dump($authorizer->authorize());
?>
