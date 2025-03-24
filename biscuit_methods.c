#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// clang-format off
#include "php.h"
#include "zend_exceptions.h"
#include "biscuit_capi/biscuit_auth.h"
#include "php_biscuit.h"
// clang-format on

/* Constants */
#define BISCUIT_KEY_SIZE 32
#define DEFAULT_ALGORITHM Ed25519

/* Helper functions */
static void throw_biscuit_exception(const char *message) { zend_throw_exception(ce_BiscuitException, message, 0); }

static bool check_key_data_length(size_t data_len) {
    if (data_len != BISCUIT_KEY_SIZE) {
        throw_biscuit_exception("Invalid key data length");
        return false;
    }
    return true;
}

/* ========================= KeyPair methods ========================= */
PHP_METHOD(BiscuitKeyPair, __construct) {
    char *seed = NULL;
    size_t seed_len = 0;
    zend_long algorithm = DEFAULT_ALGORITHM;

    ZEND_PARSE_PARAMETERS_START(0, 2)
    Z_PARAM_OPTIONAL
    Z_PARAM_STRING(seed, seed_len)
    Z_PARAM_LONG(algorithm)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_keypair_object *intern = Z_BISCUIT_KEYPAIR_P(ZEND_THIS);
    intern->keypair = key_pair_new((uint8_t *)seed, seed_len, algorithm);

    if (!intern->keypair) {
        throw_biscuit_exception("Invalid key data length");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitKeyPair, getPublicKey) {
    biscuit_keypair_object *intern = Z_BISCUIT_KEYPAIR_P(ZEND_THIS);

    object_init_ex(return_value, ce_BiscuitPublicKey);
    biscuit_publickey_object *pubkey = Z_BISCUIT_PUBLICKEY_P(return_value);
    pubkey->publickey = key_pair_public(intern->keypair);
}

PHP_METHOD(BiscuitKeyPair, serialize) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_keypair_object *intern = Z_BISCUIT_KEYPAIR_P(ZEND_THIS);
    uint8_t buffer[BISCUIT_KEY_SIZE];
    uintptr_t written = key_pair_serialize(intern->keypair, buffer);

    RETURN_STRINGL(buffer, written);
}

PHP_METHOD(BiscuitKeyPair, deserialize) {
    char *data;
    size_t data_len;
    zend_long algorithm = DEFAULT_ALGORITHM;

    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_STRING(data, data_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(algorithm)
    ZEND_PARSE_PARAMETERS_END();

    if (!check_key_data_length(data_len)) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, ce_BiscuitKeyPair);
    biscuit_keypair_object *keypair = Z_BISCUIT_KEYPAIR_P(return_value);
    keypair->keypair = key_pair_deserialize((uint8_t *)data, algorithm);

    if (!keypair->keypair) {
        throw_biscuit_exception("Failed to deserialize key pair");
        RETURN_THROWS();
    }
}

/* ========================= PublicKey methods ========================= */
PHP_METHOD(BiscuitPublicKey, serialize) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_publickey_object *intern = Z_BISCUIT_PUBLICKEY_P(ZEND_THIS);
    uint8_t buffer[BISCUIT_KEY_SIZE];
    uintptr_t written = public_key_serialize(intern->publickey, buffer);

    RETURN_STRINGL(buffer, written);
}

PHP_METHOD(BiscuitPublicKey, deserialize) {
    char *data;
    size_t data_len;
    zend_long algorithm = DEFAULT_ALGORITHM;

    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_STRING(data, data_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(algorithm)
    ZEND_PARSE_PARAMETERS_END();

    if (!check_key_data_length(data_len)) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, ce_BiscuitPublicKey);
    biscuit_publickey_object *pubkey = Z_BISCUIT_PUBLICKEY_P(return_value);
    pubkey->publickey = public_key_deserialize((uint8_t *)data, algorithm);

    if (!pubkey->publickey) {
        throw_biscuit_exception("Failed to deserialize public key");
        RETURN_THROWS();
    }
}

