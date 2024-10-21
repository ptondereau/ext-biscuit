/* biscuit extension for PHP */
#ifndef PHP_BISCUIT_H
# define PHP_BISCUIT_H

extern zend_module_entry biscuit_module_entry;
# define phpext_biscuit_ptr &biscuit_module_entry

# define PHP_BISCUIT_VERSION "0.1.0"


#ifdef PHP_WIN32
# define PHP_SODIUM_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_SODIUM_API __attribute__ ((visibility("default")))
#else
# define PHP_SODIUM_API
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#endif	/* PHP_BISCUIT_H */
