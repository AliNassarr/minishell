# Minishell Project Plan

## 📌 Project Stages

### ✅ Stage 1: Tokenization (COMPLETED)
**Location:** `tokenization/`

**What it does:**
- Parses input string into tokens
- Handles double quotes (`"`)
- Handles single quotes (`'`)
- Returns array of `t_token` with type (DQ, SQ, NQ, ER)

**Example:**
```
Input:  echo "hello world" test
Output: t_token array:
  [0] = {str: "echo ", type: NQ}
  [1] = {str: "hello world", type: DQ}
  [2] = {str: " test", type: NQ}
```

---

### 🔜 Stage 2: Command Assembly (TODO)
**What it will do:**
- Join tokens into one string per command
- Handle command separators (`;`, `|`, `&&`, `||`)
- Prepare strings for built-in/external command execution

**Example:**
```
Input:  echo "hello world" test
After Stage 1: ["echo ", "hello world", " test"]
After Stage 2: "hello world test"  (passed to builtin_echo)
```

---

### ✅ Stage 3: Built-ins (IN PROGRESS)
**Location:** `builtins/`

**Completed:**
- ✅ `builtin_pwd()` - Print working directory (with getenv fallback)
- ✅ `builtin_echo(char *str)` - Echo with -n flag support
- ✅ Cleanup system: `gc_free_all()`
- ✅ ft_ utility functions (ft_strcmp, ft_strlen, ft_strcpy, ft_strdup)

**TODO:**
- 🔜 `builtin_env(char **envp)` - Print environment variables
- 🔜 `builtin_exit(char *str)` - Exit shell with code
- 🔜 `builtin_cd(char *path)` - Change directory
- 🔜 `builtin_export(char *str)` - Export environment variables
- 🔜 `builtin_unset(char *str)` - Unset environment variables

**Function Signatures (String-based for Stage 2):**
```c
void builtin_echo(char *str);
int  builtin_pwd(void);
int  builtin_env(char **envp);
int  builtin_exit(char *args);
int  builtin_cd(char *path);
int  builtin_export(char *str);
int  builtin_unset(char *str);
```

---

### 🔜 Stage 4: Execution (TODO)
**What it will do:**
- Check if command is a built-in
- If built-in: execute directly
- If external: fork + execve
- Handle pipes, redirections, etc.

---

### 🔜 Stage 5: Main Loop (TODO)
**What it will do:**
- Read input (readline/prompt)
- Call Stage 1 (tokenization)
- Call Stage 2 (command assembly)
- Call Stage 4 (execution)
- Handle signals (Ctrl+C, Ctrl+D, Ctrl+\)
- Cleanup and repeat

---

## 🗂️ File Structure

```
minishell/
├── tokenization/
│   ├── tokenization.h      # Token types, structures
│   ├── stage1.c            # Token parsing logic
│   ├── helper.c            # gc_malloc, utilities
│   └── makefile
│
├── builtins/
│   ├── ft_utils.h          # ft_ function declarations
│   ├── ft_utils.c          # ft_strcmp, ft_strlen, etc.
│   ├── builtin_pwd.c       # pwd implementation
│   ├── builtin_echo.c      # echo implementation (string-based)
│   ├── builtin_env.c       # (TODO)
│   ├── builtin_cd.c        # (TODO)
│   ├── builtin_export.c    # (TODO)
│   ├── builtin_unset.c     # (TODO)
│   └── builtin_exit.c      # (TODO)
│
├── execution/              # (TODO - Stage 4)
│   └── executor.c
│
├── parsing/                # (TODO - Stage 2)
│   └── command_builder.c
│
└── main.c                  # (TODO - Stage 5)
```

---

## 🎯 Next Steps

1. ✅ Complete cleanup system
2. ✅ Implement pwd with getenv fallback
3. ✅ Implement echo with -n flag
4. 🔜 Implement remaining built-ins (env, exit, cd, export, unset)
5. 🔜 Build Stage 2: Command assembly
6. 🔜 Build Stage 4: Execution engine
7. 🔜 Build Stage 5: Main loop with readline

---

## 📌 Important Notes

- All built-ins are designed to work with **single string input** (Stage 2 output)
- Using custom `ft_` functions (42 requirement)
- Garbage collector pattern for memory management
- Norminette compliant (max 25 lines per function, max 80 chars per line)
