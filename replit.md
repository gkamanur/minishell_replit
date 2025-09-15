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
- ✅ Readline library installed with proper headers and linking
- ✅ Fixed header include path issues
- ✅ Fixed C keyword conflicts (renamed 'new' parameter to 'new_node')  
- ✅ Fixed Makefile tab/space formatting issues
- ✅ Project builds successfully
- ✅ Console workflow configured and running

## Recent Changes (Sept 15, 2025)
- Fixed include path for `get_next_line_bonus.h` in `SOURCE/include/minishell.h`
- Renamed function parameter `new` to `new_node` to avoid C keyword conflict in both header and implementation
- Added readline system dependency with proper header and library linking
- Updated Makefile CFLAGS to include proper include directories: `$(NIX_CFLAGS_COMPILE)`
- Updated Makefile linking to include Nix library paths: `$(NIX_LDFLAGS)`
- Fixed Makefile tab/space indentation issues using AWK script
- Configured "Minishell" console workflow for interactive shell usage
- **FIXED VARIABLE EXPANSION**: Implemented token boundary tracking system to properly handle mixed quoted/unquoted variable expansion
  - Added `join_with_next` flag to token structure to track adjacency during lexing
  - Modified expansion logic to concatenate token groups instead of 1:1 token-to-argument mapping
  - Fixed parser `dup_token` function to preserve boundary flags
  - Now correctly handles cases like `'$HOME'$USER` → `$HOMErunner` (bash-compatible)

## Usage Instructions
- **Run minishell**: Use the "Minishell" workflow in the console panel
- **Rebuild project**: Run `make clean && make` in the terminal
- **Available commands**: Built-in commands (cd, echo, env, exit, export, pwd, unset) and external commands via PATH
- **Features**: Command history, pipes, redirections, variable expansion, signal handling

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