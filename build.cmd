meson setup build
meson compile -C build
meson test -C build -v

.\build\rendercsv --help
