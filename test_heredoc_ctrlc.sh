#!/bin/bash

echo "=== Testing Heredoc Ctrl-C Behavior ==="
echo ""

echo "Test 1: Simulating Ctrl-C during heredoc (via EOF on readline)"
echo "Expected: Exit status 130, no output from cat"
echo ""

# Create a script that simulates the heredoc interruption
# Since we can't actually send Ctrl-C in a script, we test the EOF behavior
# which should be handled by our signal check

echo "Minishell (EOF behavior):"
printf 'cat << EOF\n' | timeout 1 ./minishell 2>&1 | head -5
echo ""

echo "Test 2: Normal heredoc completion"
echo "Expected: Output 'test', exit status 0"
echo ""
printf 'cat << EOF\ntest\nEOF\necho $?\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^>" | head -5
echo ""

echo "Test 3: Checking that quoted delimiters still work"
printf 'cat << "EOF"\n$USER\nEOF\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^>" | head -5
echo ""

echo "=== Tests Complete ==="
