# Build Instructions for SimplePracticalAstronomy

## Dependencies

- CMake (version 3 or above)
- C++11 compliant compiler, e.g. g++, clang.

## Build

```bash
cd build

# Create makefil
cmake ..

# Build
make clean
make all
```

## Test

```bash
# Assumes you are in the build/ directory already
./spa_unit_test
```
