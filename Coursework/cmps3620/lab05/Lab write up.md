# CMPS 3620 — Lab 5 Write-Up (Handling Multiple Clients) 

### 1. Unlike vcrec.c, which could only accept a single connection at a time, simple_daemon.c can accept multiple connections at once. How does it accomplish this?  
**Answer:** The parent loops on accept(), forks a child for each new socket, then returns immediately to accept more.

### 2. Try giving a CTRL-C in a telnet terminal. Why does this not cause telnet to exit?  
**Answer:** CTRL-C is sent as ASCII 0x03 over the network, so telnet never receives a SIGINT and stays running.

### 3. What happens when you connect to s_daemon with multiple simultaneous telnet commands? Is there any “overlap” in the commands you type in each s_shell window (i.e. do you get the output for commands typed in another window)?  
**Answer:** There is no overlap, each telnet session is served by its own child process and private pipes.

### 4. Which signals will cause simple_daemon.c to exit gracefully via parent_terminate()?  
**Answer:** SIGINT, SIGHUP, and SIGTERM.

### 5. In dialog_with_client(), the actual work of sending and receiving data from the children processes is done. How does this code tell when you have terminated the connection by giving the s_shell command “quit”?  
**Answer:** After *quit* the shell exits and closes its stdout pipe; read() on that pipe returns 0, so the handler closes the socket and ends.

### 6. What does the child_terminate() function do? How does it differ from the kill_child() function?  
**Answer:** child_terminate() (parent) reaps finished children and frees their slot; kill_child() (child) handles SIGTERM by closing its socket and exiting.

### 7. Given what you have learned in this lab, how do you think the SSH daemon on Odin handles an incoming SSH connection from Putty? Hint: look at the command ps x right after you've logged in to Odin and note what processes you have running.  
**Answer:** The master `sshd` listens on port 22, forks a child for every login, and each child starts your shell (and sftp-server if needed), so every terminal runs in its own separate process.