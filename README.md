
# WOL : Web Optimized Language

## What is WOL ?

* WOL is a new language designed for the dynamic-web with the ambition to replace JS.
* WOL is inspired by Java, C++ and Python. Retro-compatibility is also a big concern in WOL to avoid breaking old website.
* WOL is designed to be memory efficient, natively compatible with the DOM and with a simple and clear Object Oriented syntax.
* WOL is a static and strong typed language to improve code security.
* WOL is designed to be more difficult than JS to avoid code-monkeys.

## Why using WOL ?

* Because JS sucks, everybody knows it.
* Because WOL is more secure than JS.
* Because WOL is faster than JS.
* Because WOL is more beautiful than JS.
* Because JS makes you a virgin and WOL makes you a chad.
* Because full OOP is better for big project.

## CPP_WOL : The native WOL interpreter

CPP_WOL is the native WOL interpreter written in C++, using CMake for building.
CPP_WOL benefits from Object Oriented C++ for code abstraction and low level C for performance.

## How to build / run ?

### For development :

* Run `cmake -DCMAKE_BUILD_TYPE=Debug`
* Run `make`
* Generated executable should be in `bin/dev/` directory
* You can use all WOL features (run `cpp_wol -h` to display help)
* You can run unit tests by typing `cpp_wol -tm -d`

### For production :

* Run `cmake -DCMAKE_BUILD_TYPE=Release`
* Run `make`
* Generated executable should be in `bin/prod/` directory
* Executable is more optimize than the dev one
* You can use all WOL production features (run `cpp_wol -h` to display help)