/* ========================= BiscuitBuilder methods ========================= */
PHP_METHOD(BiscuitBuilder, __construct) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    intern->builder = biscuit_builder();

    if (!intern->builder) {
        throw_biscuit_exception("Failed to create builder");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitBuilder, setContext) {
    char *context;
    size_t context_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(context, context_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    RETURN_BOOL(biscuit_builder_set_context(intern->builder, context));
}

PHP_METHOD(BiscuitBuilder, addFact) {
    char *fact;
    size_t fact_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(fact, fact_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    RETURN_BOOL(biscuit_builder_add_fact(intern->builder, fact));
}

PHP_METHOD(BiscuitBuilder, addRule) {
    char *rule;
    size_t rule_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(rule, rule_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    RETURN_BOOL(biscuit_builder_add_rule(intern->builder, rule));
}

PHP_METHOD(BiscuitBuilder, addCheck) {
    char *check;
    size_t check_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(check, check_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    RETURN_BOOL(biscuit_builder_add_check(intern->builder, check));
}

PHP_METHOD(BiscuitBuilder, build) {
    zval *keypair;
    char *seed = NULL;
    size_t seed_len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_OBJECT_OF_CLASS(keypair, ce_BiscuitKeyPair)
    Z_PARAM_OPTIONAL
    Z_PARAM_STRING(seed, seed_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);
    biscuit_keypair_object *kp = Z_BISCUIT_KEYPAIR_P(keypair);

    object_init_ex(return_value, ce_BiscuitToken);
    biscuit_token_object *token = Z_BISCUIT_TOKEN_P(return_value);
    token->token = biscuit_builder_build(intern->builder, kp->keypair, (const uint8_t *)seed, seed_len);

    if (!token->token) {
        throw_biscuit_exception("Failed to build token");
        RETURN_THROWS();
    }
}

/* ========================= BiscuitToken methods ========================= */
PHP_METHOD(BiscuitToken, serialize) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);
    uint8_t *buffer = NULL;
    size_t written = biscuit_serialize(intern->token, buffer);

    if (!written) {
        throw_biscuit_exception("Failed to serialize token");
        RETURN_THROWS();
    }

    RETURN_STRINGL((char *)buffer, written);
}

PHP_METHOD(BiscuitAuthorizerBuilder, __construct) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    intern->authorizer_builder = authorizer_builder();
    if (!intern->authorizer_builder) {
        zend_throw_exception(ce_BiscuitException, "Failed to create authorizer builder", 0);
        RETURN_NULL();
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, addFact) {
    char *fact;
    size_t fact_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(fact, fact_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    bool result = authorizer_builder_add_fact(intern->authorizer_builder, fact);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    } else {
        RETURN_BOOL(false);
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, addRule) {
    char *rule;
    size_t rule_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(rule, rule_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    bool result = authorizer_builder_add_rule(intern->authorizer_builder, rule);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    } else {
        RETURN_BOOL(false);
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, addCheck) {
    char *check;
    size_t check_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(check, check_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    bool result = authorizer_builder_add_check(intern->authorizer_builder, check);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    } else {
        RETURN_BOOL(false);
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, addPolicy) {
    char *policy;
    size_t policy_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(policy, policy_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    bool result = authorizer_builder_add_policy(intern->authorizer_builder, policy);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    } else {
        RETURN_BOOL(false);
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, build) {
    zval *token = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_OBJECT_OF_CLASS(token, ce_BiscuitToken)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);
    biscuit_token_object *token_obj = Z_BISCUIT_TOKEN_P(token);

    object_init_ex(return_value, ce_BiscuitAuthorizer);
    biscuit_authorizer_object *auth = Z_BISCUIT_AUTHORIZER_P(return_value);

    auth->authorizer = authorizer_builder_build(intern->authorizer_builder, token_obj->token);
    if (!auth->authorizer) {
        zend_throw_exception(ce_BiscuitException, "Failed to build authorizer", 0);
        RETURN_NULL();
    }
}

PHP_METHOD(BiscuitAuthorizerBuilder, buildUnauthenticated) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_authorizer_builder_object *intern = Z_BISCUIT_AUTHORIZER_BUILDER_P(ZEND_THIS);

    object_init_ex(return_value, ce_BiscuitAuthorizer);
    biscuit_authorizer_object *auth = Z_BISCUIT_AUTHORIZER_P(return_value);

    auth->authorizer = authorizer_builder_build_unauthenticated(intern->authorizer_builder);
    if (!auth->authorizer) {
        zend_throw_exception(ce_BiscuitException, "Failed to build unauthenticated authorizer", 0);
        RETURN_NULL();
    }
}

PHP_METHOD(BiscuitAuthorizer, authorize) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_authorizer_object *intern = Z_BISCUIT_AUTHORIZER_P(ZEND_THIS);

    if (!intern->authorizer) {
        throw_biscuit_exception("Invalid authorizer");
        RETURN_THROWS();
    }

    bool result = authorizer_authorize(intern->authorizer);
    RETURN_BOOL(result);
}

PHP_METHOD(BiscuitAuthorizer, print) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_authorizer_object *intern = Z_BISCUIT_AUTHORIZER_P(ZEND_THIS);

    if (!intern->authorizer) {
        throw_biscuit_exception("Invalid authorizer");
        RETURN_THROWS();
    }

    char *output = authorizer_print(intern->authorizer);
    if (output) {
        RETVAL_STRING(output);
        free(output);
    } else {
        RETURN_EMPTY_STRING();
    }
}

/* ========================= BiscuitBlockBuilder methods ========================= */
PHP_METHOD(BiscuitBlockBuilder, __construct) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_block_builder_object *intern = Z_BISCUIT_BLOCK_BUILDER_P(ZEND_THIS);
    intern->block_builder = create_block();

    if (!intern->block_builder) {
        throw_biscuit_exception("Failed to create block builder");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitBlockBuilder, setContext) {
    char *context;
    size_t context_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(context, context_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_block_builder_object *intern = Z_BISCUIT_BLOCK_BUILDER_P(ZEND_THIS);

    bool result = block_builder_set_context(intern->block_builder, context);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    }
    RETURN_BOOL(false);
}

PHP_METHOD(BiscuitBlockBuilder, addFact) {
    char *fact;
    size_t fact_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(fact, fact_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_block_builder_object *intern = Z_BISCUIT_BLOCK_BUILDER_P(ZEND_THIS);

    bool result = block_builder_add_fact(intern->block_builder, fact);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    }
    RETURN_BOOL(false);
}

PHP_METHOD(BiscuitBlockBuilder, addRule) {
    char *rule;
    size_t rule_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(rule, rule_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_block_builder_object *intern = Z_BISCUIT_BLOCK_BUILDER_P(ZEND_THIS);

    bool result = block_builder_add_rule(intern->block_builder, rule);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    }
    RETURN_BOOL(false);
}

PHP_METHOD(BiscuitBlockBuilder, addCheck) {
    char *check;
    size_t check_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(check, check_len)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_block_builder_object *intern = Z_BISCUIT_BLOCK_BUILDER_P(ZEND_THIS);

    bool result = block_builder_add_check(intern->block_builder, check);
    if (result) {
        RETURN_ZVAL(getThis(), 1, 0);
    }
    RETURN_BOOL(false);
}

PHP_METHOD(BiscuitToken, fromSealed) {
    char *data;
    size_t data_len;
    zval *root;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(data, data_len)
    Z_PARAM_OBJECT_OF_CLASS(root, ce_BiscuitPublicKey)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_publickey_object *root_key = Z_BISCUIT_PUBLICKEY_P(root);

    object_init_ex(return_value, ce_BiscuitToken);
    biscuit_token_object *token = Z_BISCUIT_TOKEN_P(return_value);

    token->token = biscuit_from((const uint8_t *)data, data_len, root_key->publickey);

    if (!token->token) {
        throw_biscuit_exception("Failed to deserialize sealed token");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitToken, appendBlock) {
    zval *builder;
    zval *keypair;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_OBJECT_OF_CLASS(builder, ce_BiscuitBlockBuilder)
    Z_PARAM_OBJECT_OF_CLASS(keypair, ce_BiscuitKeyPair)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);
    biscuit_block_builder_object *block_builder = Z_BISCUIT_BLOCK_BUILDER_P(builder);
    biscuit_keypair_object *kp = Z_BISCUIT_KEYPAIR_P(keypair);

    object_init_ex(return_value, ce_BiscuitToken);
    biscuit_token_object *new_token = Z_BISCUIT_TOKEN_P(return_value);

    new_token->token = biscuit_append_block(intern->token, block_builder->block_builder, kp->keypair);

    if (!new_token->token) {
        throw_biscuit_exception("Failed to append block to token");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitToken, createAuthorizer) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    object_init_ex(return_value, ce_BiscuitAuthorizer);
    biscuit_authorizer_object *authorizer = Z_BISCUIT_AUTHORIZER_P(return_value);

    authorizer->authorizer = biscuit_authorizer(intern->token);

    if (!authorizer->authorizer) {
        throw_biscuit_exception("Failed to create authorizer from token");
        RETURN_THROWS();
    }
}

PHP_METHOD(BiscuitToken, serializeSealed) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    uintptr_t buffer_size = biscuit_sealed_size(intern->token);
    if (!buffer_size) {
        throw_biscuit_exception("Failed to determine serialized size");
        RETURN_THROWS();
    }

    uint8_t *buffer = emalloc(buffer_size);
    if (!buffer) {
        throw_biscuit_exception("Memory allocation failed");
        RETURN_THROWS();
    }

    uintptr_t written = biscuit_serialize_sealed(intern->token, buffer);

    if (!written) {
        efree(buffer);
        throw_biscuit_exception("Failed to serialize sealed token");
        RETURN_THROWS();
    }

    RETVAL_STRINGL((char *)buffer, written);
    efree(buffer);
}

PHP_METHOD(BiscuitToken, blockCount) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    uintptr_t count = biscuit_block_count(intern->token);

    RETURN_LONG((zend_long)count);
}

