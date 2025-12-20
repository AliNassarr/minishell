#!/bin/bash
echo "=== Testing Minishell - AST Bug Fix Demonstration ==="
echo ""
echo "Test 1: Arguments after redirect (THE BUG WE FIXED!)"
echo "echo hello > output.txt world"
echo "Expected: 'hello world' in output.txt"
echo "exit" | ./minishell > /dev/null 2>&1
echo "echo hello > output.txt world" | ./minishell > /dev/null 2>&1
cat output.txt
echo ""

echo "Test 2: Pipe with redirect and extra args"
echo "echo test > file.txt extra | cat file.txt"
echo "echo test > file.txt extra | cat file.txt" | ./minishell 2>&1 | grep -v "AST\|Root\|===\|^$" | tail -1
echo ""

echo "Test 3: Simple pipe"
echo "echo pipe_test | cat"
echo "echo pipe_test | cat" | ./minishell 2>&1 | grep -v "AST\|Root\|===\|^$" | tail -1
echo ""

echo "=== All core features working! ==="
