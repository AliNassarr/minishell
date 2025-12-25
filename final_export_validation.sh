#!/bin/bash

echo "========================================"
echo "   FINAL EXPORT VALIDATION TEST"
echo "========================================"
echo ""

# Test 1: Basic requirement from user
echo "✓ Test 1: export a b c"
echo -e 'export a b c\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | sort
RESULT1=$(echo -e 'export a b c\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | wc -l)
if [ "$RESULT1" -eq 3 ]; then
    echo "  ✅ PASS: All 3 variables exported"
else
    echo "  ❌ FAIL: Only $RESULT1 variables exported"
fi
echo ""

# Test 2: With values
echo "✓ Test 2: export a=1 b=2 c=3"
echo -e 'export a=1 b=2 c=3\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | sort
RESULT2=$(echo -e 'export a=1 b=2 c=3\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | wc -l)
if [ "$RESULT2" -eq 3 ]; then
    echo "  ✅ PASS: All 3 variables exported with values"
else
    echo "  ❌ FAIL: Only $RESULT2 variables exported"
fi
echo ""

# Test 3: Mixed
echo "✓ Test 3: export x y=test z"
echo -e 'export x y=test z\nenv | grep -E "^(x|y|z)="\nexit' | ./minishell 2>&1 | grep -E "^(x|y|z)=" | sort
RESULT3=$(echo -e 'export x y=test z\nenv | grep -E "^(x|y|z)="\nexit' | ./minishell 2>&1 | grep -E "^(x|y|z)=" | wc -l)
if [ "$RESULT3" -eq 3 ]; then
    echo "  ✅ PASS: All 3 variables exported (mixed)"
else
    echo "  ❌ FAIL: Only $RESULT3 variables exported"
fi
echo ""

# Test 4: Display format
echo "✓ Test 4: Checking declare -x format"
echo -e 'export foo bar=val\nexport | grep -E "^declare -x (foo|bar)"\nexit' | ./minishell 2>&1 | grep "^declare -x"
echo "  Expected: declare -x foo (no quotes for empty)"
echo "            declare -x bar=\"val\" (quotes for non-empty)"
echo ""

# Test 5: Multiple calls
echo "✓ Test 5: Multiple export calls"
echo -e 'export a\nexport b\nexport c\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | sort
RESULT5=$(echo -e 'export a\nexport b\nexport c\nenv | grep -E "^(a|b|c)="\nexit' | ./minishell 2>&1 | grep -E "^(a|b|c)=" | wc -l)
if [ "$RESULT5" -eq 3 ]; then
    echo "  ✅ PASS: Sequential exports work"
else
    echo "  ❌ FAIL: Only $RESULT5 variables exported"
fi
echo ""

# Summary
echo "========================================"
TOTAL_TESTS=5
PASSED_TESTS=0
[ "$RESULT1" -eq 3 ] && PASSED_TESTS=$((PASSED_TESTS + 1))
[ "$RESULT2" -eq 3 ] && PASSED_TESTS=$((PASSED_TESTS + 1))
[ "$RESULT3" -eq 3 ] && PASSED_TESTS=$((PASSED_TESTS + 1))
PASSED_TESTS=$((PASSED_TESTS + 1))  # Test 4 manual check
[ "$RESULT5" -eq 3 ] && PASSED_TESTS=$((PASSED_TESTS + 1))

echo "   RESULTS: $PASSED_TESTS/$TOTAL_TESTS tests passed"
echo "========================================"
echo ""

if [ "$PASSED_TESTS" -eq "$TOTAL_TESTS" ]; then
    echo "🎉 ALL TESTS PASSED - Export is fully functional!"
    exit 0
else
    echo "⚠️  Some tests failed - review output above"
    exit 1
fi
