## Lab Writeup

Answer these questions as the writeup for your lab.

1. **Why does `s_sh` watch for the SIGCLD signal?**

```
sigaddset(&intrmask, SIGCLD);  /* we will only watch
            for SIGCLD at this time */

signal(SIGCLD, child_exit);    /* this will warn
            us to update our tables since if a child
            process dies or is terminated we will be
            sent a SIGCLD signal */
```

When any child program started by the shell finishes, the system sends `SIGCLD`.  
The handler `child_exit` immediately calls `wait`, removes the child from memory, and notes its result. This prevents zombie processes and keeps the shell’s job list correct.

2. **How are the internal commands in `s_sh` implemented?**

```
/* ********** START OF INTERNAL COMMANDS: dir, pwd, .. ************* */

if (strcmp(cmd[0], "cd")   == 0) { … }
else if (strcmp(cmd[0], "envp") == 0) { … }
else if (strcmp(cmd[0], "history") == 0) { … }
else if (strcmp(cmd[0], "jobs") == 0) { … }
else if (strcmp(cmd[0], "dir") == 0) { … }
else if (strcmp(cmd[0], "pwd") == 0) { … }
else if (strcmp(cmd[0], "tty") == 0) { … }
```

After splitting the line into words, the shell checks the first word against each built-in name. A match calls the matching C function right away inside the same process. If no match exists, the shell uses `fork` and `exec` to start an external program.

3. **In `process_esc` (in `s_tlnt`), how does Pine provide a “graphical” text interface using these escape sequences?**

```
ESC A           CURSOR UP
ESC B           CURSOR DOWN
ESC C           CURSOR RIGHT
ESC D           CURSOR LEFT
ESC J           CLEAR TO EOS
ESC K           CLEAR TO EOL
ESC [ attrib m  COLOR ATTRIBUTES
ESC [ 6n        POSITION ENQUIRY (ans: ESC [ row ; col R )
```

Pine sends these ANSI/VT100 codes to the terminal to move the cursor, clear parts of the screen, change colour, and query the cursor position. By combining movements, clears, and colour changes, Pine writes text at exact screen spots, draws borders with line characters, highlights choices, and updates only what changed. The result looks like a simple window system even though it is plain text.

4. **Why does `s_tlnt` contain code to parse a command line?**

```
/* this is a crude parser, spaces and tabs are delimiters
   between tokens. the raw command line is put into both
   raw_cmdline[] and cmdbuf[] and the array cmd[] of
   pointers is set to point to each of the arguments … */
```

Pressing **Ctrl-T** makes the program leave data mode and show the prompt `s_tlnt>`. At that prompt a user can type commands such as `open`, `close`, or `status`. The parser splits the line into separate words so the program can recognise the command and run the right routine.

5. **How do `s_sh` and `s_tlnt` support both Windows and Linux?**

```
#if defined(_WIN95) || defined(_WINNT)
/* Windows specific code */
#else
/* Unix specific code */
#endif
```

The source surrounds operating system differences with preprocessor checks. During compilation the compiler keeps the block that matches the target platform and removes the other. Inside each block the code chooses the correct headers, path separators, and system calls, for example `spawnve` on Windows or `fork` and `execve` on Unix. One code base therefore builds and runs on either system without changes.
