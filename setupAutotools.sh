#!/bin/bash
libtoolize
autoheader
aclocal
automake --add-missing --copy
autoconf
