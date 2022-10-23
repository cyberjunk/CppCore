# Building

## Development

* [Visual Studio Code](https://code.visualstudio.com/) (Windows, Linux, OSX)
* [Visual Studio](https://visualstudio.microsoft.com/vs/) (Windows)

Open [CppCore.sln](https://github.com/cyberjunk/cppcore/blob/master/CppCore.sln) in Visual Studio or open the repository root folder in Visual Studio Code.

## Compilers

* CLANG (Windows, Linux, MacOS, Android, iOS)
* MSVC (Windows)

## GNU Make / Visual Studio Code

### Windows

* Download [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
* Download [LLVM for Windows](https://github.com/llvm/llvm-project/releases)
* Make sure to select "add to path" during both installations

### Linux

```
sudo apt-get install make clang lld llvm
```

### OSX

Install from the OSX Store:

* XCode
* XCode Command Line Tools

### Make Parameters

Following Parameters are supported. Defaults will be used if not provided.

| Parameter   | Values                        | Default    |
| ----------- | ----------------------------- | ---------- |
| MODE        | debug, release                | debug      |
| TARGET_OS   | win, osx, linux, android, ios | {host-os}  |
| TARGET_ARCH | x86, x64, arm, arm64          | {host-cpu} |
