# Analysis of 118 Failing Tests (15% of 744 total)

## Summary by Category

### 🔴 Critical Issues (Need Fixing)

#### 1. **UNSET Crashes** (12 tests - CRITICAL BUG)
**Status**: 🔴 BROKEN - Causes segmentation fault/abort
**Tests failing**: 290, 312, 317, 319, 332-334, 342, 344, 350-356

**Problem**: Memory corruption in `unset` builtin
```bash
# All these crash:
unset INEXISTANT
unset _HOLA
unset HOL_A
unset HOLA_
```

**Error**: `free(): invalid pointer` or `Aborted (core dumped)`

**Root Cause**: The `unset_env_value` function creates a new environment array but doesn't properly handle the old array, causing a double-free or invalid pointer when the shell exits.

**Fix Required**: 
- Don't free the old env array (GC should handle it)
- Or properly track which pointers are GC-managed

---

### ⚠️ Missing Features (Acceptable for basic minishell)

#### 2. **Parentheses/Subshells** (22 tests - BONUS FEATURE)
**Status**: ⚠️ NOT IMPLEMENTED
**Pass Rate**: 42% (16/38)

**Examples**:
```bash
(ls)                    # Subshell execution
(ls && pwd)             # Subshell with logical operators
(cd ../.. && pwd) && pwd  # Subshell doesn't affect parent
```

**Why failing**: Subshells require forking a new process and executing commands in isolation. This is a bonus feature not required for basic minishell.

---

#### 3. **Multi-line Redirections** (27 tests - COMPLEX FEATURE)
**Status**: ⚠️ PARTIAL SUPPORT
**Category**: `<< << << << << << <<` (74% pass rate)

**Examples that fail**:
```bash
echo hola > srcs/bonjour
$> echo hey > srcs/hello
$> <bonjour cat | wc > bonjour  # Reads and writes same file
```

**Why failing**: These are complex multi-step tests with:
- Multiple commands in sequence
- Files in subdirectories (srcs/)
- Same file used as input and output
- Variable expansion in filenames

---

#### 4. **Signal Handling Edge Cases** (6 tests - INTERACTIVE ONLY)
**Status**: ⚠️ REQUIRES USER INTERACTION
**Tests**: 189, 190, 195, 197-199

**Examples**:
```bash
cat (faire Ctrl-C apres avoir fait plusieurs entrées)
sleep 3 | sleep 3 | sleep 3 (faire Ctrl-C)
```

**Why failing**: These tests require:
- Manual user interaction (pressing Ctrl-C, Ctrl-D, Ctrl-\)
- Cannot be automated in the tester
- Would need expect/pexpect or similar for automation

---

#### 5. **History Command** (1 test - BONUS FEATURE)
**Status**: ⚠️ NOT IMPLEMENTED

```bash
history  # Show last 500 commands
```

**Why not needed**: History is a bonus feature using readline's history functions. Basic minishell doesn't require it.

---

### 🟡 Minor Issues (Edge Cases)

#### 6. **Special Characters** (15 tests)
**Category**: `CARACTERES A LA VOLEE` (68% pass rate)

**Examples**:
```bash
!          # History expansion (bash feature)
\          # Backslash (should return 0 in bash, but it's just a newline escape)
;;         # Double semicolon (case statement syntax - not required)
()         # Empty parentheses
''         # Empty string (should probably return 0)
.          # Current directory as command
..         # Parent directory as command  
~          # Home directory as command
ABC=hola   # Variable assignment without export (bash feature)
```

**Why failing**: These are bash-specific features or edge cases:
- History expansion (`!`)
- Case statement syntax (`;;`)
- Variable assignment without export/declare
- Directory execution

---

#### 7. **ENV with Arguments** (3 tests)
**Tests**: 201, 202, 206

```bash
env hola            # env should run 'hola' command with clean environment
env ./Makefile      # env should execute Makefile (if executable)
```

**Why failing**: Your `env` builtin only prints environment. Bash's `env` command can also execute commands with a modified environment.

---

#### 8. **EXPORT Special Cases** (6 tests)
**Tests**: 226, 227, 256-258, 290

```bash
export -HOLA=bonjour    # Should error (invalid option)
export --HOLA=bonjour   # Should error (invalid option)
export HOLA=bon(jour    # Should error (parentheses in value)
export HOLA=bon()jour   # Should error
export HOLA=bon&jour    # Should error (ampersand in value)
```

