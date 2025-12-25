#!/bin/bash

echo "=== Complete Export Test Suite ==="
echo ""

# Test 1: export without value
echo "Test 1: export a b c (no values)"
printf "export a b c\nexport\nexit\n" | ./minishell 2>&1 | grep -E "^declare -x (a|b|c)$"
echo "✓ Should show: declare -x a, declare -x b, declare -x c"
echo ""

printf "export a b c\nenv\nexit\n" | ./minishell 2>&1 | grep -E "^(a|b|c)="
result=$?
if [ $result -eq 1 ]; then
    echo "✓ PASS: Variables NOT in env (as expected)"
else
    echo "✗ FAIL: Variables appeared in env"
fi
echo ""

# Test 2: export with empty value
echo "Test 2: export a="
printf "export a=\nenv\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "✓ Should show: a="
echo ""

# Test 3: export with value
echo "Test 3: export a=hello"
printf "export a=hello\nenv\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "✓ Should show: a=hello"
echo ""

# Test 4: export then assign value
echo "Test 4: export a, then export a=world"
printf "export a\nexport a=world\nenv\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "✓ Should show: a=world"
echo ""

# Test 5: Bash comparison
echo "=== Bash Comparison ==="
echo "Bash: export xyz (not in env)"
export xyz
env | grep "^xyz=" || echo "✓ Not in env (correct)"
unset xyz

echo ""
echo "Bash: export xyz= (in env with empty value)"
export xyz=
env | grep "^xyz="
unset xyz

echo ""
echo "=== All tests complete ==="
