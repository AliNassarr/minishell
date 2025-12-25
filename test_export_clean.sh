#!/bin/bash

echo "=== Clean Export Tests ==="
echo ""

# Test 1: export without value doesn't appear in env
echo "Test 1: export a b c"
printf "export a b c\nenv\nexit\n" | ./minishell 2>&1 | grep -v minishell | grep -v exit | grep -E "^(a|b|c)="
count=$(printf "export a b c\nenv\nexit\n" | ./minishell 2>&1 | grep -v minishell | grep -v exit | grep -E "^(a|b|c)=" | wc -l)
if [ "$count" -eq 0 ]; then
    echo "✓ PASS: No variables in env"
else
    echo "✗ FAIL: Found $count variables in env"
fi
echo ""

# Test 2: export with empty value appears in env
echo "Test 2: export x="
printf "export x=\nenv\nexit\n" | ./minishell 2>&1 | grep "^x="
if [ $? -eq 0 ]; then
    echo "✓ PASS: x= found in env"
else
    echo "✗ FAIL: x= not found in env"
fi
echo ""

# Test 3: export with value appears in env
echo "Test 3: export y=hello"
printf "export y=hello\nenv\nexit\n" | ./minishell 2>&1 | grep "^y="
if [ $? -eq 0 ]; then
    echo "✓ PASS: y=hello found in env"
else
    echo "✗ FAIL: y=hello not found in env"
fi
echo ""

# Test 4: Variable expansion still works
echo "Test 4: Variable expansion"
output=$(printf "export TEST=world\necho \$TEST\nexit\n" | ./minishell 2>&1 | grep -v minishell | grep -v exit | tail -1)
if [ "$output" = "world" ]; then
    echo "✓ PASS: Expansion works"
else
    echo "✗ FAIL: Expected 'world', got '$output'"
fi
echo ""

# Test 5: Export existing variable
echo "Test 5: A=test; export A"
result=$(printf "A=test\nexport A\nenv\nexit\n" | ./minishell 2>&1 | grep "^A=test")
if [ -n "$result" ]; then
    echo "✓ PASS: Existing variable exported"
else
    echo "✗ FAIL: Existing variable not in env"
fi

echo ""
echo "=== All tests complete ==="
