#!/bin/bash

echo "=== EXPORT PARENTHESES VALIDATION TEST ==="
echo ""

echo "Test 1: export a() b"
echo "Expected: Error for a(), b should be exported"
echo ""
echo "Minishell:"
echo -e 'export a() b\nenv | grep -E "^(a|b)="\nexit' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 2: export x=1 y() z=3"
echo "Expected: x=1 exported, error for y(), z=3 exported"
echo ""
echo "Minishell:"
echo -e 'export x=1 y() z=3\nenv | grep -E "^(x|y|z)="\nexit' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 3: export func()"
echo "Expected: Error, nothing exported"
echo ""
echo "Minishell:"
echo -e 'export func()\nenv | grep "^func"\nexit' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 4: export valid_var test() another_var"
echo "Expected: valid_var and another_var exported, error for test()"
echo ""
echo "Minishell:"
echo -e 'export valid_var test() another_var\nenv | grep -E "^(valid_var|test|another_var)="\nexit' | ./minishell 2>&1 | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Test 5: Verify bash compatibility"
echo "Bash:"
bash -c 'export "a()" b 2>&1' | head -1
bash -c 'export "a()" b 2>&1; env | grep -E "^b=" | wc -l' 2>/dev/null
echo ""

echo "=== ALL TESTS COMPLETE ==="
