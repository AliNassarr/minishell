#!/bin/bash

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║         Pipeline Signal Exit Status Validation                ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

echo "=== Automated Tests ==="
echo ""

# Test 1: Normal pipeline (should be 0)
echo "Test 1: Normal pipeline exit"
result=$(printf "echo hello | cat\necho \$?\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | tail -2 | head -1)
echo "Result: $result"
[ "$result" = "hello" ] && echo "✓ Pipeline works"
result=$(printf "echo hello | cat\necho \$?\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | tail -1)
echo "Exit status: $result"
[ "$result" = "0" ] && echo "✓ PASS: Normal exit = 0" || echo "✗ FAIL: Expected 0, got $result"

echo ""

# Test 2: Failed command in pipeline
echo "Test 2: Failed command (false) in pipeline"
result=$(printf "false | true\necho \$?\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | tail -1)
echo "Exit status: $result"
[ "$result" = "0" ] && echo "✓ PASS: Right side succeeds = 0" || echo "Note: Got $result"

echo ""

# Test 3: Check signal handling logic
echo "Test 3: Verify signal handling is implemented"
grep -n "WIFSIGNALED" execution/executor_pipe.c && echo "✓ Signal check found" || echo "✗ Missing signal check"

echo ""
echo "=== Manual Test Required ==="
echo ""
echo "To fully validate the fix, run these manual tests:"
echo ""
echo "Test A: SIGQUIT (Ctrl-\\)"
echo "  1. Run: ./minishell"
echo "  2. Type: sleep 3 | sleep 3 | sleep 3"
echo "  3. Press: Ctrl-\\ (backslash) within 3 seconds"
echo "  4. Type: echo \$?"
echo "  5. Expected: 131 (128 + 3 for SIGQUIT)"
echo ""
echo "Test B: SIGINT (Ctrl-C)"
echo "  1. Run: ./minishell"
echo "  2. Type: sleep 3 | sleep 3 | sleep 3"
echo "  3. Press: Ctrl-C within 3 seconds"
echo "  4. Type: echo \$?"
echo "  5. Expected: 130 (128 + 2 for SIGINT)"
echo ""
echo "=== Bash Comparison ==="
echo ""
echo "Run the same tests in bash to verify expected behavior:"
echo "  bash"
echo "  sleep 3 | sleep 3"
echo "  Press Ctrl-\\ or Ctrl-C"
echo "  echo \$?"
echo ""
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║  Note: Automated signal testing is difficult without TTY      ║"
echo "║  Manual testing is required for full validation               ║"
echo "╚════════════════════════════════════════════════════════════════╝"
