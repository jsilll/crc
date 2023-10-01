#!/bin/bash

# Check if the binary is provided as an argument
if [ $# -ne 1 ]; then
    echo "Usage: ./test.sh <binary>"
    exit 1
fi

# Check if the binary exists
if [ ! -f $1 ]; then
    echo "Binary '$1' does not exist"
    exit 1
fi

# Check if the binary is executable
if [ ! -x $1 ]; then
    echo "Binary '$1' is not executable"
    exit 1
fi

# Check if the test directory exists
if [ ! -d tests ]; then
    echo "Test directory 'tests' does not exist"
    exit 1
fi

# Check if the test directory is empty
if [ -z "$(ls -A tests)" ]; then
    echo "Test directory 'tests' is empty"
    exit 1
fi

# Check if the input directory exists
if [ ! -d tests/input ]; then
    echo "Input directory 'tests/input' does not exist"
    exit 1
fi

# Check if the output directory exists
if [ ! -d tests/output ]; then
    echo "Output directory 'tests/output' does not exist"
    exit 1
fi

# Check if the input directory is empty
if [ -z "$(ls -A tests/input)" ]; then
    echo "Input directory 'tests/input' is empty"
    exit 1
fi

# Check if the output directory is empty
if [ -z "$(ls -A tests/output)" ]; then
    echo "Output directory 'tests/output' is empty"
    exit 1
fi

# Start testing
for out in tests/output/*; do
    # Get the name of the test case
    test_case_name=$(basename $out .out)

    # Output file format: <graph_name>-<k>.out
    k=$(echo $test_case_name | cut -d '-' -f 2)
    graph_name=$(echo $test_case_name | cut -d '-' -f 1)

    # Get the input file
    in=tests/input/$graph_name.graph

    # Run the binary and write the output to a file
    output=$(mktemp)
    $1 $in $k > $output

    # Exit if the binary does not exit with status 0
    if [ $? -ne 0 ]; then
        echo "Binary '$1' exited with status $? for test case '$test_case_name'"
        exit 1
    fi

    # Print the name of the test case
    echo -n "$test_case_name: "

    # Check if the output is correct with diff command
    if diff -q $out $output > /dev/null; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mWRONG\e[0m"
    fi
done