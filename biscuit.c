/* ext_biscuit extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// clang-format off
#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "biscuit_capi/biscuit_auth.h"

#include "biscuit_arginfo.h"
#include "php_biscuit.h"
// clang-format on

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

/* Initialize object handlers */
zend_object_handlers biscuit_keypair_object_handlers;
zend_object_handlers biscuit_publickey_object_handlers;
zend_object_handlers biscuit_token_object_handlers;
zend_object_handlers biscuit_builder_object_handlers;
zend_object_handlers biscuit_block_builder_object_handlers;
zend_object_handlers biscuit_authorizer_object_handlers;
zend_object_handlers biscuit_authorizer_builder_object_handlers;

/* Initialize class entries */
zend_class_entry *ce_BiscuitKeyPair;
zend_class_entry *ce_BiscuitPublicKey;
zend_class_entry *ce_BiscuitToken;
zend_class_entry *ce_BiscuitBuilder;
zend_class_entry *ce_BiscuitBlockBuilder;
zend_class_entry *ce_BiscuitAuthorizer;
zend_class_entry *ce_BiscuitAuthorizerBuilder;
zend_class_entry *ce_BiscuitException;

/* Object creation/free functions */
zend_object *php_biscuit_keypair_create_object(zend_class_entry *ce) {
    biscuit_keypair_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_keypair_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_keypair_object_handlers;

    return &intern->std;
}

