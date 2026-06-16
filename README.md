# Cagrinator Shell
A Unix shell implementation in C:

## Features
- REPL loop architecture
- Built-in commands: cd, ls, help, exit
- Process creation and management via fork/exec
- I/O handling

## Technical Details
- Written in pure C using POSIX system calls
- Process synchronization: waitpid

## Build & Run
gcc src/main.c -o cagrinator
./cagrinator
