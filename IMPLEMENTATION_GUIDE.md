# 🎓 Minishell Implementation Guide
## Step-by-Step Study Plan

---

## 📚 **Part 1: Environment Management (PRIORITY 1)**

### **Why We Need This:**
- `export` needs to add/modify environment variables
- `cd` needs to update `PWD` and `OLDPWD`
- Child processes need our modified environment
- The original `envp` is read-only!

### **What We Need to Build:**

#### **1.1 Copy Environment on Startup**
```c
// In main.c:
int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    shell.env = copy_environment(envp);  // Make our own copy!
    shell.pwd = getcwd(NULL, 0);         // Get current directory
    shell.oldpwd = NULL;                  // No previous directory yet
    shell.exit_status = 0;
    shell.should_exit = 0;
    
    // ... rest of shell loop
}
```

**Study Questions:**
1. Why can't we modify `envp` directly?
2. What happens if `copy_environment()` fails?
3. Why do we need to track `pwd` and `oldpwd` separately?

---

#### **1.2 Get/Set Environment Variables**

**Functions to implement:**
```c
char *get_env_value(char **env, const char *key);
// Returns: Value of KEY=value, or NULL if not found

char **set_env_value(char **env, const char *key, const char *value);
// Returns: New environment array with KEY=value set

char **unset_env_value(char **env, const char *key);
// Returns: New environment array with KEY removed
```

**Study Task:** How would you search for "HOME" in this array?
```c
env[0] = "USER=alnassar"
env[1] = "HOME=/home/alnassar"  ← We want this!
env[2] = "PATH=/usr/bin:/bin"
env[3] = NULL
```

**Answer:** Compare each string until '=' character matches "HOME"

---

## 📚 **Part 2: CD Built-in (PRIORITY 1)**

### **What CD Must Do:**

1. **Change directory** with `chdir()`
2. **Update PWD** environment variable
3. **Update OLDPWD** environment variable
4. **Handle special cases:**
   - `cd` or `cd ~` → Go to HOME
   - `cd -` → Go to OLDPWD (print it!)
   - `cd /path` → Go to absolute path
   - `cd folder` → Go to relative path

### **Algorithm:**
```
1. Parse the path argument
   - No argument or "~" → use $HOME
   - "-" → use $OLDPWD
   - Otherwise → use as-is

2. Save current directory to OLDPWD
   
3. Call chdir(path)
   - If fails → print error, return 1
   
4. Update PWD and OLDPWD in environment
   
5. Return 0 for success
```

**Study Questions:**
1. What's the difference between `chdir("/tmp")` and `cd /tmp`?
   - Answer: `chdir()` is the system call, `cd` is our built-in that also updates env
2. Why must cd be a built-in and not an external command?
   - Answer: External commands run in child process, can't change parent's directory!

---

## 📚 **Part 3: Export Built-in (PRIORITY 2)**

### **What Export Must Do:**

**Case 1: No arguments** - Show all exported variables
```bash
minishell$ export
declare -x HOME="/home/alnassar"
declare -x PATH="/usr/bin:/bin"
declare -x USER="alnassar"
```

**Case 2: With arguments** - Add/modify variables
```bash
minishell$ export MY_VAR=hello
minishell$ export PATH=$PATH:/new/path
```

### **Algorithm:**
```
1. If no arguments:
   - Loop through env array
   - Print each in format: declare -x KEY="VALUE"
   
2. If arguments:
   - Parse: "KEY=VALUE"
   - Validate KEY (alphanumeric + underscore, no digits first)
   - Call set_env_value(shell->env, KEY, VALUE)
```

**Study Questions:**
1. Is `export 123=value` valid? Why not?
2. How do you split "MY_VAR=hello" into key and value?
3. What if value contains '='? Example: `export A=B=C`

---

## 📚 **Part 4: Signals (PRIORITY 1)**

### **What Signals to Handle:**

| Signal | Key | Behavior in Shell | Behavior in Command |
|--------|-----|-------------------|---------------------|
| SIGINT | Ctrl+C | New prompt | Kill command |
| SIGQUIT | Ctrl+\ | Do nothing | Kill command (dump core) |
| EOF | Ctrl+D | Exit shell | - |

### **Implementation:**

```c
void setup_signals(void)
{
    signal(SIGINT, handle_sigint);   // Ctrl+C
    signal(SIGQUIT, SIG_IGN);        // Ctrl+\ (ignore)
}

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);               // New line
    rl_on_new_line();                // Tell readline we're on new line
    rl_replace_line("", 0);          // Clear the input
    rl_redisplay();                  // Show new prompt
}
```

