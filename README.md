# PHP Biscuit Extension

This extension provides PHP bindings for the [Biscuit](https://github.com/biscuit-auth/biscuit) authorization library. Biscuit is a bearer token format with decentralized verification and offline attenuation.

## Requirements

- PHP 8.1.0 or later (up to PHP 8.4)
- Biscuit library installed on your system (libbiscuit_auth.so.6.0.0)
- A C compiler and build tools

## Installation

1. Ensure the Biscuit library is installed:
   - Library should be in `/usr/lib/libbiscuit_auth.so.6.0.0`
   - Headers should be in `/usr/include/biscuit_capi/biscuit_auth.h`

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
// Create a new key pair
$kp = new BiscuitKeyPair();

// Or create with a specific seed
$seed = random_bytes(32);
$kp = new BiscuitKeyPair($seed);

// Get the public key
$publicKey = $kp->public();
```

### Building a Token

```php
// Create a builder
$builder = new BiscuitBuilder();

// Add facts and rules
$builder->addFact('user("1234")');
$builder->addFact('right("read")');
$builder->addRule('allow($user, $right) <- user($user), right($right)');

// Build the token
$token = $builder->build($kp);
```

### Adding Blocks

```php
// Create a block builder
$blockBuilder = new BiscuitBlockBuilder();

// Add facts and rules to the block
$blockBuilder->addFact('resource("file1.txt")');
$blockBuilder->addRule('can_access($user, $resource) <- user($user), resource($resource)');

// Append the block to the token
$newToken = $token->appendBlock($blockBuilder);
```

### Authorization

```php
// Create an authorizer
$authorizer = $token->authorizer();

// Add facts and rules for authorization
$authorizer->addFact('current_time("14:30")');
$authorizer->addRule('during_business_hours($time) <- $time >= "09:00", $time <= "17:00"');

// Add policies
$authorizer->addPolicy('allow if can_access($user, $resource), during_business_hours($time)');

// Check authorization
if ($authorizer->authorize()) {
    echo "Access granted\n";
} else {
    echo "Access denied\n";
}
```

### Serialization

```php
// Serialize a key pair
$serializedKp = $kp->serialize();
$deserializedKp = BiscuitKeyPair::deserialize($serializedKp);

// Serialize a public key
$serializedPk = $publicKey->serialize();
$deserializedPk = BiscuitPublicKey::deserialize($serializedPk);

// Serialize a token
$serializedToken = $token->serialize();
$deserializedToken = BiscuitToken::deserialize($serializedToken);
```

## Classes and Methods

### BiscuitKeyPair
- `__construct(?string $seed = null, int $algorithm = Ed25519)`
- `public(): BiscuitPublicKey`
- `serialize(): string`
- `deserialize(string $data, int $algorithm = Ed25519): BiscuitKeyPair`

### BiscuitPublicKey
- `serialize(): string`
- `deserialize(string $data, int $algorithm = Ed25519): BiscuitPublicKey`

### BiscuitBuilder
- `__construct()`
- `setContext(string $context): bool`
- `addFact(string $fact): bool`
- `addRule(string $rule): bool`
- `addCheck(string $check): bool`
- `build(BiscuitKeyPair $kp, ?string $seed = null): BiscuitToken`

### BiscuitToken
- `serialize(): string`
- `deserialize(string $data): BiscuitToken`
- `appendBlock(BiscuitBlockBuilder $builder): BiscuitToken`
- `authorizer(): BiscuitAuthorizer`

### BiscuitBlockBuilder
- `__construct()`
- `addFact(string $fact): bool`
- `addRule(string $rule): bool`
- `addCheck(string $check): bool`

### BiscuitAuthorizer
- `addFact(string $fact): bool`
- `addRule(string $rule): bool`
- `addPolicy(string $policy): bool`
- `authorize(): bool`

### BiscuitAuthorizerBuilder
- `__construct()`
- `addFact(string $fact): bool`
- `addRule(string $rule): bool`
- `addPolicy(string $policy): bool`
- `build(BiscuitToken $token): BiscuitAuthorizer`

## Error Handling

The extension provides global functions for error handling:

- `biscuit_error_message(): string` - Get the last error message
- `biscuit_error_kind(): int` - Get the last error kind
- `biscuit_error_check_count(): int` - Get the number of failed checks

## Constants

- `Ed25519` - Algorithm constant for Ed25519 signatures

## Testing

Run the test suite:
```bash
make test
```

## License

This extension is released under the MIT License.
