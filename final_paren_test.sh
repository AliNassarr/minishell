#!/bin/bash

echo "=== Parentheses Test Suite ==="
echo ""

test_case() {
    local cmd="$1"
    local expected="$2"
    printf "Test: %s\n" "$cmd"
    printf "Expected: %s\n" "$expected"
    result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep -v "^$" | head -1)
    printf "Got:      %s\n" "$result"
    if [ "$result" = "$expected" ]; then
        echo "✓ PASS"
    else
        echo "✗ FAIL"
    fi
    echo ""
}

test_case "echo (a)" "(a)"
test_case 'echo "(a)"' "(a)"
test_case "echo a(b)c" "a(b)c"
test_case "echo ( a )" "( a )"
test_case "echo ((nested))" "((nested))"
test_case "echo ()" "()"
test_case "echo ) (" ") ("

echo "=== All tests complete ==="
