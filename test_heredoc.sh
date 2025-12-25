#!/bin/bash
echo "Test 1: Unquoted delimiter (should expand)"
./minishell << 'SHELL_END'
cat << EOF
$USER
