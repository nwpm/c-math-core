# CMathCore - Mathematical Core Library

**CMathCore** is a robust library designed to provide essential mathematical functions for physics simulations and graphics programming. Built with precision and extensibility in mind, it leverages C/C++ for performance-critical applications.

## Overview

This library aims to encapsulate a wide range of mathematical utilities, including:

- Linear algebra
- Numerical methods
- Specialized computations

It uses return codes (`CmStatusCode`) to track operation outcomes, ensuring robust error handling.

## Current Implementation

The following components are implemented and partially tested:

- **Matrix**: Supports matrix operations for linear algebra tasks.
- **BigInt**: Handles arbitrary-precision integer arithmetic.
- **Vectors**: Provides vector operations for 2D and 3D spaces (e.g., `vec2_double`, `vec3_double`).

## Future Development

Additional functionalities will be added progressively, including but not limited to:

- Complex number operations
- Geometry calculations
- Numerical optimizations
- Quaternions
- Sequences
- Statistical functions
- Special mathematical functions

## Usage

The library is structured with clear separation of source (`.c`) and header (`.h`) files, managed via Makefiles in each subdirectory. Integrate by including the relevant headers and linking against the compiled objects.

## Installation

Clone the repository and build the library using the provided Makefiles:

```bash
git clone https://github.com/yourusername/CMathCore.git
cd CMathCore
make
```

## Testing

Partial testing has been conducted on implemented features. Further test cases will be developed as the library expands.

## Contributing

Contributions are welcome. Ensure new features align with the library's design and include appropriate tests.

## License

See `LICENSE.md` for details.

