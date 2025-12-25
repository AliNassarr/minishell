#!/bin/bash

echo "=== EXPORT MULTIPLE VARIABLES TEST ==="
echo ""

echo "Test 1: Export without values"
echo "Command: export a b c"
echo ""
(echo -e 'export a b c\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell) > /tmp/test1_mini.txt
bash -c 'export a b c; env | grep -E "^(a|b|c)="' > /tmp/test1_bash.txt
echo "Minishell output:"
cat /tmp/test1_mini.txt | grep -E "^(a|b|c)="
echo ""
echo "Expected (bash): Variables exist with empty values"
bash -c 'export a b c; env | grep -E "^(a|b|c)=" | wc -l'
./minishell -c 'export a b c; env | grep -E "^(a|b|c)=" | wc -l' 2>/dev/null || echo -e 'export a b c\nenv | grep -E "^(a|b|c)=" | wc -l\nexit' | ./minishell | grep -E "^[0-9]"
echo ""

echo "Test 2: Export with values"
echo "Command: export a=1 b=2 c=3"
echo ""
echo -e 'export a=1 b=2 c=3\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell | grep -E "^(a|b|c)="
echo ""

echo "Test 3: Check declare format"
echo "Command: export a b c; export"
echo ""
echo "Minishell:"
echo -e 'export a b c\nexport | grep -E "^declare -x (a|b|c)"\nexit' | ./minishell | grep -E "^declare"
echo ""
echo "Bash:"
bash -c 'export a b c; declare -p a b c'
echo ""

echo "=== ALL TESTS COMPLETE ==="
