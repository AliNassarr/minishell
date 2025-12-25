#!/bin/bash

echo "=== Export Parentheses Validation ==="
echo ""

echo "Test 1: export a() b"
printf 'export a() b\nenv | grep -E "^(a|b)="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 2: export x=1 y() z=3"
printf 'export x=1 y() z=3\nenv | grep -E "^(x|y|z)="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 3: export func()"
printf 'export func()\nenv | grep "^func"\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 4: export test(var)"
printf 'export test(var)\nenv | grep "^test"\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 5: export a()=value"
printf 'export a()=value\nenv | grep "^a"\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "All tests complete!"
