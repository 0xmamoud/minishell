# 🐚 Minishell  

**Minishell** is a custom shell implementation created as part of the 42 curriculum. This project demonstrates the fundamentals of shell behavior, including parsing, piping, and executing commands, while adhering to POSIX standards.

---

## 🛠 Features  

- **Builtin Commands**:
  - `echo` (with `-n` option)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

- **Command Execution**: Executes commands found in the system's `$PATH`.  
- **Redirections**: Handles input (`<`), output (`>`), and append (`>>`) redirections.  
- **Pipes**: Supports chaining commands with `|`.  
- **Heredoc**: Implements the `<<` operator for inline input redirection.  
- **Environment Variables**: Fully manages and expands environment variables.  
- **Error Handling**: Provides appropriate error messages for invalid commands, files, or syntax.  

### **Unsupported Features**  
`Minishell` does not support `;`, `||`, or `&&` operators.  

---

## 🛠 Installation  

No compilation is necessary, as a pre-built binary is provided.

### 1. Clone the Repository  
    ```bash
    git clone https://github.com/yourusername/minishell.git
    cd minishell


### 2. Run the Shell:

    ./minishell
### 3. Run some bash command
    echo hello from minishell

## Directory structure
    .
    ├── Makefile              
    ├── README.md              # Project documentation
    ├── includes               # Header files
    │   ├── libft              # Custom library (libft)
    │   ├── minishell.h        # Main header for Minishell
    ├── minishell              # Precompiled binary for Minishell
    ├── obj                    # Object files (generated during compilation)
    ├── src                    # Source files
    │   ├── builtins           # Builtin command implementations
    │   ├── parsing            # Parsing and tokenizer logic
    │   ├── pipe               # Pipe and redirection handlers
    │   ├── main.c             # Entry point for Minishell
    ├── utils                  # Helper functions
    │   ├── clear.c
    │   ├── ft_join.c
    │   ├── ft_print_error.c
    │   └── ...
    └── minishell_tester      
