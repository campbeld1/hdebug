PHP_ARG_ENABLE(huborg_debug, whether to enable my extension,
[ --enable-huborg-debug   Enable my extension])
 
if test "$PHP_HUBORG_DEBUG" = "yes"; then
  AC_DEFINE(HAVE_HUBORG_DEBUG, 1, [Whether you have my extension])
  PHP_NEW_EXTENSION(huborg_debug, huborg_debug.c, $ext_shared)
fi
