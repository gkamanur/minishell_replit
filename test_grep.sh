#!/bin/bash

# First test with bash for reference
echo "=== Testing with bash ==="
bash -c 'cat minishell.h | grep ");"$' 2>bash_err.log
echo "Bash exit code: $?"
cat bash_err.log
echo

# Now test with minishell
echo "=== Testing with minishell ==="
echo 'cat minishell.h | grep ");"$' | ./minishell 2>mini_err.log
echo "Minishell exit code: $?"
cat mini_err.log
echo

# Test with a different quoting style to see if it helps
echo "=== Testing with minishell and different quoting ==="
echo "cat minishell.h | grep \");\$\"" | ./minishell 2>mini_err2.log
echo "Minishell exit code: $?"
cat mini_err2.log
