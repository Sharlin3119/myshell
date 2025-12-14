# MyShell - A Mini Unix Shell

**Authors:** Sharlin Patel, Rishi Patel, Sami Qadri
**Course:** CS12600-001 Systems Programming in C
**Semester:** Fall 2025

## Overview
MyShell is a custom implementation of a Unix shell written in C. It supports execution of external commands, built-in commands, input/output redirection, piping, and background process management.

## Features
- **External Commands:** Executes standard Unix programs (e.g., `ls`, `grep`, `sleep`).
- **Built-in Commands:** `cd` (change directory) and `exit`.
- **I/O Redirection:** Supports input (`<`), output truncation (`>`), and output appending (`>>`).
- **Pipes:** Connects two commands using `|` (e.g., `ls | grep c`).
- **Background Processing:** Runs commands in the background using `&`.
- **Signal Handling:** Ignores `Ctrl-C` in the shell; cleans up zombie processes automatically.
- **Logging:** Logs all executed commands to `myshell.log`.

## Build Instructions
This project includes a Makefile for easy compilation.
```bash
make
