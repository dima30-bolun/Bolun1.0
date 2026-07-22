#!/bin/sh
set -eu
mkdir -p build apps services platform docs scripts shell assets resources configs Luna
for d in Luna build scripts shell apps assets resources services configs platform docs; do test -d "$d"; done
test -f CMakeLists.txt
test -f assets/svg/luna.svg
test ! -f assets/png/luna.png
test -f resources/i18n/en.properties
test -f resources/i18n/ru.properties
test -f Luna/assets/AssetGenerator.cpp
