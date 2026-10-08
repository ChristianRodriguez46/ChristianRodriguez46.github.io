#!/bin/bash

for arg in "$@"; do
    key=$(echo $arg | cut -f1 -d=)
    val=$(echo $arg | cut -f2 -d=)
    case $key in
        A) A=$val;;
        B) B=$val;;
        *)
    esac
done
((result=A+B))
echo "A + B = $result"
