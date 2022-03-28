### fish

```console
sudo apt-add-repository ppa:fish-shell/release-3
sudo apt-get update
sudo apt-get install fish
```

запуск

```console
fish
```

set as default

```console
chsh -s /usr/bin/fish
```

chsh is a setuid program that modifies the /etc/passwd file

```console
cat /etc/passwd | grep kyky
#kyky:x:1000:1000:kyky:/home/kyky:/usr/bin/fish
```
