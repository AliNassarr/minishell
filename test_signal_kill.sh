#!/bin/bash

echo "=== Testing Signal Exit Status with kill ==="
echo ""

# Start minishell in background and test
(
  # Test SIGINT (Ctrl-C)
  echo "sleep 10 | sleep 10" | timeout 0.5s ./minishell &
  SHELL_PID=$!
  sleep 0.2
  # Find the sleep processes
  SLEEP_PIDS=$(pgrep -P $SHELL_PID sleep 2>/dev/null)
  if [ -n "$SLEEP_PIDS" ]; then
    echo "Sending SIGINT to sleep processes..."
    kill -INT $SLEEP_PIDS 2>/dev/null
    wait $SHELL_PID 2>/dev/null
    echo "Exit code: $?"
  fi
) 2>/dev/null

echo ""

# Test with actual interactive behavior
echo "To properly test, run manually:"
echo "  ./minishell"
echo "  sleep 3 | sleep 3"
echo "  Press Ctrl-\\ quickly"
echo "  echo \$?"
echo "Expected: 131"