**Why failing**: Need better validation for:
- Options (- and --)
- Special characters in values (parentheses, ampersand)

---

#### 9. **CD Edge Cases** (8 tests)
**Tests**: 407-409, 412, 421

```bash
cd -        # Go to OLDPWD (not implemented)
cd --       # Go to HOME (bash quirk)
cd ---      # Should error
cd ~/       # Tilde expansion (might not be working)
```

**Why failing**: Missing features:
- `cd -` to go to previous directory
- Tilde expansion for `~/path`

---

#### 10. **PWD with Options** (3 tests)
**Tests**: 368-370

```bash
pwd -p      # Should error (invalid option)
pwd --p     # Should error
pwd ---p    # Should error
```

**Why failing**: Your `pwd` doesn't validate options. It should return error code 2 for invalid options.

---

#### 11. **EXIT with Multiple Args** (3 tests)
**Tests**: 452, 458, 461

```bash
exit hola que tal   # Multiple non-numeric arguments
exit hola 666       # Non-numeric then numeric
exit hola 666 666   # Non-numeric then multiple numeric
```

**Why failing**: Your exit handles spaces as "too many arguments" but these might need different handling.

---

#### 12. **Logical Operators with Syntax Errors** (4 tests)
**Tests**: 566-569

```bash
ls || ;     # Syntax error after logical operator
; || ls     # Syntax error before logical operator  
ls && ;
; && ls
```

**Why failing**: These should be caught as syntax errors (exit 2) but are probably returning different codes.

---

#### 13. **Heredoc Edge Cases** (2 tests)
**Tests**: 732, 736

```bash
<< $hola           # Heredoc with variable as delimiter
echo hola <<< bonjour  # Here-string (<<< - not required)
```

**Why failing**: 
- `<<<` (here-string) is bash-specific, not required
- Variable expansion in heredoc delimiter might not be working

---

#### 14. **Wildcard** (1 test)
**Test**: 739

```bash
ls *  # Wildcard expansion
```

**Why failing**: Wildcards are bonus features. 83% of wildcard tests pass, so basic support exists.

---

#### 15. **PIPES Complex Case** (1 test)
**Test**: 550

```bash
echo hola > a
$> >>b echo que tal
$> cat a | cat b
```

**Why failing**: Multi-line complex test with append redirection.

---

## Priority Fixes

### 🔴 **HIGH PRIORITY** (Must Fix)
1. **UNSET memory corruption** - This is a critical bug that crashes the shell
   - Affects 12 tests
   - Causes segfault/abort

### 🟡 **MEDIUM PRIORITY** (Good to have)
2. **PWD option validation** - Easy fix, 3 tests
3. **EXPORT value validation** - Better error handling, 6 tests
4. **ENV command execution** - Makes env more compatible, 3 tests

### 🟢 **LOW PRIORITY** (Optional/Bonus)
5. **cd -** support - Common feature, 3 tests
6. **Tilde expansion** - Nice to have, 2 tests
7. **Parentheses/subshells** - Bonus feature, 22 tests
8. **History** - Bonus feature, 1 test

---

## Tests That Cannot Be Fixed (Interactive/Bonus)

- **Signal tests requiring Ctrl-C/Ctrl-D**: 6 tests (need manual interaction)
- **Special characters** (!, ;;, etc.): 8 tests (bash-specific features)
- **Subshells**: 22 tests (bonus feature)
- **Here-string** (<<<): 1 test (bash-specific)
- **History**: 1 test (bonus)

**Total unfixable without major features**: ~38 tests (5% of total)

---

## Conclusion

**Current Status**: 621/744 (83%) ✅

**After fixing HIGH priority issues**:
- Fix UNSET bug: +12 tests
- **Projected**: 633/744 (85%)

**After fixing MEDIUM priority issues**:
- PWD validation: +3
- EXPORT validation: +6
- ENV execution: +3
- **Projected**: 645/744 (87%)

**After fixing LOW priority issues**:
- cd -, tilde, etc: +10
- **Projected**: 655/744 (88%)

**Realistic maximum** (without implementing bonus features like subshells, history, here-strings):
- **680/744 (91%)**

The remaining 9% would be bonus features and bash-specific edge cases that are not required for the project.
