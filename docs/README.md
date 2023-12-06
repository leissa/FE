# FE

[![docs](https://img.shields.io/github/actions/workflow/status/leissa/fe/doxygen.yml?logo=gitbook&logoColor=white&label=docs&link=https%3A%2F%2Fleissa.github.io%2Ffe%2F&link=https%3A%2F%2Fgithub.com%2Fleissa%2Ffe%2Factions%2Fworkflows%2Fdoxygen.yml)](https://github.com/leissa/fe/actions/workflows/doxygen.yml)
[![linux](https://img.shields.io/github/actions/workflow/status/leissa/fe/linux.yml?logo=linux&logoColor=white&label=linux&link=https%3A%2F%2Fgithub.com%2Fleissa%2Ffe%2Factions%2Fworkflows%2Flinux.yml)](https://github.com/leissa/fe/actions/workflows/linux.yml)
[![macos](https://img.shields.io/github/actions/workflow/status/leissa/fe/macos.yml?logo=apple&logoColor=white&label=macos&link=https%3A%2F%2Fgithub.com%2Fleissa%2Ffe%2Factions%2Fworkflows%2Fmacos.yml)](https://github.com/leissa/fe/actions/workflows/macos.yml)
[![windows](https://img.shields.io/github/actions/workflow/status/leissa/fe/windows.yml?logo=windows&logoColor=white&label=windows&link=https%3A%2F%2Fgithub.com%2Fleissa%2Ffe%2Factions%2Fworkflows%2Fwindows.yml)](https://github.com/leissa/fe/actions/workflows/windows.yml)

A header-only C++ library for writing compiler/interpreter frontends.

## What is FE?

FE provides a set of utilities that helps you writing your own compiler or interpreter frontend.
FE is **not** a lexer or parser generator.
Instead, it will give you the blueprint to easily hand-write your own lexer and parser.

## Get Started Now!

Based on the toy language *[Let](https://github.com/leissa/let)*, either
* create a [new repository from a template](https://github.com/new?template_owner=leissa&template_name=let), or
* [fork](https://github.com/leissa/let/fork) it.

## Features

* [Arena](@ref fe::Arena) allocator for efficient memory management.
* Efficient [symbol pool](@ref fe::SymPool) with optional [Abseil](https://abseil.io/) support.
    [String](@ref fe::Sym) comparisons are now only pointer comparisons!
* Keep track of [source code locations](@ref fe::Loc).
* Blueprint for a [lexer](@ref fe::Lexer) with [UTF-8](@ref fe::utf8) support.
* Blueprint for a [parser](@ref fe::Parser).
* You need at least C++-20.

## Building

FE optionally supports [Abseil](https://abseil.io/)'s excellent [hash containers](https://abseil.io/docs/cpp/guides/container).
In order to enable Abseil support, you have to define `FE_ABSL`.
Otherwise, FE will fall back to the hash containers of the C++ standard library.

### Option #1: Include FE as Submodule (Recommended)

1. Add FE as external submodule to your compiler project:
    * If your compiler project is already on GitHub, do this:
        ```sh
        git submodule add ../../leissa/fe external/fe
        ```
    * Otherwise:
        ```sh
        git submodule add git@github.com:leissa/fe.git external/fe
        ```

2. Integrate into your build system:
    * If you use CMake, add something like this to your `CMakeLists.txt`:
        ```cmake
        set(FE_ABSL ON) # remove this line, if you don't want to use Abseil
        add_subdirectory(external/fe)

        target_link_libraries(my_compiler PUBLIC fe)
        ```
    * Otherwise:
        * Add `external/fe/include` as include directory.
        * Furthermore, add `-DFE_ABSL` to your `CXXFLAGS`, if you want to use Abseil.

### Option #2: Directly include FE in your Source Tree

1. Copy over the headers from FE to your compiler project:
    ```sh
    git clone git@github.com:leissa/fe.git
    mkdir -p my_compiler/include/fe
    cp -r fe/include/fe/*.h my_compiler/include/fe
    ```

2. Integrate into your build system:

    Since your build system most likely already has `my_compiler/include/` as an include directory, nothing more needs to be done.
    In addition, add `-DFE_ABSL` to your `CXXFLAGS`, if you want to use Abseil.
    In the case of CMake, add something like this to your `CMakeLists.txt`:
    ```cmake
    target_compile_definitions(my_compiler PUBLIC FE_ABSL)
    ```
## Other Projects using FE

* [Let](https://github.com/leissa/let): A simple demo language that builds upon FE
* [GraphTool](https://github.com/leissa/graphtool): A small tool that reads a subset from Graphviz' DOT language and calculates several dominance-related properties
* [SQL](https://github.com/leissa/sql): Small and simple SQL parser
* [Thorin2](https://anydsl.github.io/thorin2/): The Higher-ORder INtermediate representation
