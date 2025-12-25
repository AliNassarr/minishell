#!/bin/bash

echo "=== COMPREHENSIVE PARENTHESES TEST ==="
echo ""

echo "Test 1: export a() b"
printf 'export a() b\nenv | grep -E "^(a|b)="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | head -5

echo ""
echo "Test 2: export 'a()' b"
printf 'export '\''a()'\'' b\nenv | grep -E "^(a|b)="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | head -5

echo ""
echo "Test 3: export x=1 y() z=3"
printf 'export x=1 y() z=3\nenv | grep -E "^(x|y|z)="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | head -5

echo ""
echo "Test 4: export ')' test"
printf 'export '\'''\'''\'' test\nenv | grep -E "^(test|\\))="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | head -5

echo ""
echo "Test 5: export '(' test"  
printf 'export '\''('\'' test\nenv | grep -E "^(test|\\()="\nexit\n' | ./minishell 2>&1 | grep -v "minishell\$" | head -5

echo ""
echo "=== END ===" 
