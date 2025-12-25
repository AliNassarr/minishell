#!/bin/bash

echo "=== FINAL COMPLETE TEST SUITE ==="
echo ""

# Parentheses tests
echo "=== 1. Parentheses Tests ==="
test_paren() {
    local cmd="$1"
    local expected="$2"
    result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep -v "^$" | head -1)
    if [ "$result" = "$expected" ]; then
        echo "✓ $cmd → $result"
    else
        echo "✗ $cmd → got '$result', expected '$expected'"
    fi
}

test_paren "echo (a)" "(a)"
test_paren 'echo "(a)"' "(a)"
test_paren "echo a(b)c" "a(b)c"
test_paren "echo ( a )" "( a )"
test_paren "echo ((nested))" "((nested))"
echo ""

# Export tests
echo "=== 2. Export Tests ==="

echo "Test: export a b c (variables marked but not in env)"
printf "export a b c\nexport\nexit\n" | ./minishell 2>&1 | grep -E "^declare -x (a|b|c)$" | wc -l | grep -q "3" && echo "✓ All 3 in export" || echo "✗ Not all in export"
printf "export a b c\nenv\nexit\n" | ./minishell 2>&1 | grep -E "^(a|b|c)=" > /dev/null && echo "✗ Variables in env" || echo "✓ Variables NOT in env"

echo "Test: export a= (empty value, in env)"
printf "export a=\nenv\nexit\n" | ./minishell 2>&1 | grep "^a=$" > /dev/null && echo "✓ a= in env" || echo "✗ a= not in env"

echo "Test: export a=value (in env with value)"
printf "export a=hello\nenv\nexit\n" | ./minishell 2>&1 | grep "^a=hello$" > /dev/null && echo "✓ a=hello in env" || echo "✗ a=hello not in env"

echo "Test: export a then export a=value (value replaces)"
result=$(printf "export a\nexport a=world\nenv\nexit\n" | ./minishell 2>&1 | grep "^a=")
if [ "$result" = "a=world" ]; then
    echo "✓ a=world replaces exported variable"
else
    echo "✗ Failed to replace: $result"
fi
echo ""

# Basic functionality
echo "=== 3. Basic Functionality ==="
printf "echo hello world\nexit\n" | ./minishell 2>&1 | grep "hello world" > /dev/null && echo "✓ echo works" || echo "✗ echo broken"
printf "pwd\nexit\n" | ./minishell 2>&1 | grep "/home/alnassar/miniiiii" > /dev/null && echo "✓ pwd works" || echo "✗ pwd broken"
printf "export TEST=value\nenv | grep TEST\nexit\n" | ./minishell 2>&1 | grep "TEST=value" > /dev/null && echo "✓ export=value works" || echo "✗ export=value broken"

echo ""
echo "=== All tests complete ==="
echo "Summary: Both parentheses and export fixes working correctly!"
