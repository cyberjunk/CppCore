# AGENTS.md

## Projects

- `CppCore`: The main project, a header-only C++ library
- `CppCore.Debug`: An empty scratch project for debugging
- `CppCore.Test`: Unit Tests
- `CppCore.Interface.C`: Some functionality of `CppCore` wrapped in C compatible shared library
- `CppCore.Example.Server`: Example project for network server code
- `CppCore.Example.Client`: Example project for network client code
- `CppCore.Example.UI`: Example project for cross-platform UI code

## Building

Classic `make` Build System, see:

- File: `./Makefile`
- Folder: `./build/make/`

### Parameters

- `MODE`: Build debug or release
  - Valid: `debug`, `release`
  - Default: `debug`
- `TARGET_OS`: Build for this Operating System
  - Valid: `win`, `osx`, `linux`, `android`, `ios`, `wasi`
  - Default: Auto Detected Host OS
- `TARGET_ARCH`: Build for this CPU arch
  - Valid: `x86`, `x64`, `arm`, `arm64`, `wasm32`
  - Default: Auto Detected Host CPU Arch

### Rules

1) You must explicitly clean projects before rebuilding them.
2) Debug outputs have an additional `_d` suffix.

### Examples

- `make CppCore.Test` creates `./build/make/bin/osx-arm64/CppCore.Test_d` on MacOS ARM64
- `make CppCore.Test-clean` cleans `./build/make/bin/osx-arm64/CppCore.Test_d` on MacOS ARM64

## Tests

- Build and run the `CppCore.Test` project.
- Prints `0` and stops if a test fails.
- Prints `1` for each successful test.