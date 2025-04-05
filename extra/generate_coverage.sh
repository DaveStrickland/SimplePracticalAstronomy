#!/bin/bash
#--------------------------------------------------------------------
#
# @brief Rerun CMake to enable code coverage, rebuild and run the test
#  executable, and generate a HTML file of the code coverage using
#  gcovr.
#
# bash generate_coverage.sh <build_dir>
#
#
# @history 2025-03-27 dks : Initial coding
#
#--------------------------------------------------------------------
#

p_usage="$0 <build_dir>"
if [ $# -ne 1 ]; then
    echo "Error, expecting 1 command line argument, got $#"
    echo "  usage: $p_usage"
    exit 1
fi

p_odir=$(pwd)
p_dir=$1
if [ ! -d $p_dir ]; then
    echo "Error, $p_dir is not a directory or an incomplete path."
    echo "  Current directory: $p_odir"
fi

cd $p_dir

echo "Removing old .gcno and .gcda files"
rm $(find . -name "*.gcno" -o -name "*.gcda" | xargs)

echo "Rebuilding make files"
cmake -D MY_PROFILING=ON ..

# Build and run
echo "Rebuilding SPA and the test executable"
make clean
make

# The compile generates .gcno files...
# ...now run the test executable.
echo "Running the test executable"
./spa_unit_test

# Use gcovr
p_cov=coverage.html
if [ -e $p_cov ]; then
    rm $p_cov
fi
gcovr -r ..  -e "/.*\/test\/.*" \
    -e "/.*\/inc\/GoodTimer.h" \
    --exclude-unreachable-branches \
    --html-details $p_cov
p_covfile=$(pwd)'/'$p_cov

echo "Generated coverage report $p_covfile"
echo "To view, run the following command: firefox file://$p_covfile"

#--------------------------------------------------------------------
#
exit 0
