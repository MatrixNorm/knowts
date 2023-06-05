### demo 1

[](./threads-demo1.c)

```
$ ./a.out 
process id 16474, tid 16474
process(thread) id 16474, tid 16475 
process(thread) id 16474, tid 16476
```

ps и htop показываю по разному:

```
$ ps -T -p 16474 
    PID    SPID TTY          TIME CMD
  16474   16474 pts/0    00:00:00 a.out
  16474   16475 pts/0    00:00:00 a.out
  16474   16476 pts/0    00:00:00 a.out

$ ps -L -p 16474 
    PID     LWP TTY          TIME CMD
  16474   16474 pts/0    00:00:00 a.out
  16474   16475 pts/0    00:00:00 a.out
  16474   16476 pts/0    00:00:00 a.out
```

htop:
```
PID      TGID   Command
16476    16474  ./a.out
16475    16474  ./a.out
16474    16474  ./a.out

# or press H

PID      TGID   Command
16474    16474  ./a.out
```

[Why does `htop` show more process than `ps`](https://unix.stackexchange.com/questions/10362/why-does-htop-show-more-process-than-ps)

By default, htop lists each thread of a process separately, while ps doesn't.


PID - process id
LWP | TID - thread id
TGID - thread group ID, which is the PID of the thread group leader
PGRP | PGID - process group ID, which is the PID of the thread group leader
SID - session ID for the session leader
TPGID - TTY process group ID for the process group leader

### demo 2

[](./threads-demo2.c)

```
$ ./a.out 
the master thread's pthread id is 140678519961408
the master thread's Pid is 26205
The LWPID of master thread is: 26205
the pthread_2 id is 140678516438592
the thread_2's Pid is 26205
The LWPID/tid of thread_2 is: 26206
the pthread_1 id is 140678508045888
the thread_1's Pid is 26205
The LWPID/tid of thread_1 is: 26207
```

```
$ ls /proc/26205/task/
26205  26206  26207
```

```
$ ps -o pid,tid,lwp,tgid,pgrp,sid,tpgid,args -L -C *a.out
    PID     TID     LWP    TGID    PGRP     SID   TPGID COMMAND
  26205   26205   26205   26205   26205   16300   26205 ./a.out
  26205   26206   26206   26205   26205   16300   26205 ./a.out
  26205   26207   26207   26205   26205   16300   26205 ./a.out

$ ps -p 16300 -o pid,ppid,args
    PID    PPID COMMAND
  16300   12147 /bin/bash

$ ps -p 12147 -o pid,ppid,args
    PID    PPID COMMAND
  12147    3715 /usr/bin/python3 /usr/bin/x-terminal-emulator
```