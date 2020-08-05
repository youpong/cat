#!/bin/bash

function error() {
    echo "$@" >&2
    exit 1
}

cmp <(cat cat.c | ./cat) cat.c || error "Error: differ $LINENO"
cmp <(cat /dev/null | ./cat) /dev/null || error "Error: differ $LINENO"

cmp <(./cat cat.c) cat.c || error "Error: differ $LINENO"

echo "Ok." 

