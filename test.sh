#!/bin/bash

function error() {
    echo "$@" >&2
    exit 1
}

cmp <(cat cat.c | ./cat) cat.c || error "Error: differ $LINENO"
cmp <(cat /dev/null | ./cat) /dev/null || error "Error: 0 input $LINENO"

cmp <(./cat cat.c) cat.c || error "Error: differ $LINENO"

# - as stdin
cmp <(cat cat.c | ./cat -) cat.c || error "Error: differ $LINENO"

# multiple file
cmp <(./cat cat.c test.sh) <(cat cat.c test.sh) \
    || error "Error: multi files  $LINENO"

# multiple -
cat /dev/null | ./cat - - 2>/dev/null \
    && error "Error: multiple - throw error $LINENO"

# cannot open file
./cat ''       2>/dev/null >&2 && error "Error: $LINENO: cannot open file"
./cat '' cat.c 2>/dev/null >&2 && error "Error: $LINENO: cannot open file"

# directory
./cat .       2>/dev/null >&2 && error "Error: $LINENO: directory"
./cat . cat.c 2>/dev/null >&2 && error "Error: $LINENO: directory"

echo "Ok." 
