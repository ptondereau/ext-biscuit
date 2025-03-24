<?php

/** @generate-function-entries */

/**
 * Biscuit PHP Extension
 */

/**
 * Error kind constants
 */
/** @var int */
const BISCUIT_ERROR_NONE = 0;
/** @var int */
const BISCUIT_ERROR_INVALID_ARGUMENT = 1;
/** @var int */
const BISCUIT_ERROR_INTERNAL_ERROR = 2;
/** @var int */
const BISCUIT_ERROR_FORMAT_SIGNATURE_INVALID_FORMAT = 3;
/** @var int */
const BISCUIT_ERROR_FORMAT_SIGNATURE_INVALID_SIGNATURE = 4;
/** @var int */
const BISCUIT_ERROR_FORMAT_SEALED_SIGNATURE = 5;
/** @var int */
const BISCUIT_ERROR_FORMAT_EMPTY_KEYS = 6;
/** @var int */
const BISCUIT_ERROR_FORMAT_UNKNOWN_PUBLIC_KEY = 7;
/** @var int */
const BISCUIT_ERROR_FORMAT_DESERIALIZATION_ERROR = 8;
/** @var int */
const BISCUIT_ERROR_FORMAT_SERIALIZATION_ERROR = 9;
/** @var int */
const BISCUIT_ERROR_FORMAT_BLOCK_DESERIALIZATION_ERROR = 10;
/** @var int */
const BISCUIT_ERROR_FORMAT_BLOCK_SERIALIZATION_ERROR = 11;
/** @var int */
const BISCUIT_ERROR_FORMAT_VERSION = 12;
/** @var int */
const BISCUIT_ERROR_FORMAT_INVALID_BLOCK_ID = 13;
/** @var int */
const BISCUIT_ERROR_FORMAT_EXISTING_PUBLIC_KEY = 14;
/** @var int */
const BISCUIT_ERROR_FORMAT_SYMBOL_TABLE_OVERLAP = 15;
/** @var int */
const BISCUIT_ERROR_FORMAT_PUBLIC_KEY_TABLE_OVERLAP = 16;
/** @var int */
const BISCUIT_ERROR_FORMAT_UNKNOWN_EXTERNAL_KEY = 17;
/** @var int */
const BISCUIT_ERROR_FORMAT_UNKNOWN_SYMBOL = 18;
/** @var int */
const BISCUIT_ERROR_APPEND_ON_SEALED = 19;
/** @var int */
const BISCUIT_ERROR_LOGIC_INVALID_BLOCK_RULE = 20;
/** @var int */
const BISCUIT_ERROR_LOGIC_UNAUTHORIZED = 21;
/** @var int */
const BISCUIT_ERROR_LOGIC_AUTHORIZER_NOT_EMPTY = 22;
/** @var int */
const BISCUIT_ERROR_LOGIC_NO_MATCHING_POLICY = 23;
/** @var int */
const BISCUIT_ERROR_LANGUAGE_ERROR = 24;
/** @var int */
const BISCUIT_ERROR_TOO_MANY_FACTS = 25;
/** @var int */
const BISCUIT_ERROR_TOO_MANY_ITERATIONS = 26;
/** @var int */
const BISCUIT_ERROR_TIMEOUT = 27;
/** @var int */
const BISCUIT_ERROR_CONVERSION_ERROR = 28;

/**
 * Signature algorithm constants
 */
 /** @var int */
const BISCUIT_ALGORITHM_ED25519 = 0;
/** @var int */
const BISCUIT_ALGORITHM_SECP256R1 = 1;

/**
 * Biscuit KeyPair class
 */
class BiscuitKeyPair {
    public function __construct(
        string $seed = "",
        int $algorithm = BISCUIT_ALGORITHM_ED25519
    ) {}
    public function public(): BiscuitPublicKey {}
    public function serialize(): string {}
    public static function deserialize(
        string $data,
        int $algorithm = BISCUIT_ALGORITHM_ED25519
    ): BiscuitKeyPair {}
}

/**
 * Biscuit PublicKey class
 */
class BiscuitPublicKey {
    public function serialize(): string {}
    public static function deserialize(
        string $data,
        int $algorithm = BISCUIT_ALGORITHM_ED25519
    ): BiscuitPublicKey {}
}

/**
 * Biscuit Builder class
 */
class BiscuitBuilder {
    public function __construct() {}
    public function setContext(string $context): BiscuitBuilder {}
    public function setRootKeyId(int $id): BiscuitBuilder {}
    public function addFact(string $fact): BiscuitBuilder {}
    public function addRule(string $rule): BiscuitBuilder {}
    public function addCheck(string $check): BiscuitBuilder {}
    public function build(
        BiscuitKeyPair $keypair,
        string $seed
    ): BiscuitToken {}
}

/**
 * Biscuit Token class
 */
class BiscuitToken {
    public static function fromSealed(
        string $data,
        BiscuitPublicKey $root
    ): BiscuitToken {}
    public function appendBlock(
        BiscuitBlockBuilder $builder,
        BiscuitKeyPair $keypair
    ): BiscuitToken {}
    public function createAuthorizer(): BiscuitAuthorizer {}
    public function serialize(): string {}
    public function serializeSealed(): string {}
    public function blockCount(): int {}
    public function blockContext(int $index): string {}
    public function print(): string {}
    public function printBlockSource(int $index): string {}
}

/**
 * Biscuit Block Builder class
 */
class BiscuitBlockBuilder {
    public function __construct() {}
    public function setContext(string $context): BiscuitBlockBuilder {}
    public function addFact(string $fact): BiscuitBlockBuilder {}
    public function addRule(string $rule): BiscuitBlockBuilder {}
    public function addCheck(string $check): BiscuitBlockBuilder {}
}

/**
 * Biscuit Authorizer Builder class
 */
class BiscuitAuthorizerBuilder {
    public function __construct() {}
    public function addFact(string $fact): BiscuitAuthorizerBuilder {}
    public function addRule(string $rule): BiscuitAuthorizerBuilder {}
    public function addCheck(string $check): BiscuitAuthorizerBuilder {}
    public function addPolicy(string $policy): BiscuitAuthorizerBuilder {}
    public function build(BiscuitToken $token): BiscuitAuthorizer {}
    public function buildUnauthenticated(): BiscuitAuthorizer {}
}

/**
 * Biscuit Authorizer class
 */
class BiscuitAuthorizer {
    public function authorize(): bool {}
    public function print(): string {}
}

/**
 * Error handling functions
 */
function biscuit_error_message(): string {}
function biscuit_error_kind(): int {}
function biscuit_error_check_count(): int {}
function biscuit_error_check_id(int $check_index): int {}
function biscuit_error_check_block_id(int $check_index): int {}
function biscuit_error_check_rule(int $check_index): string {}
function biscuit_error_check_is_authorizer(int $check_index): bool {}
