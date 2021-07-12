#!/bin/bash
autoheader
aclocal
automake --add-missing --copy
autoconf
