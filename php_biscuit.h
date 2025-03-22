/* biscuit extension for PHP */
#ifndef PHP_BISCUIT_H
#define PHP_BISCUIT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* Define the version */
#define PHP_BISCUIT_VERSION "0.1.0"

/* Object structures */
typedef struct _biscuit_keypair_object {
  void *keypair;
  zend_object std;
} biscuit_keypair_object;

typedef struct _biscuit_publickey_object {
  void *publickey;
  zend_object std;
} biscuit_publickey_object;

typedef struct _biscuit_token_object {
  void *token;
  zend_object std;
} biscuit_token_object;

typedef struct _biscuit_builder_object {
  void *builder;
  zend_object std;
} biscuit_builder_object;

typedef struct _biscuit_block_builder_object {
  void *block_builder;
  zend_object std;
} biscuit_block_builder_object;

typedef struct _biscuit_authorizer_object {
  void *authorizer;
  zend_object std;
} biscuit_authorizer_object;

typedef struct _biscuit_authorizer_builder_object {
  void *authorizer_builder;
  zend_object std;
} biscuit_authorizer_builder_object;

/* Object handlers */
extern zend_object_handlers biscuit_keypair_object_handlers;
extern zend_object_handlers biscuit_publickey_object_handlers;
extern zend_object_handlers biscuit_token_object_handlers;
extern zend_object_handlers biscuit_builder_object_handlers;
extern zend_object_handlers biscuit_block_builder_object_handlers;
extern zend_object_handlers biscuit_authorizer_object_handlers;
extern zend_object_handlers biscuit_authorizer_builder_object_handlers;

/* Object creation/free functions */
zend_object *php_biscuit_keypair_create_object(zend_class_entry *ce);
void php_biscuit_keypair_free_obj(zend_object *obj);

zend_object *php_biscuit_publickey_create_object(zend_class_entry *ce);
void php_biscuit_publickey_free_obj(zend_object *obj);

zend_object *php_biscuit_token_create_object(zend_class_entry *ce);
void php_biscuit_token_free_obj(zend_object *obj);

zend_object *php_biscuit_builder_create_object(zend_class_entry *ce);
void php_biscuit_builder_free_obj(zend_object *obj);

zend_object *php_biscuit_block_builder_create_object(zend_class_entry *ce);
void php_biscuit_block_builder_free_obj(zend_object *obj);

zend_object *php_biscuit_authorizer_create_object(zend_class_entry *ce);
void php_biscuit_authorizer_free_obj(zend_object *obj);

zend_object *php_biscuit_authorizer_builder_create_object(zend_class_entry *ce);
void php_biscuit_authorizer_builder_free_obj(zend_object *obj);

/* Object access macros */
static biscuit_keypair_object *
php_biscuit_keypair_from_obj(zend_object *obj) {
  return (biscuit_keypair_object *)((char *)(obj)-XtOffsetOf(
      biscuit_keypair_object, std));
}
#define Z_BISCUIT_KEYPAIR_P(zv) php_biscuit_keypair_from_obj(Z_OBJ_P(zv))

static biscuit_publickey_object *
php_biscuit_publickey_from_obj(zend_object *obj) {
  return (biscuit_publickey_object *)((char *)(obj)-XtOffsetOf(
      biscuit_publickey_object, std));
}
#define Z_BISCUIT_PUBLICKEY_P(zv) php_biscuit_publickey_from_obj(Z_OBJ_P(zv))

static biscuit_token_object *
php_biscuit_token_from_obj(zend_object *obj) {
  return (biscuit_token_object *)((char *)(obj)-XtOffsetOf(biscuit_token_object,
                                                           std));
}
#define Z_BISCUIT_TOKEN_P(zv) php_biscuit_token_from_obj(Z_OBJ_P(zv))

static inline biscuit_builder_object *
php_biscuit_builder_from_obj(zend_object *obj) {
  return (biscuit_builder_object *)((char *)(obj)-XtOffsetOf(
      biscuit_builder_object, std));
}
#define Z_BISCUIT_BUILDER_P(zv) php_biscuit_builder_from_obj(Z_OBJ_P(zv))

static inline biscuit_block_builder_object *
php_biscuit_block_builder_from_obj(zend_object *obj) {
  return (biscuit_block_builder_object *)((char *)(obj)-XtOffsetOf(
      biscuit_block_builder_object, std));
}
#define Z_BISCUIT_BLOCK_BUILDER_P(zv)                                          \
  php_biscuit_block_builder_from_obj(Z_OBJ_P(zv))

static inline biscuit_authorizer_object *
php_biscuit_authorizer_from_obj(zend_object *obj) {
  return (biscuit_authorizer_object *)((char *)(obj)-XtOffsetOf(
      biscuit_authorizer_object, std));
}
#define Z_BISCUIT_AUTHORIZER_P(zv) php_biscuit_authorizer_from_obj(Z_OBJ_P(zv))

static inline biscuit_authorizer_builder_object *
php_biscuit_authorizer_builder_from_obj(zend_object *obj) {
  return (biscuit_authorizer_builder_object *)((char *)(obj)-XtOffsetOf(
      biscuit_authorizer_builder_object, std));
}
#define Z_BISCUIT_AUTHORIZER_BUILDER_P(zv)                                     \
  php_biscuit_authorizer_builder_from_obj(Z_OBJ_P(zv))

/* Class entries */
extern zend_class_entry *ce_BiscuitKeyPair;
extern zend_class_entry *ce_BiscuitPublicKey;
extern zend_class_entry *ce_BiscuitToken;
extern zend_class_entry *ce_BiscuitBuilder;
extern zend_class_entry *ce_BiscuitBlockBuilder;
extern zend_class_entry *ce_BiscuitAuthorizer;
extern zend_class_entry *ce_BiscuitAuthorizerBuilder;
extern zend_class_entry *ce_BiscuitException;

/* Module functions */
PHP_MINIT_FUNCTION(biscuit);
PHP_MSHUTDOWN_FUNCTION(biscuit);
PHP_MINFO_FUNCTION(biscuit);

/* Error handling functions */
PHP_FUNCTION(biscuit_error_message);
PHP_FUNCTION(biscuit_error_kind);
PHP_FUNCTION(biscuit_error_check_count);
PHP_FUNCTION(biscuit_error_check_id);
PHP_FUNCTION(biscuit_error_check_block_id);
PHP_FUNCTION(biscuit_error_check_rule);
PHP_FUNCTION(biscuit_error_check_is_authorizer);

/* Module entry */
extern zend_module_entry biscuit_module_entry;
#define phpext_biscuit_ptr &biscuit_module_entry

#endif /* PHP_BISCUIT_H */
