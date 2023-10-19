AC_INIT([libcasagpio.so], [0.1])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AM_PROG_AR

LT_INIT

AC_CONFIG_FILES(Makefile)
AC_CONFIG_MACRO_DIRS([m4])

AC_PREFIX_DEFAULT([/usr])

AC_CHECK_LIB([gpiod], [gpiod_line_set_value],
  [LIBS="-lgpiod $LIBS"],
  [AC_MSG_ERROR([libgpiod not found])])

AC_OUTPUT
