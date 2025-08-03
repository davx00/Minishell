# 🐚 Minishell

> A simplified Bash-like shell developed as part of the 42 core curriculum.  
> Built from scratch in C, following POSIX standards and handling many of the core shell features.

---

## 📌 About the Project

Minishell is a small, custom implementation of a Unix shell.  
It replicates fundamental behaviors of Bash such as parsing, command execution, redirections, pipes, and built-in commands — all without using system() or external shell tools.

This project taught us how shells really work under the hood and gave us hands-on experience with process management, file descriptors, and signal handling.

---

## ✅ Features

- Interactive prompt with command parsing
- Built-in commands:  
  `cd`, `echo`, `pwd`, `exit`, `env`, `export`, `unset`
- Pipes and redirections: `|`, `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion: `$VAR`
- Signal handling (`CTRL+C`, `CTRL+\`)
- Error management and exit codes
- Support for quotes (`'single'` and `"double"`)
- Executables from PATH or with relative/absolute paths
- No memory leaks (checked with Valgrind)

---

## 🚀 Getting Started

### Prerequisites

- A Unix-like environment (Linux/macOS)
- GCC or Clang compiler
- Make

### Installation

```bash
git clone https://github.com/davx00/Minishell.git
cd Minishell
make
```
## Running

```bash
./minishell
```
