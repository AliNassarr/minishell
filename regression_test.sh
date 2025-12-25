#!/bin/bash

echo "=== Regression Tests ==="
echo ""

test_case() {
    local cmd="$1"
    local expected="$2"
    printf "Test: %s\n" "$cmd"
    result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep -v "^$" | head -1)
    printf "Expected: %s\n" "$expected"
    printf "Got:      %s\n" "$result"
    if [ "$result" = "$expected" ]; then
        echo "✓ PASS"
    else
        echo "✗ FAIL"
    fi
    echo ""
}

# Basic tests
test_case "echo hello world" "hello world"
test_case 'echo "hello world"' "hello world"
test_case "echo 'hello world'" "hello world"
test_case "echo a b c" "a b c"

# Quote tests
test_case 'echo "$USER"' "$USER"
test_case "echo '\$USER'" '\$USER'

# Pipes and redirects
printf "echo test | cat\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep "test" && echo "✓ Pipes work" || echo "✗ Pipes broken"

echo ""
echo "=== All regression tests complete ==="
