#!/bin/bash

echo "=== Integration Tests ==="
echo ""

# Test pipes
result=$(printf "echo test | cat\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep "test")
[ -n "$result" ] && echo "✓ Pipes work" || echo "✗ Pipes broken"

# Test redirects
printf "echo hello > /tmp/ms_test\ncat /tmp/ms_test\nexit\n" | ./minishell > /dev/null 2>&1
result=$(cat /tmp/ms_test 2>/dev/null)
[ "$result" = "hello" ] && echo "✓ Redirects work" || echo "✗ Redirects broken"
rm -f /tmp/ms_test

# Test parentheses with pipes
result=$(printf "echo (test) | cat\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep "(test)")
[ -n "$result" ] && echo "✓ Parentheses + pipes work" || echo "✗ Parentheses + pipes broken"

# Test heredoc
result=$(printf "cat << EOF\n(test)\nEOF\nexit\n" | ./minishell 2>&1 | grep "(test)" | head -1)
[ "$result" = "(test)" ] && echo "✓ Heredoc with parentheses works" || echo "✗ Heredoc broken"

# Test export (from previous fixes)
result=$(printf "export TEST=(value)\necho \$TEST\nexit\n" | ./minishell 2>&1 | grep -v "minishell" | grep -v "exit" | grep "not a valid" | head -1)
[ -n "$result" ] && echo "✓ Export validation still works" || echo "✗ Export validation broken"

echo ""
echo "=== All integration tests complete ==="
