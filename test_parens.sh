#!/bin/bash
echo "=== Test 1: echo (a) ==="
echo "(a)" | ./minishell 2>&1 | grep -A1 "minishell>"

echo ""
echo "=== Test 2: Bash behavior ==="
bash -c 'echo (a)'