**Study Questions:**
1. Why use `write()` instead of `printf()` in signal handler?
   - Answer: Signal handlers must use async-signal-safe functions
2. What happens if we don't ignore SIGQUIT in the shell?
3. How is Ctrl+D different from signals?

---

## 📚 **Part 5: History with Readline (BUILT-IN!)**

### **Good News:** History is automatic with readline!

```c
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;
    
    while (1)
    {
        line = readline("minishell$ ");  // Automatically handles ↑ ↓
        if (!line)  // Ctrl+D pressed
            break;
        
        if (*line)  // Not empty
            add_history(line);  // Add to history
        
        // Process command...
        
        free(line);
    }
}
```

**That's it!** Users can press ↑ and ↓ to navigate history automatically!

**Study Questions:**
1. What does `readline()` return on Ctrl+D?
2. Why check `if (*line)` before `add_history()`?
3. Do we need to free history entries?

---

## 📚 **Part 6: Exit Built-in (PRIORITY 2)**

### **What Exit Must Do:**

```bash
minishell$ exit         # Exit with last status ($?)
minishell$ exit 42      # Exit with code 42
minishell$ exit hello   # Error: numeric argument required
```

### **Algorithm:**
```
1. If no argument:
   - Exit with shell->exit_status
   
2. If argument:
   - Check if numeric
   - If not → print error, set exit_status=2, don't exit
   - If yes → exit with that code
   
3. Set shell->should_exit = 1
```

**Study Questions:**
1. Should `exit 999` exit with code 999 or 999 % 256?
   - Answer: 999 % 256 = 231 (exit codes are 0-255)
2. What if user types `exit 42 extra args`?
   - Bash prints error but still exits with 42

---

## 🎯 **Implementation Order**

### **Week 1: Core Infrastructure**
- [ ] Day 1-2: Environment management (copy, get, set, unset)
- [ ] Day 3: CD built-in with PWD/OLDPWD updates
- [ ] Day 4: Signals (SIGINT, SIGQUIT)
- [ ] Day 5: Testing everything together

### **Week 2: Remaining Built-ins**
- [ ] Day 1: Export (display + set)
- [ ] Day 2: Unset
- [ ] Day 3: Exit
- [ ] Day 4: ENV (simple - just print shell->env)
- [ ] Day 5: Integration and testing

### **Week 3: Main Shell Loop**
- [ ] Day 1-2: Main loop with readline
- [ ] Day 3: Built-in dispatcher
- [ ] Day 4-5: Final testing and debugging

---

## 🧪 **Testing Checklist**

### **CD Tests:**
```bash
cd /tmp                 # Absolute path
cd ..                   # Relative path
cd                      # Go to HOME
cd ~                    # Go to HOME
cd -                    # Go to OLDPWD (should print path)
cd nonexistent          # Error handling
```

### **Export Tests:**
```bash
export                  # Show all vars
export MY_VAR=hello     # Set new var
export MY_VAR=world     # Modify existing
export INVALID-VAR=x    # Error: invalid name
export                  # Verify MY_VAR appears
```

### **Signal Tests:**
- Press Ctrl+C → Should show new prompt
- Press Ctrl+\ → Should do nothing
- Press Ctrl+D → Should exit cleanly

### **History Tests:**
- Type `echo hello`
- Press ↑ → Should show `echo hello`
- Press ↓ → Should clear
- Works automatically with readline!

---

## 💡 **Key Concepts to Understand**

1. **Why personal env copy?**
   - envp is read-only
   - We need to modify for export/unset
   - Child processes need modified version

2. **Why cd updates env?**
   - PWD and OLDPWD must stay in sync
   - Other programs rely on $PWD
   - `cd -` needs OLDPWD

3. **Why signals matter?**
   - Ctrl+C shouldn't kill the shell
   - Ctrl+\ should be ignored in shell
   - But both should work in child commands!

4. **Why readline for history?**
   - It's standard and battle-tested
   - Handles all edge cases
   - Free functionality!

---

## 🚀 **Let's Start!**

Ready to begin? Let's tackle them in this order:
1. Environment management (foundation for everything)
2. CD (uses environment)
3. Signals (user experience)
4. Export/Unset (uses environment)
5. Exit (simple)
6. Main loop with readline (ties everything together)

**Which part do you want to start with?**
