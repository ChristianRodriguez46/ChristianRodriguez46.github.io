#!/usr/bin/env bash
# lab8-02.sh

echo -n "Enter a number: "
read n

fact=1
for (( i=2; i<=n; i++ )); do
  fact=$(( fact * i ))
done

echo "$n! = $fact"
