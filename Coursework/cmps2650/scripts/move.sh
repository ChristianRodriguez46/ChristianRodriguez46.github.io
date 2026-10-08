#!/bin/bash
f=$1
base="${f%.*}"
ext="${1##*.}"
d="$(date +%Y%m%d)"
mv "$f" "${base}_${d}.${ext}"
