#!/bin/bash

# Number of tests
num_tests=500
num_integers=500

all_tests_passed=true
lines_printed=()
highest_line_count=0

for ((i=1; i<=$num_tests; i++)); do
    # Generate 500 unique random integers
    numbers=($(shuf -i 1-1000 -n $num_integers))

    # Convert the array to a space-separated string
    arg=$(IFS=" "; echo "${numbers[*]}")

	ps_output=$(./push_swap $arg)
	num_lines=$(echo "$ps_output" | wc -l)
    # Call push_swap and checker with the generated argument
    test_output=$(./push_swap $arg | ./checker $arg)

    # Check the result
    if [ "$test_output" != "OK" ]; then
        echo "Test $i Failed: push_swap output is not valid."
        all_tests_passed=false
    fi

    lines_printed+=($num_lines)

    if [ $num_lines -gt $highest_line_count ]; then
        highest_line_count=$num_lines
        hs_arg=$arg
    fi
    #echo "$highest_line_count"
done

total_lines=$(IFS=+; echo "$((${lines_printed[*]}))")
average_lines=$((total_lines / num_tests))

if $all_tests_passed; then
    echo "All tests passed: OK"
    echo "Average operation count: $average_lines"
    echo "Highest operation count: $highest_line_count"
    echo "$hs_arg"
else
    echo "Some tests failed: KO"
fi

