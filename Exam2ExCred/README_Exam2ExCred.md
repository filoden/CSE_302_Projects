Exam2ExCred - build & run
==========================

This folder contains a small C++ project. Use the provided Makefile or the helper scripts to build and run.

Files added:

- `Makefile` - builds `exam2excred` by compiling all .cpp files.
- `build.sh` - POSIX-friendly script that runs `make` or falls back to `g++`.
- `build.ps1` - PowerShell script that runs `make` or falls back to `g++` on Windows.

Single-line examples (replace <repo-url> when cloning):

PowerShell (Windows):

    git clone <repo-url> ; Set-Location 'CSE_302_Projects/Exam2ExCred' ; .\build.ps1

Git Bash / WSL / macOS / Linux:

    git clone <repo-url> && cd CSE_302_Projects/Exam2ExCred && ./build.sh

Notes
-----
- Scripts expect either `make` (recommended) or `g++` in PATH.
- On Windows, install MSYS2/MinGW-w64 or Visual Studio Build Tools. If you use `cl.exe`, I can add a `build.ps1` path for `cl`.
