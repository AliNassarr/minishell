#!/bin/bash

# Simple debug tester to understand the issue
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MINISHELL="$SCRIPT_DIR/minishell"
TEST_DIR="/tmp/debug_test_$$"

mkdir -p "$TEST_DIR"

echo "=== Test 1: Plain exit ==="
cd "$TEST_DIR"
echo -e "exit\nexit" | timeout 5 "$MINISHELL" >"$TEST_DIR/m_out" 2>&1
MINI_EXIT=$?
cd - >/dev/null
echo "Minishell exit code: $MINI_EXIT"
echo "Minishell output:"
cat "$TEST_DIR/m_out"
echo ""

echo "=== Test 2: exit 42 ==="
cd "$TEST_DIR"
echo -e "exit 42\nexit" | timeout 5 "$MINISHELL" >"$TEST_DIR/m_out" 2>&1
MINI_EXIT=$?
cd - >/dev/null
echo "Minishell exit code: $MINI_EXIT"
echo ""

echo "=== Test 3: echo hello ==="
cd "$TEST_DIR"
echo -e "echo hello\nexit" | timeout 5 "$MINISHELL" >"$TEST_DIR/m_out" 2>&1
MINI_EXIT=$?
cd - >/dev/null
echo "Minishell exit code: $MINI_EXIT"
echo "Minishell output:"
cat "$TEST_DIR/m_out"
echo ""

rm -rf "$TEST_DIR"
