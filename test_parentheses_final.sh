#!/bin/bash

echo "=== Parentheses Test Suite ==="
echo ""

echo "Test 1: echo (a)"
echo "Expected: (a)"
echo -n "Result:   "
echo "echo (a)" | ./minishell 2>&1 | grep -v "minishell>" | grep -v "exit" | head -1

echo ""
echo "Test 2: echo \"(a)\""
echo "Expected: (a)"
echo -n "Result:   "
echo 'echo "(a)"' | ./minishell 2>&1 | grep -v "minishell>" | grep -v "exit" | head -1

echo ""
echo "Test 3: echo a(b)c"
echo "Expected: a(b)c"
echo -n "Result:   "
echo "echo a(b)c" | ./minishell 2>&1 | grep -v "minishell>" | grep -v "exit" | head -1

echo ""
echo "Test 4: echo ( a )"
echo "Expected: ( a )"
echo -n "Result:   "
echo "echo ( a )" | ./minishell 2>&1 | grep -v "minishell>" | grep -v "exit" | head -1

echo ""
echo "Test 5: echo ((nested))"
echo "Expected: ((nested))"
echo -n "Result:   "
echo "echo ((nested))" | ./minishell 2>&1 | grep -v "minishell>" | grep -v "exit" | head -1

echo ""
echo "=== Bash Comparison ==="
echo ""
echo "Bash: echo (a) => $(bash -c 'echo (a)')"
echo "Bash: echo \"(a)\" => $(bash -c 'echo "(a)"')"
echo "Bash: echo a(b)c => $(bash -c 'echo a(b)c')"
echo "Bash: echo ( a ) => $(bash -c 'echo ( a )')"
echo "Bash: echo ((nested)) => $(bash -c 'echo ((nested))')"
