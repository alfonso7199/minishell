# Minishell

**Project completed with a score of 100/100**

A minimalist shell implemented in C that replicates the basic functionalities of bash, developed as a project for **42 Madrid School**.

## Main Features

### Core Features (Required)
- **Interactive prompt** with command history
- **Command execution** using system PATH
- **Built-ins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirections**: `<`, `>`, `>>`, `<<` (here-document)
- **Pipes** (`|`) to connect commands
- **Environment variables** with `$VAR` and `$?` expansion
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)
- **Proper exit codes**

### Additional Features (Extras)
- **Semicolons (`;`)** to separate multiple commands
- **Unclosed quotes handling** – smart management of incomplete quotes

## Project Architecture

```
minishell/
├── include/
│   └── minishell.h          # Header principal con todas las estructuras
├── src/
│   ├── minishell.c          # Función main y loop principal
│   ├── shell.c              # Inicialización y limpieza del shell
│   ├── tokenizing/          # Lexer - análisis léxico
│   ├── parsing/             # Parser - análisis sintáctico
│   ├── executor/            # Ejecutor de comandos
│   ├── builtin/             # Comandos integrados
│   ├── signals/             # Manejo de señales
│   ├── error/               # Gestión de errores
│   └── utils/               # Utilidades generales
└── libft/                   # Biblioteca de funciones auxiliares
```


## Technologies Used

- **Language**: C (C99)
- **System**: Unix/Linux
- **Libraries**: `readline`, `termios`, `signal`, ...
- **Compiler**: GCC / Clang
- **Make**: Automated build system

## Installation and Usage

### Prerequisites
```bash
# On Ubuntu/Debian systems
sudo apt-get install libreadline-dev

# On macOS
brew install readline
```

### Compilation
```bash
make
```

### Execution
```bash
./minishell
```

## Usage Examples

### Basic Commands
```bash
minishell> ls -la
minishell> echo "Hello World"
minishell> pwd
minishell> cd /home/user
```

### Environment Variables
```bash
minishell> echo $USER
minishell> export MY_VAR="Hello"
minishell> echo $MY_VAR
minishell> echo $?
```

### Redirections
```bash
minishell> ls > output.txt
minishell> cat < input.txt
minishell> echo "append" >> file.txt
minishell> cat << EOF
> This is a here-document
> EOF
```

### Pipes
```bash
minishell> ls | grep .c
minishell> cat file.txt | wc -l
minishell> ps aux | grep bash
```

### Semicolons
```bash
minishell> echo "First"; echo "Second"
minishell> ls; pwd; whoami
```

### Comillas Sin Cerrar
```bash
minishell> echo "This is a multiline
> string with unclosed quotes"
minishell> echo 'Another example
> with single quotes'
```

## 👥 Authors

**Escuela 42 Madrid**
- **Alfonso Sánchez** - [@alfonso7199](https://github.com/alfonso7199)
- **Rafael Zamolo Tanganelli** - [@rzamolo-](https://github.com/rafaelzt)
