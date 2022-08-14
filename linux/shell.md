### /etc/shell
list of valid login shells
```bash
$cat /etc/shells
/bin/sh
/bin/dash
/bin/bash
/bin/rbash
/bin/zsh
/usr/bin/zsh
```

## chsh
command to change login shell
```bash
$chsh -s /usr/bin/fish
```

```bash
$cat /etc/passwd | grep ^me:
me:x:1000:1000:me,,,:/home/me:/usr/bin/zsh
```
