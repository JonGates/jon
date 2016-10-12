#!/bin/sh

set -e

#autoscan
aclocal
autoheader
automake --foreign --add-missing --copy
autoconf --warnings=all

./configure
make
make install