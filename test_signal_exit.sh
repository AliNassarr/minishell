#!/bin/bash

echo "=== Testing Pipeline Signal Exit Status ==="
echo ""

# Test 1: Normal exit
echo "Test 1: Normal pipeline exit"
printf "echo test | cat\necho \$?\nexit\n" | ./minishell 2>&1 | grep -A1 "echo test" | tail -1

# Test 2: Simulate SIGQUIT (we can't actually send it in test)
echo ""
echo "Test 2: Checking SIGQUIT handling (131 = 128 + 3)"
echo "Note: Manual test required with Ctrl-\\"

# Test 3: Check exit code propagation
echo ""
echo "Test 3: False command in pipeline"
printf "false | true\necho \$?\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | tail -1

echo ""
echo "=== Manual Test Instructions ==="
echo "Run: ./minishell"
echo "Type: sleep 5 | sleep 5 | sleep 5"
echo "Press: Ctrl-\\ (SIGQUIT)"
echo "Type: echo \$?"
echo "Expected: 131"
echo ""
echo "Then:"
echo "Type: sleep 5 | sleep 5 | sleep 5"
echo "Press: Ctrl-C (SIGINT)"
echo "Type: echo \$?"
echo "Expected: 130"
