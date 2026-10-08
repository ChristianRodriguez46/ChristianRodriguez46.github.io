#!/usr/bin/env bash
# lab8-03.sh

calc() {
  local n="$1"
  local fact=1
  for (( i=2; i<=n; i++ )); do
    fact=$(( fact * i ))
  done
  echo "$n! = $fact"
}

if [[ -n "$1" ]]; then
  calc "$1"
else
  cat <<'MSG'
Script did not receive cmd-line input
MSG
  echo -n "Enter a number: "
  read n
  calc "$n"
fi
