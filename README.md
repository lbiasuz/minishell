# Minishell

This project is a simple shell implementation written in **C**.

To test it, you only need to build the shell, then run it to get an interactive command prompt.
The shell supports basic command execution, pipes, redirections, and built-in commands.

## Build and start the shell
```bash
make
./minishell
```

## Test basic commands
Once running, you can test various shell features:
```bash
# Basic commands
ls -la
echo "Hello World"
pwd

# Pipes
ls | grep .c | wc -l
cat Makefile | head -5

# Redirections
echo "test" > output.txt
cat < input.txt
ls >> log.txt

# Built-in commands
cd /tmp
export PATH=$PATH:/usr/local/bin
unset VAR
env
exit
```

## Features
- Command execution with arguments
- Input/Output redirections (`<`, `>`, `>>`)
- Pipes (`|`)
- Environment variables
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Exit the shell
- Type `exit` or press `Ctrl-D` to quit the shell
