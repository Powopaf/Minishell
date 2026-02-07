*This project has been created as part of the 42 curriculum by flomulle and pifourni.*

# Minishell

## Description

Minishell is a lightweight shell implementation that replicates core functionality of a POSIX-compliant shell. It provides an interactive command-line interface where users can execute commands, manage input/output redirections, chain commands with pipes, and use control operators (AND, OR, semicolons).

### Project Goal

The goal of this project is to deepen understanding of:

- Process management (fork, exec, wait)
- File descriptor manipulation and redirections
- Token-based parsing and Abstract Syntax Trees (AST)
- Signal handling and terminal interaction
- Memory management in complex systems

### Key Features

- **Command Execution**: Run both builtin and external commands
- **Pipes**: Chain multiple commands with `|`
- **Redirections**: Input (`<`, `<<`), output (`>`, `>>`), and heredoc support
- **Control Operators**: Sequential (`;`), AND (`&&`), OR (`||`), and subshells
- **Environment Variables**: Expansion and environment manipulation
- **Error Handling**: Detailed error messages with proper exit codes

## How It Works

Minishell follows a classic shell architecture with four main stages:

### 1. **Tokenization** (`src/parsing/token/`)

The input line is broken into tokens (keywords, operators, words):

- `isshspace()`, `isshbreak()` - Character classification
- `tokenization()` - Main tokenization loop
- `syntax_check()` - Validates token sequence for syntax errors

**Example**: `ls -la | grep .c` becomes:

```bash
[WORD: "ls"] [WORD: "-la"] [PIPE] [WORD: "grep"] [WORD: ".c"]
```

### 2. **Parsing** (`src/parsing/`)

Tokens are converted into an Abstract Syntax Tree (AST) representing command structure:

- `parser()` - Builds AST from tokens
- `parse_command_args()` - Extracts command and arguments
- `parse_redir()` - Processes redirections
- `expand_var()` - Expands environment variables

**Example**: AST structure for `ls | wc -l`:

```c
        PIPE
        /  \
      CMD  CMD
      /     /
    "ls"  "wc" "-l"
```

### 3. **Execution** (`src/exec/`)

The AST is walked and commands are executed:

- `exec_root()` - Recursively executes AST nodes
- `exec_cmd()` - Executes individual commands (builtins or external)
- `setup_pipe()` - Creates pipes between processes
- `redir()` - Applies input/output redirections
- `parse_cmd()` - Resolves command paths using `PATH` environment

**Flow**:

1. Fork a child process
2. Apply redirections (dup2)
3. Execute command or run builtin
4. Parent waits for child completion

### 4. **Cleanup** (`src/clean/`)

After execution, allocated memory is freed:

- `clean_shell()` - Frees entire shell context
- `tokens_clear()` - Frees token list
- `redir_clear()` - Frees redirection structures

### Data Structures

**Token** (`struct.h`):

```c
typedef struct s_token {
    t_token_kw kw;      // Token type (WORD, PIPE, REDIR_IN, etc.)
    char *token;        // Token string
    struct s_token *prev, *next;  // Linked list
} t_token;
```

**AST Node**:

```c
typedef struct s_ast {
    t_ast_node_type astkw;  // CMD, PIPE, AND, OR, SUBSHELL
    char **args;            // Command arguments
    struct s_redir *redir;  // Redirections
    int fd_in, fd_out;      // Pipe file descriptors
    pid_t pid;              // Child process ID
    struct s_ast *left, *right;  // Tree structure
} t_ast;
```

### Example Execution Trace

**Input**: `cat file.txt | grep "hello" > output.txt`

1. **Tokenization**:
   - [WORD:"cat"] [WORD:"file.txt"] [PIPE] [WORD:"grep"] [WORD:"hello"] [REDIR_OUT] [WORD:"output.txt"]

2. **Parsing**:

```c
           PIPE
           /  \
         CMD  CMD (redir: > output.txt)
         /     /
       cat   grep
   ```

3.**Execution**:

- Fork for `cat`: reads file.txt → pipe
- Fork for `grep`: reads from pipe → redirects to output.txt
- Parent waits for both children

4.**Cleanup**: Free all tokens, AST nodes, file descriptors

## Instructions

### Compilation

The project uses a Makefile for compilation with AddressSanitizer enabled:

```bash
make                # Compile with debug and sanitizer
make clean          # Remove object files
make fclean         # Remove all generated files
make re             # Full recompilation
```

**Compiled binary**: `./minishell`

### Execution

```bash
./minishell         # Start interactive shell
./minishell < file  # Execute commands from file
echo "ls -la" | ./minishell  # Pipe commands to shell
```

### Requirements

- **C99 or later**
- **AddressSanitizer** (built-in with modern GCC/Clang)
- **POSIX-compliant system** (Linux, macOS, BSD)

### Testing

Basic command tests:

```bash
./minishell
> ls -la
> pwd
> echo $HOME
> cat file.txt | grep pattern
> ls > output.txt
> cat < input.txt
> echo "line1\nline2" | wc -l
> cd ..  # If builtin cd is implemented
```

## Resources

### Official Documentation

- [POSIX Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) - Standard shell behavior reference
- [Linux man pages](https://man7.org/) - System call documentation (fork, exec, wait, dup2)
- [The C Standard Library](https://en.cppreference.com/w/c/header) - Standard C functions

### Key System Calls

- `fork()` - Process creation
- `execve()` - Program execution
- `wait()` / `waitpid()` - Process synchronization
- `pipe()` - Inter-process communication
- `dup2()` - File descriptor redirection
- `open()` / `close()` - File operations
- `signal()` - Signal handling

### Learning Resources

- Advanced Programming in the UNIX Environment (W. Richard Stevens) - Deep dive into processes and I/O
- Shell Scripting Tutorial - Understanding shell mechanics
- Bash Manual - Reference implementation behavior

### AI Usage

AI was used to assist with:

1. **Code Documentation** (Header comments following libft style)
   - Generated JSDoc-style function documentation blocks
   - Standardized parameter and return value descriptions

2. **Bug Fixes** (Double-free error resolution)
   - Identified memory management issues in `parser_cmd.c`
   - Assisted with pointer lifecycle management

3. **README Generation** (This file)
   - Structured project documentation
   - Explained complex execution flow with examples
   - Listed resources and requirements

4. **Code Organization**
   - Reviewed function signatures
   - Suggested architectural improvements
   - Identified memory leak risks

**Note**: All core logic, algorithms, parsing, execution, and system-level code was written by the project authors. AI provided refactoring guidance, documentation assistance, and debugging support.

## Technical Choices

- **Linked Lists**: Used for tokens and redirections for dynamic sizing
- **Recursive AST**: Natural representation for nested command structures (pipes, control operators)
- **Immediate Execution**: Commands are executed as the AST is built (no optimization passes)
- **File Descriptor Preservation**: Original stdin/stdout backed up to restore after subshells
- **AddressSanitizer**: Enabled by default to catch memory errors early

## Known Limitations

- No job control (bg/fg commands not supported)
- Limited builtin commands (implementation-dependent)
- Subshells may not fully replicate bash behavior
- No command history (readline not used)

## Project Structure

```bash
Minishell/
├── libft/              # Custom C library functions
├── src/
│   ├── parsing/        # Tokenization → AST building
│   ├── exec/           # Command execution engine
│   ├── init/           # Shell initialization
│   ├── clean/          # Memory cleanup
│   └── error/          # Error handling
├── minishell.c         # Main entry point
├── struct.h            # Core data structures
└── redir.h             # Redirection structures
```
