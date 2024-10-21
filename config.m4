dnl config.m4 for extension biscuit

PHP_ARG_WITH(biscuit, for biscuit support,
[  --with-biscuit[=DIR]             Include biscuit support])

if test "$PHP_BISCUIT" != "no"; then
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/biscuit_auth/biscuit_auth.h"

  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  AC_MSG_CHECKING([for biscuit_auth])

  if test -r $PHP_BISCUIT/$SEARCH_FOR; then # path given as parameter
    BISCUIT_DIR=$PHP_BISCUIT
    AC_MSG_RESULT(found in $PHP_BISCUIT)
  
  dnl pkg-config output
  elif test -x "$PKG_CONFIG" && $PKG_CONFIG --exists biscuit_auth; then
    BISCUIT_VERSION=`$PKG_CONFIG biscuit_auth --modversion`
    if $PKG_CONFIG biscuit_auth --atleast-version=4.1.0; then
      BISCUIT_CFLAGS=`$PKG_CONFIG biscuit_auth --cflags`
      BISCUIT_LIBS=`$PKG_CONFIG biscuit_auth --libs`
      AC_MSG_RESULT(version $BISCUIT_VERSION found using pkg-config)
      PHP_EVAL_LIBLINE($BISCUIT_LIBS, BISCUIT_SHARED_LIBADD)
      PHP_EVAL_INCLINE($BISCUIT_CFLAGS)
    else
      AC_MSG_ERROR([Biscuit lib $BISCUIT_VERSION is too old, version >= 4.1.0 required])
    fi
  else # search default path list
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        BISCUIT_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
    if test -z "$BISCUIT_DIR"; then
      AC_MSG_RESULT([not found])
      AC_MSG_ERROR([Please install the biscuit library - see https://github.com/biscuit-auth/biscuit-rust])
    fi
  fi

  LIBNAME=biscuit_auth
  LIBSYMBOL=create_block

  if test -n "$BISCUIT_DIR"; then
    PHP_ADD_INCLUDE($BISCUIT_DIR/include)
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BISCUIT_DIR/$PHP_LIBDIR, BISCUIT_SHARED_LIBADD)
  fi

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    AC_DEFINE(HAVE_BISCUITLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong Biscuit lib version or lib not found])
  ],[
  ])

  PHP_SUBST(BISCUIT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(biscuit, biscuit.c, $ext_shared)
fi