void php_biscuit_keypair_free_obj(zend_object *obj) {
    biscuit_keypair_object *intern = php_biscuit_keypair_from_obj(obj);
    if (intern->keypair) {
        key_pair_free(intern->keypair);
        intern->keypair = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_publickey_create_object(zend_class_entry *ce) {
    biscuit_publickey_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_publickey_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_publickey_object_handlers;

    return &intern->std;
}

void php_biscuit_publickey_free_obj(zend_object *obj) {
    biscuit_publickey_object *intern = php_biscuit_publickey_from_obj(obj);
    if (intern->publickey) {
        public_key_free(intern->publickey);
        intern->publickey = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_token_create_object(zend_class_entry *ce) {
    biscuit_token_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_token_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_token_object_handlers;

    return &intern->std;
}

void php_biscuit_token_free_obj(zend_object *obj) {
    biscuit_token_object *intern = php_biscuit_token_from_obj(obj);
    if (intern->token) {
        biscuit_free(intern->token);
        intern->token = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_builder_create_object(zend_class_entry *ce) {
    biscuit_builder_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_builder_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_builder_object_handlers;

    return &intern->std;
}

void php_biscuit_builder_free_obj(zend_object *obj) {
    biscuit_builder_object *intern = php_biscuit_builder_from_obj(obj);
    if (intern->builder) {
        biscuit_builder_free(intern->builder);
        intern->builder = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_block_builder_create_object(zend_class_entry *ce) {
    biscuit_block_builder_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_block_builder_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_block_builder_object_handlers;

    return &intern->std;
}

void php_biscuit_block_builder_free_obj(zend_object *obj) {
    biscuit_block_builder_object *intern = php_biscuit_block_builder_from_obj(obj);
    if (intern->block_builder) {
        block_builder_free(intern->block_builder);
        intern->block_builder = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_authorizer_create_object(zend_class_entry *ce) {
    biscuit_authorizer_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_authorizer_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_authorizer_object_handlers;

    return &intern->std;
}

void php_biscuit_authorizer_free_obj(zend_object *obj) {
    biscuit_authorizer_object *intern = php_biscuit_authorizer_from_obj(obj);
    if (intern->authorizer) {
        authorizer_free(intern->authorizer);
        intern->authorizer = NULL;
    }
    zend_object_std_dtor(obj);
}

zend_object *php_biscuit_authorizer_builder_create_object(zend_class_entry *ce) {
    biscuit_authorizer_builder_object *intern;
    intern = zend_object_alloc(sizeof(biscuit_authorizer_builder_object), ce);
    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);
    intern->std.handlers = &biscuit_authorizer_builder_object_handlers;

    return &intern->std;
}

void php_biscuit_authorizer_builder_free_obj(zend_object *obj) {
    biscuit_authorizer_builder_object *intern = php_biscuit_authorizer_builder_from_obj(obj);
    if (intern->authorizer_builder) {
        authorizer_builder_free(intern->authorizer_builder);
        intern->authorizer_builder = NULL;
    }
    zend_object_std_dtor(obj);
}

/* Error handling functions */
PHP_FUNCTION(biscuit_error_message) {
    ZEND_PARSE_PARAMETERS_NONE();
    const char *message = error_message();
    RETURN_STRING(message);
}

PHP_FUNCTION(biscuit_error_kind) {
    ZEND_PARSE_PARAMETERS_NONE();
    ErrorKind kind = error_kind();
    RETURN_LONG(kind);
}

PHP_FUNCTION(biscuit_error_check_count) {
    ZEND_PARSE_PARAMETERS_NONE();
    uint64_t count = error_check_count();
    RETURN_LONG(count);
}

PHP_FUNCTION(biscuit_error_check_id) {
    zend_long check_index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(check_index)
    ZEND_PARSE_PARAMETERS_END();

    uint64_t id = error_check_id(check_index);
    RETURN_LONG(id);
}

PHP_FUNCTION(biscuit_error_check_block_id) {
    zend_long check_index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(check_index)
    ZEND_PARSE_PARAMETERS_END();

    uint64_t block_id = error_check_block_id(check_index);
    RETURN_LONG(block_id);
}

PHP_FUNCTION(biscuit_error_check_rule) {
    zend_long check_index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(check_index)
    ZEND_PARSE_PARAMETERS_END();

    const char *rule = error_check_rule(check_index);
    RETURN_STRING(rule);
}

PHP_FUNCTION(biscuit_error_check_is_authorizer) {
    zend_long check_index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(check_index)
    ZEND_PARSE_PARAMETERS_END();

    bool is_authorizer = error_check_is_authorizer(check_index);
    RETURN_BOOL(is_authorizer);
}

/* Module initialization */
PHP_MINIT_FUNCTION(biscuit) {
    zend_class_entry ce;

    memcpy(&biscuit_keypair_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_keypair_object_handlers.offset = XtOffsetOf(biscuit_keypair_object, std);
    biscuit_keypair_object_handlers.free_obj = php_biscuit_keypair_free_obj;

    memcpy(&biscuit_publickey_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_publickey_object_handlers.offset = XtOffsetOf(biscuit_publickey_object, std);
    biscuit_publickey_object_handlers.free_obj = php_biscuit_publickey_free_obj;

    memcpy(&biscuit_token_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_token_object_handlers.offset = XtOffsetOf(biscuit_token_object, std);
    biscuit_token_object_handlers.free_obj = php_biscuit_token_free_obj;

    memcpy(&biscuit_builder_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_builder_object_handlers.offset = XtOffsetOf(biscuit_builder_object, std);
    biscuit_builder_object_handlers.free_obj = php_biscuit_builder_free_obj;

    memcpy(&biscuit_block_builder_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_block_builder_object_handlers.offset = XtOffsetOf(biscuit_block_builder_object, std);
    biscuit_block_builder_object_handlers.free_obj = php_biscuit_block_builder_free_obj;

    memcpy(&biscuit_authorizer_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_authorizer_object_handlers.offset = XtOffsetOf(biscuit_authorizer_object, std);
    biscuit_authorizer_object_handlers.free_obj = php_biscuit_authorizer_free_obj;

    memcpy(&biscuit_authorizer_builder_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    biscuit_authorizer_builder_object_handlers.offset = XtOffsetOf(biscuit_authorizer_builder_object, std);
    biscuit_authorizer_builder_object_handlers.free_obj = php_biscuit_authorizer_builder_free_obj;

    /* Register BiscuitException class */
    INIT_CLASS_ENTRY(ce, "BiscuitException", NULL);
    ce_BiscuitException = zend_register_internal_class_ex(&ce, zend_ce_exception);

    /* Register BiscuitKeyPair class */
    INIT_CLASS_ENTRY(ce, "BiscuitKeyPair", class_BiscuitKeyPair_methods);
    ce_BiscuitKeyPair = zend_register_internal_class(&ce);
    ce_BiscuitKeyPair->create_object = php_biscuit_keypair_create_object;

    /* Register BiscuitPublicKey class */
    INIT_CLASS_ENTRY(ce, "BiscuitPublicKey", class_BiscuitPublicKey_methods);
    ce_BiscuitPublicKey = zend_register_internal_class(&ce);
    ce_BiscuitPublicKey->create_object = php_biscuit_publickey_create_object;

    /* Register BiscuitToken class */
    INIT_CLASS_ENTRY(ce, "BiscuitToken", class_BiscuitToken_methods);
    ce_BiscuitToken = zend_register_internal_class(&ce);
    ce_BiscuitToken->create_object = php_biscuit_token_create_object;

    /* Register BiscuitBuilder class */
    INIT_CLASS_ENTRY(ce, "BiscuitBuilder", class_BiscuitBuilder_methods);
    ce_BiscuitBuilder = zend_register_internal_class(&ce);
    ce_BiscuitBuilder->create_object = php_biscuit_builder_create_object;

    /* Register BiscuitBlockBuilder class */
    INIT_CLASS_ENTRY(ce, "BiscuitBlockBuilder", class_BiscuitBlockBuilder_methods);
    ce_BiscuitBlockBuilder = zend_register_internal_class(&ce);
    ce_BiscuitBlockBuilder->create_object = php_biscuit_block_builder_create_object;

    /* Register BiscuitAuthorizer class */
    INIT_CLASS_ENTRY(ce, "BiscuitAuthorizer", class_BiscuitAuthorizer_methods);
    ce_BiscuitAuthorizer = zend_register_internal_class(&ce);
    ce_BiscuitAuthorizer->create_object = php_biscuit_authorizer_create_object;

    /* Register BiscuitAuthorizerBuilder class */
    INIT_CLASS_ENTRY(ce, "BiscuitAuthorizerBuilder", class_BiscuitAuthorizerBuilder_methods);
    ce_BiscuitAuthorizerBuilder = zend_register_internal_class(&ce);
    ce_BiscuitAuthorizerBuilder->create_object = php_biscuit_authorizer_builder_create_object;

    /* Register error constants */
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_NONE", None, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_INVALID_ARGUMENT", InvalidArgument, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_INTERNAL_ERROR", InternalError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SIGNATURE_INVALID_FORMAT", FormatSignatureInvalidFormat, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SIGNATURE_INVALID_SIGNATURE", FormatSignatureInvalidSignature, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SEALED_SIGNATURE", FormatSealedSignature, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_EMPTY_KEYS", FormatEmptyKeys, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_UNKNOWN_PUBLIC_KEY", FormatUnknownPublicKey, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_DESERIALIZATION_ERROR", FormatDeserializationError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SERIALIZATION_ERROR", FormatSerializationError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_BLOCK_DESERIALIZATION_ERROR", FormatBlockDeserializationError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_BLOCK_SERIALIZATION_ERROR", FormatBlockSerializationError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_VERSION", FormatVersion, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_INVALID_BLOCK_ID", FormatInvalidBlockId, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_EXISTING_PUBLIC_KEY", FormatExistingPublicKey, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SYMBOL_TABLE_OVERLAP", FormatSymbolTableOverlap, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_PUBLIC_KEY_TABLE_OVERLAP", FormatPublicKeyTableOverlap, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_UNKNOWN_EXTERNAL_KEY", FormatUnknownExternalKey, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_UNKNOWN_SYMBOL", FormatUnknownSymbol, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_APPEND_ON_SEALED", AppendOnSealed, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_LOGIC_INVALID_BLOCK_RULE", LogicInvalidBlockRule, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_LOGIC_UNAUTHORIZED", LogicUnauthorized, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_LOGIC_AUTHORIZER_NOT_EMPTY", LogicAuthorizerNotEmpty, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_LOGIC_NO_MATCHING_POLICY", LogicNoMatchingPolicy, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_LANGUAGE_ERROR", LanguageError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_TOO_MANY_FACTS", TooManyFacts, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_TOO_MANY_ITERATIONS", TooManyIterations, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_TIMEOUT", Timeout, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_CONVERSION_ERROR", ConversionError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_INVALID_KEY_SIZE", FormatInvalidKeySize, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_INVALID_SIGNATURE_SIZE", FormatInvalidSignatureSize, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_INVALID_KEY", FormatInvalidKey, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SIGNATURE_DESERIALIZATION_ERROR", FormatSignatureDeserializationError, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_BLOCK_SIGNATURE_DESERIALIZATION_ERROR", FormatBlockSignatureDeserializationError,
                           CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_SIGNATURE_INVALID_SIGNATURE_GENERATION", FormatSignatureInvalidSignatureGeneration,
                           CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_ALREADY_SEALED", AlreadySealed, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_EXECUTION", Execution, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_UNEXPECTED_QUERY_RESULT", UnexpectedQueryResult, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ERROR_FORMAT_PKCS8", FormatPKCS8, CONST_CS | CONST_PERSISTENT);

    /* Register algorithm constants */
    REGISTER_LONG_CONSTANT("BISCUIT_ALGORITHM_ED25519", Ed25519, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("BISCUIT_ALGORITHM_SECP256R1", Secp256r1, CONST_CS | CONST_PERSISTENT);

    zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);

    return SUCCESS;
}

/* Module shutdown */
PHP_MSHUTDOWN_FUNCTION(biscuit) { return SUCCESS; }

/* Module info */
PHP_MINFO_FUNCTION(biscuit) {
    char version[32];
    snprintf(version, sizeof(version), "%d.%d.%d", BISCUIT_AUTH_MAJOR, BISCUIT_AUTH_MINOR, BISCUIT_AUTH_PATCH);

    php_info_print_table_start();
    php_info_print_table_header(2, "biscuit support", "enabled");
    php_info_print_table_row(2, "Version", PHP_BISCUIT_VERSION);
    php_info_print_table_row(2, "Biscuit C API Version", version);
    php_info_print_table_row(2, "Official Website", "https://www.biscuitsec.org/");
    php_info_print_table_row(2, "Copyright", "2025 Eclipse Foundation");
    php_info_print_table_end();
}

/* {{{ biscuit_module_entry
 */
zend_module_entry biscuit_module_entry = {
    STANDARD_MODULE_HEADER,    "biscuit", NULL, PHP_MINIT(biscuit), PHP_MSHUTDOWN(biscuit), NULL, NULL, PHP_MINFO(biscuit), PHP_BISCUIT_VERSION,
    STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_BISCUIT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(biscuit)
#endif
