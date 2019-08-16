## Process this file with automake to produce a Makefile.in for libungif.

EXTRA_DIST = Makefile.unx

lib_LTLIBRARIES = libungif.la
noinst_LIBRARIES = libgetarg.a

include_HEADERS = gif_lib.h

libgetarg_a_SOURCES = getarg.c getarg.h

libungif_la_SOURCES = dev2gif.c   \
                    dgif_lib.c  \
                    egif_lib.c  \
                    gif_err.c   \
                    gif_font.c  \
                    gifalloc.c  \
                    qprintf.c   \
                    quantize.c  \
					gif_lib_private.h

## Version is 4.1.0  [x:y:z  (x - z).(z).(y) ]
libungif_la_LDFLAGS = -version-info 5:0:1
libungif_la_LIBADD = @DEVS@
CFLAGS = @CFLAGS@ $(X_CFLAGS)
