#!/bin/bash

echo "=== FINAL VALIDATION: Parentheses Support ==="
echo ""

pass=0
fail=0

test_case() {
    local cmd="$1"
    local expected="$2"
    result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep -v "^$" | head -1)
    if [ "$result" = "$expected" ]; then
        ((pass++))
        echo "✓ $cmd"
    else
        ((fail++))
        echo "✗ $cmd - Expected: '$expected', Got: '$result'"
    fi
}

echo "Parentheses as literal characters:"
test_case "echo (a)" "(a)"
test_case "echo a(b)c" "a(b)c"
test_case "echo ( a )" "( a )"
test_case "echo ()" "()"
test_case "echo ) (" ") ("
test_case "echo ((nested))" "((nested))"

echo ""
echo "Quoted parentheses:"
test_case 'echo "(a)"' "(a)"
test_case "echo '(a)'" "(a)"

echo ""
echo "Mixed with other features:"
test_case "echo hello (world)" "hello (world)"
test_case "echo a b (c) d" "a b (c) d"

echo ""
echo "Regression tests:"
test_case "echo hello world" "hello world"
test_case 'echo "hello world"' "hello world"
test_case "echo a b c" "a b c"

echo ""
echo "=== RESULTS ==="
echo "Passed: $pass"
echo "Failed: $fail"

if [ $fail -eq 0 ]; then
    echo ""
    echo "🎉 ALL TESTS PASSED! Parentheses are properly treated as literal characters."
    exit 0
else
    echo ""
    echo "❌ Some tests failed."
    exit 1
fi
