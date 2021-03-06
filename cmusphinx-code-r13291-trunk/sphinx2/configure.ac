dnl Welcome to the Sphinx-2 automated build system.
dnl try not to hurt yourself ;)

AC_INIT([sphinx2], [0.6])
AM_INIT_AUTOMAKE([no-define foreign])
AC_CONFIG_MACRO_DIR([m4])

CFLAGS=${CFLAGS:--g -O2 -Wall}

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_WORDS_BIGENDIAN
AC_TYPE_SIGNAL

hmmdata=`ls -1 $srcdir/model/hmm/6k | egrep -v '(Makefile|CVS)'`
hmmdata=`echo $hmmdata`

lmdata=`ls -1 $srcdir/model/lm/turtle/ | egrep -v '(Makefile|CVS)'`
lmdata=`echo $lmdata`

docdata=`ls -1 $srcdir/doc | egrep -v '(Makefile|CVS)'`
docdata=`echo $docdata`

AC_CANONICAL_HOST


dnl
dnl determine audio type or use none if none supported on this platform
dnl

ad_files=""
ad_libs=""

dnl
dnl Allow compilation for fixed or floating-point MFCC and GMM computation
dnl
AC_ARG_ENABLE(fixed,
	AC_HELP_STRING([--enable-fixed],
		       [Use fixed-point for MFCC and GMM computation]),[
if test x$enableval = xyes; then
   AC_DEFINE(FIXED_POINT)
fi])

dnl
dnl Optional log-domain power spectrum for fixed-point - more accurate but slower
dnl
AC_ARG_ENABLE(fixed,
	AC_HELP_STRING([--enable-logpower],
		       [Calculate power spectrum in log domain (slower but more accurate)]),[
if test x$enableval = xyes; then
   AC_DEFINE(LOG_SPEC)
fi])

dnl Added from suggestion by 
dnl Jasper van Veghel <jvveghel@vanboxtelsoftware.nl>, 02/03/2003:
AC_ARG_WITH(alsa,
           AC_HELP_STRING([--with-alsa], [Use ALSA library for sound I/O]),
           [ad_files="ad_alsa.lo"
            ad_backend="AD_BACKEND_ALSA"
            ad_libs="-lasound"
	    AC_DEFINE(AD_BACKEND_ALSA)
            AC_CHECK_HEADER(alsa/asoundlib.h,,
                    AC_ERROR(ALSA header file <alsa/asoundlib.h> not found!))]
)

if test "x$ad_files" = "x"; then
        case $host in
                *-*-linux*)
                        ad_files="ad_oss.lo"
                        ad_backend="AD_BACKEND_OSS"
			AC_DEFINE(AD_BACKEND_OSS)
                        ;;
                # FIXME: isn't this the same OSS as on Linux?
                *-*-freebsd*|*-*-netbsd*|*-*-openbsd*)
                        ad_files="ad_oss_bsd.lo mulaw_base.lo"
                        ad_libs="-lossaudio"
                        ad_backend="AD_BACKEND_OSS_BSD"
			AC_DEFINE(AD_BACKEND_OSS_BSD)
                        ;;
                *-*-osf*)
                        ad_files="ad_osf.lo mulaw_base.lo"
                        ad_backend="AD_BACKEND_OSF"
			AC_DEFINE(AD_BACKEND_OSF)
                        ;;
                *-*-irix*)
                        ad_files="ad_irix.lo mulaw_base.lo"
                        ad_libs="-laudio"
                        ad_backend="AD_BACKEND_IRIX"
			AC_DEFINE(AD_BACKEND_IRIX)
                        ;;
                *-*-sunos4*)
                        ad_files="ad_sunos.lo audio_utils_sunos.lo"
                        ad_libs="-lm -lnsl -ldl"
                        ad_backend="AD_BACKEND_SUNOS"
			AC_DEFINE(AD_BACKEND_SUNOS)
                        ;;
                *-*-solaris*)
                        ad_files="ad_sunos.lo audio_utils_sunos.lo"
                        ad_libs="-lm -lnsl -lsocket -ldl"
                        ad_backend="AD_BACKEND_SUNOS"
			AC_DEFINE(AD_BACKEND_SUNOS)
                        ;;
                *-*-*cygwin*)
                        ad_files="play_win32.lo rec_win32.lo"
                        ad_libs="-lwinmm"
                        ad_backend="AD_BACKEND_WIN32"
			AC_DEFINE(AD_BACKEND_WIN32)
                        ;;
                *-*apple*-*)
                        ad_files="ad_base.lo"
                        ad_backend="AD_BACKEND_NONE"
			AC_DEFINE(AD_BACKEND_NONE)
                        ;;
                *)
                        ad_files="ad_base.lo"
                        ad_backend="AD_BACKEND_NONE"
                        AC_MSG_RESULT([No audio interface for host type $host.])
			AC_DEFINE(AD_BACKEND_NONE)
                        ;;
        esac
fi

AC_PATH_PROG(PERL,perl)
AC_PATH_PROG(CSH,csh)
AC_SUBST(hmmdata)
AC_SUBST(lmdata)
AC_SUBST(docdata)
AC_SUBST(ad_files)
AC_SUBST(ad_libs)
AC_SUBST(ad_backend)
AC_SUBST(PERL)
AC_SUBST(CSH)

LT_INIT

AC_OUTPUT([
sphinx2.pc
Makefile
include/Makefile
include/ad_conf.h
src/Makefile
src/libsphinx2/Makefile
src/libsphinx2/include/Makefile
src/libsphinx2fe/Makefile
src/libsphinx2ad/Makefile
src/examples/Makefile
model/Makefile
model/hmm/Makefile
model/hmm/6k/Makefile
model/lm/Makefile
model/lm/turtle/Makefile
doc/Makefile
scripts/Makefile
scripts/allphone-test.csh
scripts/batch.csh
scripts/sphinx2-demo
scripts/sphinx2-simple
scripts/sphinx2-phone
scripts/sphinx2-test
scripts/stress2sphinx
scripts/sphinx2-align
])

chmod +x scripts/allphone-test.csh
chmod +x scripts/batch.csh
chmod +x scripts/sphinx2-demo
chmod +x scripts/sphinx2-simple
chmod +x scripts/sphinx2-test
chmod +x scripts/sphinx2-phone
chmod +x scripts/stress2sphinx
chmod +x scripts/sphinx2-align
