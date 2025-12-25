#!/bin/bash

echo "=========================================="
echo "FINAL VALIDATION - ALL FIXES"
echo "=========================================="
echo ""

pass_count=0
fail_count=0

test_case() {
    local name="$1"
    local cmd="$2"
    local expected="$3"
    local check_type="$4"  # "exact" or "contains" or "not_contains"
    
    echo "Test: $name"
    result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -v minishell | grep -v exit | grep -v "^$" | tail -1)
    
    case "$check_type" in
        "exact")
            if [ "$result" = "$expected" ]; then
                echo "✓ PASS"
                ((pass_count++))
            else
                echo "✗ FAIL (expected: '$expected', got: '$result')"
                ((fail_count++))
            fi
            ;;
        "contains")
            if echo "$result" | grep -q "$expected"; then
                echo "✓ PASS"
                ((pass_count++))
            else
                echo "✗ FAIL (expected to contain: '$expected', got: '$result')"
                ((fail_count++))
            fi
            ;;
        "not_contains")
            if ! echo "$result" | grep -q "$expected"; then
                echo "✓ PASS"
                ((pass_count++))
            else
                echo "✗ FAIL (should NOT contain: '$expected', but got: '$result')"
                ((fail_count++))
            fi
            ;;
    esac
    echo ""
}

echo "=== PARENTHESES TESTS ==="
test_case "echo (a)" "echo (a)" "(a)" "exact"
test_case "echo a(b)c" "echo a(b)c" "a(b)c" "exact"
test_case "echo ( a )" "echo ( a )" "( a )" "exact"
test_case "echo ((nested))" "echo ((nested))" "((nested))" "exact"

echo "=== EXPORT WITHOUT VALUE TESTS ==="
# Test that export without = doesn't add to env
cmd="export testvar1 testvar2
env"
result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep -E "^(testvar1|testvar2)=" | wc -l)
echo "Test: export without value not in env"
if [ "$result" -eq 0 ]; then
    echo "✓ PASS"
    ((pass_count++))
else
    echo "✗ FAIL (found $result vars in env)"
    ((fail_count++))
fi
echo ""

# Test that export with = adds to env
cmd="export testvar3=
env"
result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep "^testvar3=")
echo "Test: export with = in env"
if [ -n "$result" ]; then
    echo "✓ PASS"
    ((pass_count++))
else
    echo "✗ FAIL (not found in env)"
    ((fail_count++))
fi
echo ""

# Test that export with value adds to env
cmd="export testvar4=hello
env"
result=$(printf "%s\nexit\n" "$cmd" | ./minishell 2>&1 | grep "^testvar4=hello")
echo "Test: export with value in env"
if [ -n "$result" ]; then
    echo "✓ PASS"
    ((pass_count++))
else
    echo "✗ FAIL (not found in env)"
    ((fail_count++))
fi
echo ""

echo "=== BASIC FUNCTIONALITY TESTS ==="
test_case "echo hello" "echo hello" "hello" "exact"
test_case "echo with spaces" "echo a b c" "a b c" "exact"
test_case "quoted string" 'echo "hello world"' "hello world" "exact"

echo "=========================================="
echo "RESULTS: $pass_count passed, $fail_count failed"
echo "=========================================="

if [ $fail_count -eq 0 ]; then
    echo "✓ ALL TESTS PASSED!"
    exit 0
else
    echo "✗ SOME TESTS FAILED"
    exit 1
fi
