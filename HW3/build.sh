#!/usr/bin/env bash
set -euo pipefail

# Configuration
CXX=${CXX:-g++}
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -pedantic"
OUT=program   # change to QueDr or desired exe name

# Targets: default = build
case "${1:-build}" in
  build)
    echo "Compiling all .cpp -> .o"
    for f in *.cpp; do
      echo "  $CXX -c $CXXFLAGS -o ${f%.cpp}.o $f"
      $CXX -c $CXXFLAGS -o "${f%.cpp}.o" "$f"
    done
    echo "Linking *.o -> $OUT"
    $CXX *.o -o "$OUT"
    echo "Built $OUT"
    ;;

  debug)
    echo "Debug build"
    DF="-g -O0"
    for f in *.cpp; do
      $CXX -c "$DF" -o "${f%.cpp}.o" "$f"
    done
    $CXX *.o -o "$OUT"
    ;;

  clcdean)
    echo "Cleaning"
    rm -f *.o "$OUT"
    ;;

  *)
    echo "Usage: $0 [build|debug|clean]"
    exit 1
    ;;
esac