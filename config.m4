PHP_ARG_WITH(timeuuid, for timeuuid support,
Make sure that the comment is aligned:
[  --with-timeuuid             Include timeuuid support])

dnl PHP_ARG_ENABLE(timeuuid, whether to enable timeuuid support,
dnl Make sure that the comment is aligned:
dnl [  --enable-timeuuid           Enable timeuuid support])

if test "$PHP_TIMEUUID" != "no"; then

  dnl # --with-timeuuid -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/timeuuid.h"  # you most likely want to change this
  dnl if test -r $PHP_TIMEUUID/$SEARCH_FOR; then # path given as parameter
  dnl   TIMEUUID_DIR=$PHP_TIMEUUID
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for timeuuid files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TIMEUUID_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TIMEUUID_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the timeuuid distribution])
  dnl fi

  dnl # --with-timeuuid -> add include path
  dnl PHP_ADD_INCLUDE($TIMEUUID_DIR/include)

  dnl # --with-timeuuid -> check for lib and symbol presence
  dnl LIBNAME=timeuuid # you may want to change this
  dnl LIBSYMBOL=timeuuid # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TIMEUUID_DIR/lib, TIMEUUID_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TIMEUUIDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong timeuuid lib version or lib not found])
  dnl ],[
  dnl   -L$TIMEUUID_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TIMEUUID_SHARED_LIBADD)

  PHP_NEW_EXTENSION(timeuuid, timeuuid.c, $ext_shared)
fi
