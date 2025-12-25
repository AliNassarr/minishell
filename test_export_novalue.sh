#!/bin/bash

echo "=== Export Without Value Test ==="
echo ""

echo "Test 1: export a b c (no values)"
printf "export a b c\nenv | grep -E '^(a|b|c)='\nexit\n" | ./minishell 2>&1 | grep -E "^(a|b|c)=" | wc -l
echo "Expected: 0 (no output)"

echo ""
echo "Test 2: export a= (explicit empty)"
printf "export a=\nenv | grep '^a='\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "Expected: a="

echo ""
echo "Test 3: export a=value"
printf "export a=hello\nenv | grep '^a='\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "Expected: a=hello"

echo ""
echo "Test 4: Mixed - export x y=1 z"
printf "export x y=1 z\nenv | grep -E '^(x|y|z)='\nexit\n" | ./minishell 2>&1 | grep -E "^(x|y|z)="
echo "Expected: only y=1"

echo ""
echo "=== Bash Comparison ==="
echo "Bash: export a b c"
bash -c 'export a b c; env | grep -E "^(a|b|c)=" | wc -l'
echo "Expected: 0"

echo ""
echo "Bash: export a="
bash -c 'export a=; env | grep "^a="'
echo "Expected: a="

