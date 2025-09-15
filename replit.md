# Minishell Project

## Overview
This is a C project implementing a minimal shell (minishell) that mimics bash functionality. It's originally a GitHub import that needs to be set up to run in the Replit environment.

## Project Architecture
- **Language**: C with make build system
- **Key Components**:
  - Shell parsing and lexing
  - Command execution and piping
  - Built-in commands (cd, echo, env, exit, export, pwd, unset)
  - Environment variable expansion
  - Signal handling
  - Readline integration for command line input

## Current Setup Status
- ✅ C compiler (clang-14) installed
- ✅ Readline library installed  
- ✅ Fixed header include path issues
- ✅ Fixed C keyword conflicts (renamed 'new' parameter to 'new_node')
- 🔄 Working on Makefile tab/space formatting issues
- ❌ Project not yet successfully building
- ❌ No workflow configured yet

## Recent Changes (Sept 15, 2025)
- Fixed include path for `get_next_line_bonus.h` in `SOURCE/include/minishell.h`
- Renamed function parameter `new` to `new_node` to avoid C keyword conflict in both header and implementation
- Added readline system dependency
- Updated Makefile CFLAGS to include proper include directories

## Dependencies
- System: readline library
- Build: make, clang compiler
- Libraries: libft (custom C library), get_next_line

## File Structure
```
SOURCE/
├── include/
│   ├── minishell.h     # Main header file
│   └── colors.h        # Color definitions
├── main/               # Main program logic
├── lexer/              # Tokenization and parsing
├── parser/             # Command parsing
├── execute/            # Command execution
├── built/              # Built-in commands
├── expansion/          # Variable expansion
├── pipe/               # Pipe handling
├── gnl/                # Get next line utility
└── libft/              # Custom C library
```

## User Preferences
- Project imported from GitHub, should maintain existing structure and conventions
- Needs to run as terminal-based application (TUI/console app)