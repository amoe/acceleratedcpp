#! /bin/sh

set -eu

path=$(mktemp -t quine-XXXXXXXX.cc)
exe=$(mktemp)

scons
./build/ex16_1 > "$path"
g++ -o "$exe" "$path" || echo "$path"

