#!/bin/bash

echo "════════════════════════════════════════════════════════════════════════"
echo "              MINISHELL COMPREHENSIVE FINAL TEST"
echo "════════════════════════════════════════════════════════════════════════"
echo ""

PASS=0
FAIL=0

test_case() {
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "Test: $1"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
}

check_result() {
    if [ "$1" -eq 0 ]; then
        echo "✅ PASS"
        ((PASS++))
    else
        echo "❌ FAIL"
        ((FAIL++))
    fi
    echo ""
}

# Test 1: Export multiple variables
test_case "Export multiple variables (export a b c)"
RESULT=$(printf 'export a b c\nenv | grep -E "^(a|b|c)=" | wc -l\nexit\n' | ./minishell 2>&1 | grep "^3$")
[ -n "$RESULT" ]
check_result $?

# Test 2: Export with values
test_case "Export with values (export x=1 y=2 z=3)"
RESULT=$(printf 'export x=1 y=2 z=3\nenv | grep -E "^(x|y|z)=" | wc -l\nexit\n' | ./minishell 2>&1 | grep "^3$")
[ -n "$RESULT" ]
check_result $?

# Test 3: Export rejects parentheses
test_case "Export rejects parentheses (export a() b)"
RESULT=$(printf 'export a() b\nenv | grep "^b="\nexit\n' | ./minishell 2>&1 | grep "b=")
[ -n "$RESULT" ]
check_result $?

# Test 4: Heredoc with quoted delimiter (no expansion)
test_case "Heredoc quoted delimiter - no expansion (cat << \"EOF\")"
RESULT=$(printf 'cat << "EOF"\n$USER\nEOF\nexit\n' | ./minishell 2>&1 | grep '^\$USER$')
[ -n "$RESULT" ]
check_result $?

# Test 5: Heredoc with unquoted delimiter (expansion)
test_case "Heredoc unquoted delimiter - expansion (cat << EOF)"
RESULT=$(printf 'cat << EOF\n$USER\nEOF\nexit\n' | ./minishell 2>&1 | grep "^$USER$")
[ -n "$RESULT" ]
check_result $?

# Test 6: Export display format
test_case "Export display format (declare -x)"
RESULT=$(printf 'export TEST=value\nexport | grep "declare -x TEST"\nexit\n' | ./minishell 2>&1 | grep 'declare -x TEST')
[ -n "$RESULT" ]
check_result $?

# Test 7: Compilation check
test_case "No forbidden functions in code"
RESULT=$(grep -r "fprintf\|memset\|strncmp\|strtok\|sprintf" --include="*.c" --include="*.h" | grep -v "ft_" | grep -v "//" | grep -v "Binary" | wc -l)
[ "$RESULT" -eq 0 ]
check_result $?

# Test 8: Norminette compliance
test_case "Norminette compliance"
make re > /dev/null 2>&1
norminette **/*.c **/*.h > /tmp/norm_result.txt 2>&1
ERRORS=$(grep "Error" /tmp/norm_result.txt | wc -l)
[ "$ERRORS" -eq 0 ]
check_result $?

# Test 9: Basic command execution
test_case "Basic command execution (echo test)"
RESULT=$(printf 'echo test\nexit\n' | ./minishell 2>&1 | grep "^test$")
[ -n "$RESULT" ]
check_result $?

# Test 10: PWD builtin
test_case "PWD builtin"
RESULT=$(printf 'pwd\nexit\n' | ./minishell 2>&1 | grep "$(pwd)")
[ -n "$RESULT" ]
check_result $?

echo "════════════════════════════════════════════════════════════════════════"
echo "                          TEST RESULTS"
echo "════════════════════════════════════════════════════════════════════════"
echo ""
echo "✅ PASSED: $PASS"
echo "❌ FAILED: $FAIL"
echo ""

if [ "$FAIL" -eq 0 ]; then
    echo "🎉 ALL TESTS PASSED! PROJECT READY FOR SUBMISSION!"
else
    echo "⚠️  Some tests failed. Please review the output above."
fi

echo ""
echo "════════════════════════════════════════════════════════════════════════"