PHP_METHOD(BiscuitToken, blockContext) {
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    if (index < 0) {
        throw_biscuit_exception("Block index cannot be negative");
        RETURN_THROWS();
    }

    char *context = biscuit_block_context(intern->token, index);

    if (!context) {
        throw_biscuit_exception("Failed to get block context or invalid block index");
        RETURN_THROWS();
    }

    RETVAL_STRING(context);
    string_free(context);
}

PHP_METHOD(BiscuitToken, print) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    const char *output = biscuit_print(intern->token);

    if (!output) {
        throw_biscuit_exception("Failed to print token");
        RETURN_THROWS();
    }

    RETURN_STRING(output);
}

PHP_METHOD(BiscuitToken, printBlockSource) {
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    biscuit_token_object *intern = Z_BISCUIT_TOKEN_P(ZEND_THIS);

    if (!intern->token) {
        throw_biscuit_exception("Invalid token");
        RETURN_THROWS();
    }

    if (index < 0) {
        throw_biscuit_exception("Block index cannot be negative");
        RETURN_THROWS();
    }

    const char *source = biscuit_print_block_source(intern->token, index);

    if (!source) {
        throw_biscuit_exception("Failed to get block source or invalid block index");
        RETURN_THROWS();
    }

    RETURN_STRING(source);
}

PHP_METHOD(BiscuitBuilder, setRootKeyId) {
    zend_long id;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(id)
    ZEND_PARSE_PARAMETERS_END();

    if (id < 0) {
        throw_biscuit_exception("Root key ID cannot be negative");
        RETURN_THROWS();
    }

    biscuit_builder_object *intern = Z_BISCUIT_BUILDER_P(ZEND_THIS);

    bool result = biscuit_builder_set_root_key_id(intern->builder, id);
    RETURN_BOOL(result);
}

PHP_METHOD(BiscuitKeyPair, public) {
    ZEND_PARSE_PARAMETERS_NONE();

    biscuit_keypair_object *intern = Z_BISCUIT_KEYPAIR_P(ZEND_THIS);

    if (!intern->keypair) {
        throw_biscuit_exception("Invalid key pair");
        RETURN_THROWS();
    }

    object_init_ex(return_value, ce_BiscuitPublicKey);
    biscuit_publickey_object *pubkey = Z_BISCUIT_PUBLICKEY_P(return_value);
    pubkey->publickey = key_pair_public(intern->keypair);

    if (!pubkey->publickey) {
        throw_biscuit_exception("Failed to get public key");
        RETURN_THROWS();
    }
}