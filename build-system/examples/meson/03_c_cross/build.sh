#!/bin/sh

rm -rf build
meson build . --cross meson_cross.ini
ninja -C build
./build/demo
