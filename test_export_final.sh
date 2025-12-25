#!/bin/bash

echo "=== Export Variable Tracking Test ==="
echo ""

test_case() {
    local desc="$1"
    local cmd="$2"
    local check_cmd="$3"
    local expected="$4"
    
    echo "Test: $desc"
    echo "Command: $cmd"
    result=$(printf "%s\n%s\nexit\n" "$cmd" "$check_cmd" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep -v "^$" | tail -1)
    echo "Expected: $expected"
    echo "Got: $result"
    if [ "$result" = "$expected" ]; then
        echo "✓ PASS"
    else
        echo "✗ FAIL"
    fi
    echo ""
}

# Test 1: export a b c - should appear in export, not in env
echo "=== Test 1: export a b c ==="
printf "export a b c\nexport | grep -E '^declare -x (a|b|c)$'\nexit\n" | ./minishell 2>&1 | grep "declare -x" | wc -l
echo "Expected: 3 lines"
echo ""

printf "export a b c\nenv | grep -E '^(a|b|c)='\nexit\n" | ./minishell 2>&1 | grep -E "^(a|b|c)=" | wc -l
echo "Expected: 0 lines"
echo ""

# Test 2: export a= - should appear in both
echo "=== Test 2: export a= ==="
printf "export a=\nexport | grep '^declare -x a'\nexit\n" | ./minishell 2>&1 | grep "declare -x a"
echo "Expected: declare -x a=\"\""
echo ""

printf "export a=\nenv | grep '^a='\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "Expected: a="
echo ""

# Test 3: export a=value
echo "=== Test 3: export a=value ==="
printf "export a=hello\nexport | grep '^declare -x a'\nexit\n" | ./minishell 2>&1 | grep "declare -x a"
echo "Expected: declare -x a=\"hello\""
echo ""

printf "export a=hello\nenv | grep '^a='\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "Expected: a=hello"
echo ""

# Test 4: export a, then export a=value
echo "=== Test 4: export a, then export a=value ==="
printf "export a\nexport a=world\nenv | grep '^a='\nexit\n" | ./minishell 2>&1 | grep "^a="
echo "Expected: a=world"
echo ""

echo "=== All tests complete ==="
