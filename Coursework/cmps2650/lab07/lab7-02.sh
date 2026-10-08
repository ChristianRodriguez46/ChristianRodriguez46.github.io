#!/bin/bash

# usage: ./lab7-02.sh file.cpp

g++ "$1" -o a.out 2>/dev/null
if [ $? -eq 0 ]; then
  echo "Compile successful"
else
  echo "Compile failed"
fi
