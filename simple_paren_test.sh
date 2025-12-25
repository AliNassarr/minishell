#!/bin/bash

# Create test input file
echo 'echo (a)' > /tmp/test_input.txt
echo 'exit' >> /tmp/test_input.txt

# Run and capture output
./minishell < /tmp/test_input.txt 2>&1 | grep -E "^(a|\\(a\\))" | head -1

rm -f /tmp/test_input.txt
