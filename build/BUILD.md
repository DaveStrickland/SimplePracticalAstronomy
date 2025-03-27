# Build Instructions for SimplePracticalAstronomy

## Dependencies

- CMake (version 3 or above)
- C++11 compliant compiler, e.g. g++, clang.

## Build

```bash
# Assumes you're in the SimplePracticalAstronomy directory.
cd build

# Create Makefile
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

### Test Coverage

Test coverage reporting requires `govr`. To generate and visualize test coverage
follow the example:

```bash
cd build/
cmake -D MY_PROFILING=ON ..

# Build and run
make
# The compile generates .gcno files...
# ...now run the test executable.
./spa_unit_test

# Use gcovr
gcovr -r .. --html-details coverage.html
firefox file://$(pwd)/coverage.html
```