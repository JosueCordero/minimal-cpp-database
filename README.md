<div align="center">

<img src="https://img.shields.io/badge/version-0.1.0--beta-blue" alt="status badge">

<h2>🚧🔧 UNDER DEVELOPMENT 🔧🚧</h2>
<p>This project is currently in active development.<br>
Expect frequent updates and possible breaking changes!</p>

</div>

# MinimalDB

A minimal, educational database written in modern C++ for learning purposes.

## ✨Features

- Simple CLI
- In-memory paging system

## ⚙️Prerequisites

- C++17 compatible compiler
- __make__ (or compatible build tool)
- [CMake](https://cmake.org/)

## 🛠️ Build Instructions

```bash
git clone https://github.com/JosueCordero/minimal-cpp-database.git
cd minimal-cpp-database/
```

```bash
mkdir build
cmke -B build/
cd build
make prod
```
## 🚀 Run the CLI
```bash
./miniCLI database_name.db
```
This will start the minimal REPL interface.

## 🧩 Architecture (Brief)

MinimalDB follows a modular design:

- Pager – Manages fixed-size pages of memory.
- Buffer – Collects and stores user input.
- CLI – Minimal REPL interface to test DB functions.

Planned components:
- Lexer - Token extraction from the bufffer
- Parser – Statement analysis and validation.
- Executor – Executes parsed instructions.
