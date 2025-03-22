/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: db7699b7bc45f0cdb3b5756780286e905e320cf7 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_biscuit_error_message, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_biscuit_error_kind, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_biscuit_error_check_count arginfo_biscuit_error_kind

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_biscuit_error_check_id, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, check_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_biscuit_error_check_block_id arginfo_biscuit_error_check_id

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_biscuit_error_check_rule, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, check_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_biscuit_error_check_is_authorizer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, check_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_BiscuitKeyPair___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, seed, IS_STRING, 0, "\"\"")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, algorithm, IS_LONG, 0, "BISCUIT_ALGORITHM_ED25519")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitKeyPair_public, 0, 0, BiscuitPublicKey, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitKeyPair_serialize arginfo_biscuit_error_message

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitKeyPair_deserialize, 0, 1, BiscuitKeyPair, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, algorithm, IS_LONG, 0, "BISCUIT_ALGORITHM_ED25519")
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitPublicKey_serialize arginfo_biscuit_error_message

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitPublicKey_deserialize, 0, 1, BiscuitPublicKey, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, algorithm, IS_LONG, 0, "BISCUIT_ALGORITHM_ED25519")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_BiscuitBuilder___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitBuilder_setContext, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitBuilder_setRootKeyId, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitBuilder_addFact, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, fact, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitBuilder_addRule, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, rule, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitBuilder_addCheck, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, check, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitBuilder_build, 0, 1, BiscuitToken, 0)
	ZEND_ARG_OBJ_INFO(0, keypair, BiscuitKeyPair, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, seed, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitToken_fromSealed, 0, 2, BiscuitToken, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, root, BiscuitPublicKey, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitToken_appendBlock, 0, 2, BiscuitToken, 0)
	ZEND_ARG_OBJ_INFO(0, builder, BiscuitBlockBuilder, 0)
	ZEND_ARG_OBJ_INFO(0, keypair, BiscuitKeyPair, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitToken_createAuthorizer, 0, 0, BiscuitAuthorizer, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitToken_serialize arginfo_biscuit_error_message

#define arginfo_class_BiscuitToken_serializeSealed arginfo_biscuit_error_message

#define arginfo_class_BiscuitToken_blockCount arginfo_biscuit_error_kind

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitToken_blockContext, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitToken_print arginfo_biscuit_error_message

#define arginfo_class_BiscuitToken_printBlockSource arginfo_class_BiscuitToken_blockContext

#define arginfo_class_BiscuitBlockBuilder___construct arginfo_class_BiscuitBuilder___construct

#define arginfo_class_BiscuitBlockBuilder_setContext arginfo_class_BiscuitBuilder_setContext

#define arginfo_class_BiscuitBlockBuilder_addFact arginfo_class_BiscuitBuilder_addFact

#define arginfo_class_BiscuitBlockBuilder_addRule arginfo_class_BiscuitBuilder_addRule

#define arginfo_class_BiscuitBlockBuilder_addCheck arginfo_class_BiscuitBuilder_addCheck

#define arginfo_class_BiscuitAuthorizerBuilder___construct arginfo_class_BiscuitBuilder___construct

#define arginfo_class_BiscuitAuthorizerBuilder_addFact arginfo_class_BiscuitBuilder_addFact

#define arginfo_class_BiscuitAuthorizerBuilder_addRule arginfo_class_BiscuitBuilder_addRule

#define arginfo_class_BiscuitAuthorizerBuilder_addCheck arginfo_class_BiscuitBuilder_addCheck

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitAuthorizerBuilder_addPolicy, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, policy, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BiscuitAuthorizerBuilder_build, 0, 1, BiscuitAuthorizer, 0)
	ZEND_ARG_OBJ_INFO(0, token, BiscuitToken, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitAuthorizerBuilder_buildUnauthenticated arginfo_class_BiscuitToken_createAuthorizer

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BiscuitAuthorizer_authorize, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BiscuitAuthorizer_print arginfo_biscuit_error_message


ZEND_FUNCTION(biscuit_error_message);
ZEND_FUNCTION(biscuit_error_kind);
ZEND_FUNCTION(biscuit_error_check_count);
ZEND_FUNCTION(biscuit_error_check_id);
ZEND_FUNCTION(biscuit_error_check_block_id);
ZEND_FUNCTION(biscuit_error_check_rule);
ZEND_FUNCTION(biscuit_error_check_is_authorizer);
ZEND_METHOD(BiscuitKeyPair, __construct);
ZEND_METHOD(BiscuitKeyPair, public);
ZEND_METHOD(BiscuitKeyPair, serialize);
ZEND_METHOD(BiscuitKeyPair, deserialize);
ZEND_METHOD(BiscuitPublicKey, serialize);
ZEND_METHOD(BiscuitPublicKey, deserialize);
ZEND_METHOD(BiscuitBuilder, __construct);
ZEND_METHOD(BiscuitBuilder, setContext);
ZEND_METHOD(BiscuitBuilder, setRootKeyId);
ZEND_METHOD(BiscuitBuilder, addFact);
ZEND_METHOD(BiscuitBuilder, addRule);
ZEND_METHOD(BiscuitBuilder, addCheck);
ZEND_METHOD(BiscuitBuilder, build);
ZEND_METHOD(BiscuitToken, fromSealed);
ZEND_METHOD(BiscuitToken, appendBlock);
ZEND_METHOD(BiscuitToken, createAuthorizer);
ZEND_METHOD(BiscuitToken, serialize);
ZEND_METHOD(BiscuitToken, serializeSealed);
ZEND_METHOD(BiscuitToken, blockCount);
ZEND_METHOD(BiscuitToken, blockContext);
ZEND_METHOD(BiscuitToken, print);
ZEND_METHOD(BiscuitToken, printBlockSource);
ZEND_METHOD(BiscuitBlockBuilder, __construct);
ZEND_METHOD(BiscuitBlockBuilder, setContext);
ZEND_METHOD(BiscuitBlockBuilder, addFact);
ZEND_METHOD(BiscuitBlockBuilder, addRule);
ZEND_METHOD(BiscuitBlockBuilder, addCheck);
ZEND_METHOD(BiscuitAuthorizerBuilder, __construct);
ZEND_METHOD(BiscuitAuthorizerBuilder, addFact);
ZEND_METHOD(BiscuitAuthorizerBuilder, addRule);
ZEND_METHOD(BiscuitAuthorizerBuilder, addCheck);
ZEND_METHOD(BiscuitAuthorizerBuilder, addPolicy);
ZEND_METHOD(BiscuitAuthorizerBuilder, build);
ZEND_METHOD(BiscuitAuthorizerBuilder, buildUnauthenticated);
ZEND_METHOD(BiscuitAuthorizer, authorize);
ZEND_METHOD(BiscuitAuthorizer, print);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(biscuit_error_message, arginfo_biscuit_error_message)
	ZEND_FE(biscuit_error_kind, arginfo_biscuit_error_kind)
	ZEND_FE(biscuit_error_check_count, arginfo_biscuit_error_check_count)
	ZEND_FE(biscuit_error_check_id, arginfo_biscuit_error_check_id)
	ZEND_FE(biscuit_error_check_block_id, arginfo_biscuit_error_check_block_id)
	ZEND_FE(biscuit_error_check_rule, arginfo_biscuit_error_check_rule)
	ZEND_FE(biscuit_error_check_is_authorizer, arginfo_biscuit_error_check_is_authorizer)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitKeyPair_methods[] = {
	ZEND_ME(BiscuitKeyPair, __construct, arginfo_class_BiscuitKeyPair___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitKeyPair, public, arginfo_class_BiscuitKeyPair_public, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitKeyPair, serialize, arginfo_class_BiscuitKeyPair_serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitKeyPair, deserialize, arginfo_class_BiscuitKeyPair_deserialize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitPublicKey_methods[] = {
	ZEND_ME(BiscuitPublicKey, serialize, arginfo_class_BiscuitPublicKey_serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitPublicKey, deserialize, arginfo_class_BiscuitPublicKey_deserialize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitBuilder_methods[] = {
	ZEND_ME(BiscuitBuilder, __construct, arginfo_class_BiscuitBuilder___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, setContext, arginfo_class_BiscuitBuilder_setContext, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, setRootKeyId, arginfo_class_BiscuitBuilder_setRootKeyId, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, addFact, arginfo_class_BiscuitBuilder_addFact, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, addRule, arginfo_class_BiscuitBuilder_addRule, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, addCheck, arginfo_class_BiscuitBuilder_addCheck, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBuilder, build, arginfo_class_BiscuitBuilder_build, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitToken_methods[] = {
	ZEND_ME(BiscuitToken, fromSealed, arginfo_class_BiscuitToken_fromSealed, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(BiscuitToken, appendBlock, arginfo_class_BiscuitToken_appendBlock, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, createAuthorizer, arginfo_class_BiscuitToken_createAuthorizer, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, serialize, arginfo_class_BiscuitToken_serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, serializeSealed, arginfo_class_BiscuitToken_serializeSealed, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, blockCount, arginfo_class_BiscuitToken_blockCount, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, blockContext, arginfo_class_BiscuitToken_blockContext, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, print, arginfo_class_BiscuitToken_print, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitToken, printBlockSource, arginfo_class_BiscuitToken_printBlockSource, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitBlockBuilder_methods[] = {
	ZEND_ME(BiscuitBlockBuilder, __construct, arginfo_class_BiscuitBlockBuilder___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBlockBuilder, setContext, arginfo_class_BiscuitBlockBuilder_setContext, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBlockBuilder, addFact, arginfo_class_BiscuitBlockBuilder_addFact, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBlockBuilder, addRule, arginfo_class_BiscuitBlockBuilder_addRule, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitBlockBuilder, addCheck, arginfo_class_BiscuitBlockBuilder_addCheck, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitAuthorizerBuilder_methods[] = {
	ZEND_ME(BiscuitAuthorizerBuilder, __construct, arginfo_class_BiscuitAuthorizerBuilder___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, addFact, arginfo_class_BiscuitAuthorizerBuilder_addFact, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, addRule, arginfo_class_BiscuitAuthorizerBuilder_addRule, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, addCheck, arginfo_class_BiscuitAuthorizerBuilder_addCheck, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, addPolicy, arginfo_class_BiscuitAuthorizerBuilder_addPolicy, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, build, arginfo_class_BiscuitAuthorizerBuilder_build, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizerBuilder, buildUnauthenticated, arginfo_class_BiscuitAuthorizerBuilder_buildUnauthenticated, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_BiscuitAuthorizer_methods[] = {
	ZEND_ME(BiscuitAuthorizer, authorize, arginfo_class_BiscuitAuthorizer_authorize, ZEND_ACC_PUBLIC)
	ZEND_ME(BiscuitAuthorizer, print, arginfo_class_BiscuitAuthorizer_print, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
