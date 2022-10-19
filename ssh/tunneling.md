# local port forwarding (local tunneling)

Scenario: Jimmy is at work and wants to connect to his home PC via remote desktop but it's port 3389 is blocked by firewall.

on a work computer:
```bash
>ssh -L 9999:32.43.54.65:3389 jimmy@32.43.54.65 
# 32.43.54.65 - home pc ip address
# 9999 - local port
# 3389 - remote port that is blocked
```