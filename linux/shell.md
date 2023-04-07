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

## fish shell install

```console
# as a root
apt-get update
apt-add-repository -y ppa:fish-shell/release-3
apt-get update
```

check for available version
```console
apt-cache policy fish
```

```console
apt-get install -y fish=3.5.1-1~bionic
```

set fish shell as default
```console
chsh -s /usr/bin/fish
```

Fish config file: ~/.config/fish/config.fish

Add Node.js to path:
```
fish_add_path ~/opt/node/bin
```