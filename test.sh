#!/bin/bash

function error() {
    echo "$@" >&2
    exit 1
}

cmp <(cat cat.c | ./cat) cat.c || error "Error: differ $LINENO"

echo "Ok." 

