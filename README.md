CMathCore
CMathCore is a C library designed for mathematical computations, providing robust support for vectors (2D and 3D), matrices, arbitrary-precision integers (BigInt). In future: complex, geometry, statistics, calculus, series. Built with performance, reliability, and portability in mind, CMathCore is ideal for applications in computer graphics, physics simulations, machine learning, and scientific computing. The library follows a modular design, employs explicit memory management, and uses status codes for error handling.

Installation
Prerequisites

C compiler (GCC, Clang, or equivalent).
Standard C libraries (<stdlib.h>, <string.h>, <math.h>).
Build system: make

Quick Start

Clone the repository:git clone https://github.com/yourusername/CMathCore.git
cd CMathCore


Build the library using make:make

(Optional) Install the library:make install


Building and Linking
To compile a program using CMathCore:
gcc -Ipath/to/CMathCore/src -c your_program.c -o your_program.o
gcc your_program.o -Lpath/to/CMathCore/lib -lmathcore -lm -o your_program

License
CMathCore is licensed under the MIT License.
