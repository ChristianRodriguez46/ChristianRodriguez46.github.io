-----
output: pdf_document
-----

# Lab Write-Up
 - Answer the following questions and upload them to Canvas.

1. What is the purpose of SIGCHLD and SIGQUIT according to the man page?

2. What is the full list of signals marked in show_signals as important signals? Just give the signals, not their purpose

3. Pick three signals from Question 2 that you did not describe in Question 1 and describe their purpose.

4. Look at the man page for sigemptyset and describe its purpose in this code.

5. Look at the man page for sigprocmask and describe how it is used in in this code.

6. Look at the source code. How is the SIGINT (CTRL-C) signal handler set up in main()?

7. How does the code tell select() to watch stdin for activity?

8. One of the issues with Lab 2 is there was no way to check both the socket and the keyboard for data at the same time, so we could only recode the programs to use half-duplex communication.

    a. How would you use concepts explored in this lab to allow full duplex communication between vcrec and vcsend?

    b. Describe the general code changes you would need to make, but do not actually code the changes (we will code the changes for next week's lab).