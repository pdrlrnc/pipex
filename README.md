# pipex 🔧
Rebuild shell-style pipelines in C. Because why not. 😎

## 📋 Quick Start

### Requirements
- Linux or macOS with a POSIX shell
- `make` + `gcc`/`clang`
- Standard C library + POSIX syscalls (`fork`, `execve`, `pipe`, `dup2`, …)

### Build
```bash
make        # builds mandatory
make bonus  # builds bonus (multi-pipe)
```

### Run
**Mandatory (2 commands):**
```bash
./pipex <infile> "<cmd1> [args...]" "<cmd2> [args...]" <outfile>
# behaves like: < infile cmd1 | cmd2 > outfile
```

**Bonus (N ≥ 2 commands):**
```bash
./pipex <infile> "<cmd1> [args...]" "<cmd2> [args...]" ... "<cmdN> [args...]" <outfile>
# behaves like: < infile cmd1 | cmd2 | ... | cmdN > outfile
```

> ❗️Not implemented on purpose: `<<` here_doc and `>>` append. Outfile is **truncated** (overwrite), never appended.

---

## ✨ What it does (and doesn’t)
- ✔️ Chains multiple commands with pipes (bonus).
- ✔️ Resolves commands via `$PATH` (so `grep`, `awk`, etc. just work).
- ✔️ Handles quoted arguments: `"grep -E 'foo|bar'"`.
- ✔️ Proper file redirection: read from `infile`, write to **new** `outfile`.
- ❌ **No** here-doc (`<< LIMITER ...`) and **no** append to outfile (`>>`).

---

## 🔧 Behavior & Exit Status
- The program’s **exit code** matches the **exit status of the last command** in the pipeline (like Bash).
- If a command cannot be executed, a non‑zero status is returned (commonly:
  - `127` → command not found,
  - `126` → found but not executable).
- Errors are printed to `stderr` (perror‑style messages).

Check it quickly:
```bash
./pipex a.txt "grep as" "wc -l" out.txt; echo "pipex rc=$?"
< a.txt grep as | wc -l > out-bash.txt; echo "bash rc=$?"
diff -u out.txt out-bash.txt
```

---

## 🧪 Quick Examples

### Basic two‑stage
```bash
./pipex a.txt "cat" "wc -l" out.txt
# < a.txt cat | wc -l > out.txt
```

### With arguments & quoting
```bash
./pipex input.txt "grep -E 'foo|bar'" "sort -u" out.txt
# < input.txt grep -E 'foo|bar' | sort -u > out.txt
```

### Multi‑pipe (bonus)
```bash
./pipex a.txt "cut -d, -f2" "tr 'a-z' 'A-Z'" "uniq" "sort" z.txt
# < a.txt cut -d, -f2 | tr 'a-z' 'A-Z' | uniq | sort > z.txt
```

### Compare against Bash + exit codes
```bash
# Files
./pipex a.txt "head -n 8" "tail -n 3" z_pipex.txt; rc_px=$?
< a.txt head -n 8 | tail -n 3 > z_bash.txt; rc_bash=$?
echo "pipex rc=$rc_px | bash rc=$rc_bash"
diff -u z_*txt

# Nonexistent command
./pipex a.txt "zbsd" "cat" o.txt; echo "rc=$?"
```

---

## 🛠️ Implementation Notes (for the curious)
- Uses `fork`, `pipe`, `dup2` to wire `stdin/stdout` across children.
- Each `execve` only sees its slice of the pipeline:
  - First cmd: `stdin` ← `infile`
  - Middle cmds: `stdin` ← prev pipe, `stdout` → next pipe
  - Last cmd: `stdout` → `outfile` (truncated)
- Closes all unused FDs in parent/children to avoid leaks & deadlocks.
- Waits for all children; propagates the **last** child’s status as program exit code.

---

## ⚠️ Common gotchas
- Quote your commands so the shell doesn’t pre‑parse them:
  - ✅ `"grep -E 'foo|bar'"`  ❌ `grep -E 'foo|bar'` (unquoted)
- If `infile` doesn’t exist or isn’t readable → you’ll get an error and the pipeline will fail early.
- Outfile is **overwritten**, not appended.

---

## 📦 Allowed / typical functions (42‑style)
`open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid` (+ your libft helpers).

---

## 🧰 Make targets
```bash
make        # pipex
make bonus  # pipex (multi-pipe)
make clean  # remove objects
make fclean # remove binary + objects
make re     # rebuild
```

---

## ✅ Project status
- Mandatory: ✅
- Bonus (multi‑pipe): ✅
- `>>` / `<<`: ❌ (intentionally skipped)
