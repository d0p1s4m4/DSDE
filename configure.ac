AC_INIT([D0p1 Simple Desktop Envirnment],
        [0.1],
        [],
        [dsde]
        [])

AC_CONFIG_HEADERS([include/dsde_config.h])
AH_TOP([
#ifndef DSDE_CONFIG_H
# define DSDE_CONFIG_H 1
])

AH_BOTTOM([
#endif /* !DSDE_CONFIG_H */
])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_LANG(C)
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_RANLIB
AM_PROG_AR
AM_PROG_CC_C_O

AC_CHECK_INCLUDES_DEFAULT
AC_C_CONST
AC_CHECK_TYPE(size_t)

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.16)

dnl +---------------------------+
dnl | Check xlib availability   |
dnl +---------------------------+

AC_CHECK_HEADERS([X11/Xlib.h], [], [
    AC_MSG_ERROR([unable to find Xlib header])
])
AC_SEARCH_LIBS([XOpenDisplay], [X11], [], [
    AC_MSG_ERROR([unable to find XOpenDisplay()])
])

dnl +---------------------------+
dnl | Check dtk availability    |
dnl +---------------------------+

AC_ARG_WITH(dtk,
	AS_HELP_STRING([--with-dtk],
					[]),
					[
case "$with_dtk" in
	yes)
		:
		;;
	no)
		AC_MSG_ERROR([DTK is mandatory])
		;;
	*)
		if test ! -d "$with_dtk" ; then
			AC_MSG_ERROR([--with-dtk path does not point to a directory])
		fi
		LIBDTK_PATH="-L$with_dtk/lib"
		CFLAGS="-I$with_dtk/include $CFLAGS"
		LIBS="$LIBS $LIBDTK_PATH"
esac
])

AC_CHECK_HEADERS([dtk.h], [], [
    AC_MSG_WARN([unable to find DTK header])
])

AC_SEARCH_LIBS([dtk_application_new], [dtk], [], [
	AC_MSG_WARN([unable to find dtk_application_new])
])

AC_CONFIG_FILES([Makefile
                 src/Makefile
				 src/dsfm/Makefile
				 src/dsterm/Makefile
                 src/dswm/Makefile])
AC_OUTPUT
