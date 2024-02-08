#!/bin/bash

PROGRAM="/home/fleurs/CLionProjects/bmstu_cpp_work/cmake-build-debug/let_9/let_9"

test_number() {
    local number=$1
    local expected=$2
    result=$($PROGRAM "$number"; echo $?)
    if [ "$result" -eq "$expected" ]; then
        echo "Test passed for number $number: Expected exit code $expected, got $result"
    else
        echo "Test failed for number $number: Expected exit code $expected, got $result"
        exit 1
    fi
}

test_cases=(
"6 0"
"28 0"
"496 0"
"8128 0"
"5 1"
"10 1"
)

for test_case in "${test_cases[@]}"; do
    IFS=' ' read -r number expected_result <<< "$test_case"
    test_number $number $expected_result
done

echo "All tests passed!"
