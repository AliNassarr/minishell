#!/bin/bash

echo "=== Export Regression Tests ==="
echo ""

test_pass() {
    echo "✓ PASS: $1"
}

test_fail() {
    echo "✗ FAIL: $1"
}

# Test 1: Basic export with value
result=$(printf "export VAR=test\nenv | grep '^VAR='\nexit\n" | ./minishell 2>&1 | grep "^VAR=")
if [ "$result" = "VAR=test" ]; then
    test_pass "export VAR=value"
else
    test_fail "export VAR=value (got: $result)"
fi

# Test 2: Export and use in command
result=$(printf "export MYVAR=hello\necho \$MYVAR\nexit\n" | ./minishell 2>&1 | grep "hello")
if [ "$result" = "hello" ]; then
    test_pass "export and variable expansion"
else
    test_fail "export and variable expansion (got: $result)"
fi

# Test 3: Multiple exports with values
result=$(printf "export A=1 B=2 C=3\nenv | grep -E '^(A|B|C)=' | wc -l\nexit\n" | ./minishell 2>&1 | tail -1)
if [ "$result" = "3" ]; then
    test_pass "export A=1 B=2 C=3"
else
    test_fail "export A=1 B=2 C=3 (got $result vars)"
fi

# Test 4: Export existing variable
result=$(printf "A=test\nexport A\nenv | grep '^A='\nexit\n" | ./minishell 2>&1 | grep "^A=")
if [ "$result" = "A=test" ]; then
    test_pass "export existing variable"
else
    test_fail "export existing variable (got: $result)"
fi

# Test 5: Export with spaces in value (quoted)
result=$(printf 'export MSG="hello world"\nenv | grep "^MSG="\nexit\n' | ./minishell 2>&1 | grep "^MSG=")
if [ "$result" = 'MSG=hello world' ]; then
    test_pass "export with quoted value"
else
    test_fail "export with quoted value (got: $result)"
fi

# Test 6: Invalid identifier rejected
result=$(printf "export 123=test\nexit\n" | ./minishell 2>&1 | grep "not a valid identifier")
if [ -n "$result" ]; then
    test_pass "reject invalid identifier"
else
    test_fail "reject invalid identifier"
fi

echo ""
echo "=== All regression tests complete ==="
