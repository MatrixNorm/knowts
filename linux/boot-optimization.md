
```shell
>systemd-analyze blame

>systemd-analyze plot > ~/Pictures/blame.svg
```

## init daemon - PID 1

Is the first programm launched by the kernel after if has booted. 
At boot init has to: start system daemons, configure stuff. Then it seats in background.