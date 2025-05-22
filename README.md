# SquareMat Project

## Overview

This project implements a `SquareMat` class in C++ to represent square matrices and provide full operator overloading for arithmetic, logical, and comparison operations. The implementation includes memory management, safety checks, and compliance with specified assignment requirements.

## Features

* Dynamic memory allocation for square matrices
* Deep copy constructor and assignment operator
* Operator overloading:

  * Arithmetic: `+`, `-`, `*`, `/`, `%`, and their compound versions `+=`, `-=`, etc.
  * Increment/Decrement: `++`, `--` (prefix and postfix)
  * Unary operators: `-`, `~` (transpose), `!` (determinant)
  * Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=` (based on sum of elements)
  * Power operator: `^` for matrix exponentiation
* Exception safety for invalid operations (e.g., size mismatch, division by zero)
* Stream output support via `operator<<`
* Utility functions:

  * `identity(int size)`: generates an identity matrix
  * `sum()`: returns the sum of all matrix elements
  * `getSize()`: returns the matrix dimension

## File Structure

* `SquareMat.hpp`: Header file containing the class interface
* `SquareMat.cpp`: Implementation of all methods and operators
* `test_SquareMat.cpp`: Unit tests using the Doctest framework
* `main.cpp`: Sample use case for the matrix class
* `Makefile`: Build script for compilation and testing

## Build Instructions

This project uses a simple Makefile. To build and run:

### Run main program:

```bash
make run
```

### Run unit tests:

```bash
make test
```

### Run memory checks with Valgrind:

```bash
make valgrind 
```

Make sure you have `doctest.h` available in your include path.

## Testing

The project uses the [Doctest](https://github.com/doctest/doctest) testing framework. The test suite covers:

* Basic operations
* Scalar interactions
* Compound assignments
* Copy and assignment behavior
* Increment/decrement correctness
* Error handling
* Matrix identity and power
* Transpose and negation

## Requirements Compliance

All operator behaviors comply with the assignment specification:

* Matrix equality is determined by **sum of elements**, not exact values.
* All mathematical operations are implemented using appropriate linear algebra definitions.
* Edge cases such as zero-size matrices and invalid input are handled gracefully.


