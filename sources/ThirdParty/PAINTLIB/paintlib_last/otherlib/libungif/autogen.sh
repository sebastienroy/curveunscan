#!/bin/sh

# This script runs commands necessary to generate a Makefile for libgif.

echo "Warning: This script will run configure for you -- if you need to pass"
echo "  arguments to configure, please give them as arguments to this script."

aclocal
automake --add-missing
autoconf
automake --add-missing
configure $*

exit 0
