#!/bin/bash
BuildExe="nbuild"

if [ -f "$BuildExe" ]; then
  echo "Building project..."
  ./"$BuildExe"
else
  echo "Bootstraping build..."
  clang nob.c -o "$BuildExe"
  ./"$BuildExe"
fi