dnl config.m4 for extension biscuit

PHP_ARG_WITH(biscuit, for biscuit support,
  [  --with-biscuit           Include biscuit support])

if test "$PHP_BISCUIT" != "no"; then
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/biscuit_capi/biscuit_auth.h"
  
  if test -r $PHP_BISCUIT/$SEARCH_FOR; then
    BISCUIT_DIR=$PHP_BISCUIT
  else
    AC_MSG_CHECKING([for biscuit_auth.h in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        BISCUIT_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$BISCUIT_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install the biscuit library])
  fi

  PHP_ADD_INCLUDE($BISCUIT_DIR/include)
  SOURCES="biscuit.c biscuit_methods.c"
  LIBNAME=biscuit_auth
  LIBSYMBOL=biscuit_authorizer

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BISCUIT_DIR/$PHP_LIBDIR, BISCUIT_SHARED_LIBADD)
    AC_DEFINE(HAVE_BISCUITLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong biscuit lib version or lib not found])
  ],[
    -L$BISCUIT_DIR/$PHP_LIBDIR -lm
  ])

  ORIG_LDFLAGS="$LDFLAGS"
  ORIG_CPPFLAGS="$CPPFLAGS"
  LDFLAGS="-L$BISCUIT_DIR/$PHP_LIBDIR -lm"
  CPPFLAGS="-I$BISCUIT_DIR/include"

  AC_MSG_CHECKING([PHP version])
  PHP_VERSION=`${PHP_CONFIG} --version`
  PHP_VERSION_ID=`echo "${PHP_VERSION}" | $AWK 'BEGIN { FS = "."; } { printf "%d", ($1 * 100 + $2) * 100 + $3;}'`
  
  if test "$PHP_VERSION_ID" -lt "80100"; then
    AC_MSG_ERROR([PHP version 8.1.0 or greater required])
  fi

  LDFLAGS="$ORIG_LDFLAGS"
  CPPFLAGS="$ORIG_CPPFLAGS"

  PHP_SUBST(BISCUIT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(biscuit, $SOURCES, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
