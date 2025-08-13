# pipex 🔧✨

Rebuild shell‑style pipelines in C. Understanding the wheel by reinventing the wheel 🚀

## 🛠️ Build
```bash
make
```

## ▶️ Usage
```bash
./pipex <infile> "<cmd1> [args...]" ... "<cmdN> [args...]" <outfile>
# behaves like: < infile cmd1 | ... | cmdN > outfile
```
N ≥ 2 commands are supported. 🔗

## 💡 Examples
```bash
./pipex a.txt "grep as" "wc -l" out.txt
./pipex in.csv "cut -d, -f2" "tr 'a-z' 'A-Z'" "sort -u" out.txt
```

## 📝 Notes
- Quote each command so the shell doesn’t pre‑parse args. 🧷
- Exit code equals the exit status of the **last** command. ✅
```bash
./pipex a.txt "head -n 8" "tail -n 3" px.txt; echo "pipex rc=$?"
< a.txt head -n 8 | tail -n 3 > sh.txt; echo "bash rc=$?"
diff -u px.txt sh.txt
```
