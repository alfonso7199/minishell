# Minishell

**Proyecto completado con calificación 100/100** 

Un shell minimalista implementado en C que replica las funcionalidades básicas de bash, desarrollado como proyecto de la **Escuela 42 Madrid**.

## Características Principales

### Funcionalidades Básicas (Requeridas)
- **Prompt interactivo** con historial de comandos
- **Ejecución de comandos** del sistema (PATH)
- **Built-ins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirecciones**: `<`, `>`, `>>`, `<<` (here-document)
- **Pipes** (`|`) para conectar comandos
- **Variables de entorno** con expansión `$VAR` y `$?`
- **Manejo de señales** (Ctrl+C, Ctrl+D, Ctrl+\)
- **Códigos de salida** apropiados

### Funcionalidades Adicionales (Extras)
- **Semicolons (`;`)** para separar comandos múltiples
- **Comillas sin cerrar** - manejo inteligente de comillas incompletas

## Arquitectura del Proyecto

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

## Tecnologías Utilizadas

- **Lenguaje**: C (C99)
- **Sistema**: Unix/Linux
- **Librerías**: `readline`, `termios`, `signal` ...
- **Compilador**: GCC/Clang
- **Make**: Sistema de build automatizado

## Instalación y Uso

### Prerrequisitos
```bash
# En sistemas Ubuntu/Debian
sudo apt-get install libreadline-dev

# En macOS
brew install readline
```

### Compilación
```bash
make
```

### Ejecución
```bash
./minishell
```

## Ejemplos de Uso

### Comandos Básicos
```bash
minishell> ls -la
minishell> echo "Hello World"
minishell> pwd
minishell> cd /home/user
```

### Variables de Entorno
```bash
minishell> echo $USER
minishell> export MY_VAR="Hello"
minishell> echo $MY_VAR
minishell> echo $?
```

### Redirecciones
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

### Semicolons (Funcionalidad Extra)
```bash
minishell> echo "First"; echo "Second"
minishell> ls; pwd; whoami
```

### Comillas Sin Cerrar (Funcionalidad Extra)
```bash
minishell> echo "This is a multiline
> string with unclosed quotes"
minishell> echo 'Another example
> with single quotes'
```

## 👥 Autores

**Escuela 42 Madrid**
- **Alfonso Sánchez** - [@alfonso7199](https://github.com/alfonso7199)
- **Rafael Zamolo Tanganelli** - [@rzamolo-](https://github.com/rafaelzt)
