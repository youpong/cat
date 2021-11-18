#!/bin/bash

set -o nounset

prog=./cat

function error() {
    echo "$@" >&2
    exit 1
}

#
# normal cases...
#

# returns 0
$prog $prog >/dev/null                 || error "must return 0"

# one file
cmp <($prog $prog) $prog               || error "differ in $LINENO"
# stdin
cmp <(cat $prog | $prog) $prog         || error "differ in $LINENO"
# 0 input
cmp <($prog /dev/null) /dev/null       || error "0 input in $LINENO"
# - as stdin
cmp <(cat $prog | $prog -) $prog       || error "differ $LINENO"
# multiple file
cmp <($prog $prog $0) <(cat $prog $0)  || error "multi files $LINENO"

#
# irregular cases...
#

# applied multiple standard input: not same as cat(1)
cat /dev/null | $prog - - 2>/dev/null \
    && error "should exit in error: multiple stdin $LINENO"

# cannot open file
$prog ''       2>/dev/null >&2 \
    && error "should exit in error: $LINENO: cannot open file"

# directory
$prog .       2>/dev/null >&2 \
    && error "should exit in error: $LINENO: directory"

echo "Ok."
