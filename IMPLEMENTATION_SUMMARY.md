# Minishell Implementation Summary

## Fixed Issues

### 1. AST Parsing Bug - Arguments After Redirections
**Problem:** When parsing commands like `echo hello > filename world | ls`, the AST was incorrectly grouping arguments. The word `world` (which appears after the redirect filename) was being grouped with the filename instead of with the command.

**Solution:** Modified `ast.c` to:
- Prioritize redirection operators over pipe/logical operators in the AST
- Created `createredirast()` function that extracts all CMD/ARG tokens (excluding the redirect operator and filename) and groups them together on the left side
- The redirection operator becomes the root node with:
  - **Left child:** All command and argument tokens grouped together
  - **Right child:** Just the filename/limiter token

**Result:** 
```
Input: echo hello > filename world | ls

Old AST (BROKEN):
Root: |
  L: >
    L: [echo hello]
    R: [filename world]  <- WRONG! "world" grouped with filename
  R: [ls]

New AST (FIXED):
Root: >
  L: |
    L: [echo hello world]  <- CORRECT! All args together
    R: [ls]
  R: [filename]
```

## Implemented Features

### 1. Base Executor (`execution/executor.c`)
- **AST Traversal:** Recursively processes the AST tree to execute commands
- **Simple Commands:** Extracts and executes commands with arguments
- **PATH Search:** Finds executables in PATH environment variable
- **Pipe Handling:** Creates child processes and connects stdin/stdout via pipes
- **Redirection Handling:** Opens files and redirects file descriptors
- **Logical Operators:** Implements AND (&&) and OR (||) with short-circuit evaluation

### 2. Shell Initialization (`minishell.c`)
- **Environment Copying:** Creates a managed copy of environment variables
- **PWD/OLDPWD Tracking:** Initializes and maintains current/previous directories
- **Signal Setup:** Integrates interactive and execution signal handlers
- **REPL Loop:** Implements the Read-Eval-Print-Loop with proper cleanup

### 3. Signal Handling Integration
- **Interactive Mode:** Handles Ctrl+C to clear line and show new prompt (doesn't exit)
- **Execution Mode:** Properly switches signal handlers during command execution
- **Signal Status Tracking:** Updates exit status when signals occur (e.g., 130 for SIGINT)
- **Child Process Handling:** Restores default signal behavior in child processes

### 4. Builtin Command Dispatcher (`builtins/builtin_dispatch.c`)
- **Command Detection:** Identifies builtin commands (echo, cd, pwd, env, export, unset, exit)
- **Argument Joining:** Combines argument array into single string for builtins that need it
- **Proper Execution:** Calls appropriate builtin with correct arguments
- **Memory Management:** Creates temporary GC heaps for builtins that need allocation

### 5. Utility Functions
- **Environment Management** (`utils/env_utils.c`):
  - `copy_environment()` - Duplicates environment array
  - `get_env_value()` - Retrieves value by key
  - `set_env_value()` - Sets or updates environment variable
  - `unset_env_value()` - Removes environment variable

- **String Utilities** (`utils/ft_utils.c`):
  - `ft_strcmp()` - Compare strings
  - `ft_strncmp()` - Compare n characters
  - `ft_strlen()` - Get string length
  - `ft_strcpy()` - Copy string
  - `ft_strdup()` - Duplicate string
  - `ft_strdup_gc()` - Duplicate string with GC

## Testing Results

### Working Features ✅
1. **Simple commands:** `echo hello`, `pwd`, `ls`
2. **Commands with pipes:** `echo hello | cat`
3. **Redirections:** `echo test > file.txt`
4. **Arguments after redirections:** `echo hello > file.txt world` ✅ **MAIN FIX!**
5. **Complex combinations:** `echo test > file.txt extra | cat file.txt`
6. **Builtins:** All builtin commands work correctly
7. **Signal handling:** Ctrl+C works in interactive mode
8. **Exit status:** Properly tracked and returned

### Known Issues ⚠️
1. **Tokenization Buffer Overflow:** The existing `tokenization/joining.c` code has a buffer overflow issue that causes heap corruption with certain long command strings (3+ arguments in some cases). This is a pre-existing bug in the tokenization layer that needs to be fixed separately.

## File Structure

```
minishell/
├── minishell.c              # Main entry point, REPL loop, shell initialization
├── execution/
│   └── executor.c           # NEW: AST executor with pipe, redirect, logical op handling
├── parsing/
│   └── ast.c                # MODIFIED: Fixed AST creation for redirections
├── builtins/
│   ├── builtin_dispatch.c   # NEW: Builtin command dispatcher
│   ├── builtin_cd.c         # Existing builtin implementations
│   ├── builtin_echo.c
│   ├── builtin_env.c
│   ├── builtin_exit.c
│   ├── builtin_export.c
│   ├── builtin_pwd.c
│   └── builtin_unset.c
├── signals/
│   ├── signal_handlers.c    # Existing signal handlers
│   ├── signal_setup.c       # Existing signal setup
│   └── signal_utils.c       # Existing signal utilities
└── utils/
    ├── env_utils.c          # NEW: Environment variable management
    └── ft_utils.c           # MODIFIED: Added ft_strncmp, fixed gc_malloc
```

## Usage Examples

```bash
# Simple command
minishell$ echo hello
hello

# Command with arguments AFTER redirection (the bug we fixed!)
minishell$ echo hello > output.txt world
minishell$ cat output.txt
hello world

# Pipes
minishell$ ls | head -3

# Complex combinations
minishell$ echo test1 > file.txt extra | cat file.txt

# Builtins
minishell$ pwd
minishell$ cd /tmp
minishell$ export VAR=value
minishell$ env | grep VAR
minishell$ exit
```

## Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

## Summary

The main accomplishment was fixing the AST parsing bug where arguments appearing after redirection operators were incorrectly grouped with the filename instead of with the command. The fix ensures that all CMD/ARG tokens stay together on the left side of a redirection node, while only the filename/limiter appears on the right side.

Additionally, a complete base executor was implemented with support for:
- Simple command execution with PATH searching
- Pipe operators with proper process management
- Redirection operators (>, <, >>, <<)
- Logical operators (&&, ||) with short-circuit evaluation
- Signal handling integration
- Builtin command execution
- Proper shell initialization and cleanup

The shell is now functional for basic command execution and demonstrates correct AST parsing for the originally reported bug.
