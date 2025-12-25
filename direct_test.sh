#!/bin/bash

echo "=== Direct Minishell Test ==="
echo ""

# Test with actual input
printf "echo (a)\nexit\n" | ./minishell 2>&1 | grep -A1 "echo (a)"

echo ""
echo "=== Testing if output contains parentheses ==="
OUTPUT=$(printf "echo (a)\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | tail -1)
echo "Output: [$OUTPUT]"

if [ "$OUTPUT" = "(a)" ]; then
    echo "✓ SUCCESS: Parentheses preserved!"
else
    echo "✗ FAIL: Expected '(a)', got '$OUTPUT'"
fi
