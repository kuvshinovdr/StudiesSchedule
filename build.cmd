meson setup build
meson compile -C build
.\build\studiesschedule --help

meson test -C build -v
