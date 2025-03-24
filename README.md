> [!WARNING]  
> The PHP extension is still ine BETA and maybe not suitable for production for now

# PHP Biscuit Extension

This extension provides PHP bindings for the [Biscuit](https://github.com/biscuit-auth/biscuit) authorization library. Biscuit is a bearer token format with decentralized verification and offline attenuation.

## Requirements

- PHP 8.1.0 or later (up to PHP 8.4)
- Biscuit library installed on your system (libbiscuit_auth.so) if you want to build it from sources

> [!IMPORTANT]  
> We doesn't support Windows build for the moment

## Installation

1. Ensure the Biscuit library is installed:

If not, you can download the library with your corresponding OS and architecture here: https://github.com/eclipse-biscuit/biscuit-rust/releases

2. Build and install the extension:
```bash
phpize
./configure --with-biscuit
make
sudo make install
```

3. Add the extension to your php.ini:
```ini
extension=biscuit.so
```

## Usage

### Creating a Key Pair

```php
$seed = random_bytes(32); // or any string
$kp = new BiscuitKeyPair($seed, BISCUIT_ALGORITHM_ED25519);

// Get the public key
$publicKey = $kp->getPublicKey();
```

### Building a Token

```php
// Create a builder
$builder = new BiscuitBuilder();

// Set context (optional)
$builder->setContext('app_v1');

// Add facts and rules
$builder->addFact('user("1234")');
$builder->addFact('right("read")');
$builder->addRule('allow($user, $right) <- user($user), right($right)');

// Add a check (optional)
$builder->addCheck('check if user($id), $id == "1234"');

// Build the token (with optional random seed)
$seed = random_bytes(32);
$token = $builder->build($kp, $seed);
```

### Adding Blocks

```php
// Create a block builder
$blockBuilder = new BiscuitBlockBuilder();

// Set context (optional)
$blockBuilder->setContext('block_v1');

// Add facts and rules to the block
$blockBuilder->addFact('resource("file1.txt")');
$blockBuilder->addRule('can_access($user, $resource) <- user($user), resource($resource)');

// Append the block to the token
$newToken = $token->appendBlock($blockBuilder, $kp);
```

### Authorization

```php
// Create an authorizer
$authorizer = $token->createAuthorizer();

// Alternatively, use the builder pattern
$authBuilder = new BiscuitAuthorizerBuilder();
$authBuilder->addFact('current_time("14:30")')
    ->addRule('during_business_hours($time) <- $time >= "09:00", $time <= "17:00"')
    ->addPolicy('allow if can_access($user, $resource), during_business_hours($time)');
$authorizer = $authBuilder->build($token);

// Check authorization
if ($authorizer->authorize()) {
    echo "Access granted\n";
} else {
    echo "Access denied: " . biscuit_error_message() . "\n";
}
```

### Serialization

```php
// Serialize a key pair
$serializedKp = $kp->serialize();
$deserializedKp = BiscuitKeyPair::deserialize($serializedKp, BISCUIT_ALGORITHM_ED25519);

// Serialize a public key
$serializedPk = $publicKey->serialize();
$deserializedPk = BiscuitPublicKey::deserialize($serializedPk, BISCUIT_ALGORITHM_ED25519);

// Serialize a token
$serializedToken = $token->serialize();

// Serialize a token in sealed mode
$sealedToken = $token->serializeSealed();
$deserializedToken = BiscuitToken::fromSealed($sealedToken, $publicKey);
```

### Inspection and Debugging

```php
// Print token information
echo $token->print();

// Get block source
echo $token->printBlockSource(0); // Print the first block

// Get block count
$blockCount = $token->blockCount();

// Get block context
$context = $token->blockContext(1); // Get context of the second block

// Print authorizer state
echo $authorizer->print();
```

## Testing

Run the test suite:
```bash
make test
```

## License

This extension is released under the MIT License.
