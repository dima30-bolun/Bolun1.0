# Luna

Luna is an original C++20, CMake, Qt6/QML desktop shell project for Ubuntu Linux with a modular MVVM-ready service architecture. The current tree contains working native services, custom `.ben`, `.bapp` and `.luna` format support, a runtime, SDK builder, a control utility, resources, localization files, generated binary assets and a Qt6 shell target that is enabled automatically when Qt6 is installed.

## Build

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

PNG icons are generated inside `build/generated-assets` and are not committed as binary repository files.

If Qt6 Core, Gui, Qml and Quick are present, the `luna-shell` Wayland/X11 QML shell is built. Without Qt6, the native runtime, SDK and service tests still build so the project remains verifiable on minimal Ubuntu images.
