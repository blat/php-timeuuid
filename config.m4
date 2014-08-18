PHP_ARG_WITH(timeuuid, for timeuuid support,
Make sure that the comment is aligned:
[  --with-timeuuid             Include timeuuid support])

if test "$PHP_TIMEUUID" != "no"; then

  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/uuid/uuid.h"
  if test -r $PHP_TIMEUUID/$SEARCH_FOR; then
    LIBUUID_DIR=$PHP_TIMEUUID
  else
    AC_MSG_CHECKING([for timeuuid files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        LIBUUID_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$LIBUUID_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the timeuuid distribution])
  fi

  PHP_ADD_INCLUDE($LIBUUID_DIR/include)

  LIBNAME=uuid
  LIBSYMBOL=uuid_generate_time_safe

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBUUID_DIR/lib, TIMEUUID_SHARED_LIBADD)
    AC_DEFINE(HAVE_UUIDLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong uuid lib version or lib not found])
  ],[
    -L$LIBUUID_DIR/lib -lm
  ])

  PHP_SUBST(TIMEUUID_SHARED_LIBADD)

  PHP_NEW_EXTENSION(timeuuid, timeuuid.c, $ext_shared)
fi
