
AUTOMAKE_OPTIONS        =

# EXTRA_DIST = config/config.guess \
config/config.sub \
config/install-sh \
config/ltconfig \
config/ltmain.sh \
config/missing \
config/mkinstalldirs \
reconfig \
acconfig.h \
paintlib-config.in \
TODO \
gnu/libtiff/port.h \
gnu/libtiff/tif_dir.h \
gnu/libtiff/tiffconf.h \
gnu/libtiff/tiffiop.h

MAINTAINERCLEANFILES =

# Directories to process
if WIN32
SUBDIRS = common win lib gnu
else
SUBDIRS = common lib gnu
endif

DIST_SUBDIRS = common lib gnu

bin_SCRIPTS = paintlib-config
