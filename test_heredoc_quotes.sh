#!/bin/bash

echo "=== Testing Heredoc with Quoted Delimiter ==="
echo ""

echo "Test 1: Quoted delimiter (should NOT expand)"
echo 'Command: cat << "EOF"'
echo ""

printf 'cat << "EOF"\n$USER\n$HOME\nEOF\nexit\n' | ./minishell > /tmp/mini_quoted.txt 2>&1
echo "Minishell output:"
cat /tmp/mini_quoted.txt | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Expected (bash):"
bash << 'BASH_TEST'
cat << "EOF"
$USER
$HOME
EOF
BASH_TEST
echo ""

echo "Test 2: Unquoted delimiter (SHOULD expand)"
echo 'Command: cat << EOF'
echo ""

printf 'cat << EOF\n$USER\n$HOME\nEOF\nexit\n' | ./minishell > /tmp/mini_unquoted.txt 2>&1
echo "Minishell output:"
cat /tmp/mini_unquoted.txt | grep -v "minishell\$" | grep -v "^exit$"
echo ""

echo "Expected (bash):"
bash << 'BASH_TEST'
cat << EOF
$USER
$HOME
EOF
BASH_TEST

