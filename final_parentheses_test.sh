#!/bin/bash

echo "=== Final Export Parentheses Validation Test ==="
echo ""

echo "✅ Test 1: export a() b (parentheses in middle)"
RESULT=$(printf 'export a() b\nenv | grep "^b="\nexit\n' | ./minishell 2>&1)
echo "$RESULT" | grep "not a valid identifier" > /dev/null && echo "✅ Error message shown"
echo "$RESULT" | grep "^b=" > /dev/null && echo "✅ Variable b exported"
echo ""

echo "✅ Test 2: export x=1 y() z=3 (mixed valid/invalid)"  
RESULT=$(printf 'export x=1 y() z=3\nenv | grep -E "^(x|y|z)="\nexit\n' | ./minishell 2>&1)
echo "$RESULT" | grep "not a valid identifier" > /dev/null && echo "✅ Error message shown for y()"
echo "$RESULT" | grep "^x=1" > /dev/null && echo "✅ Variable x=1 exported"
echo "$RESULT" | grep "^z=3" > /dev/null && echo "✅ Variable z=3 exported"
echo "$RESULT" | grep "^y=" > /dev/null || echo "✅ Variable y() NOT exported"
echo ""

echo "✅ Test 3: export 'a()' (quoted)"
RESULT=$(printf "export 'a()'\nenv | grep '^a'\nexit\n" | ./minishell 2>&1)
echo "$RESULT" | grep "not a valid identifier" > /dev/null && echo "✅ Error message shown"
echo "$RESULT" | grep "^a=" > /dev/null || echo "✅ Variable a() NOT exported"
echo ""

echo "✅ Test 4: Bash comparison"
echo "Bash behavior with 'export a() b':"
bash -c 'export "a()" b 2>&1; env | grep -E "^(a|b)="' 2>&1 | head -3
echo ""

echo "=== All export validation tests complete! ==="
