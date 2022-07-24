## How can I check the available version of a package in the repositories?

$apt-cache policy fish
```
fish:
  Installed: (none)
  Candidate: 3.5.1-1~bionic
  Version table:
     3.5.1-1~bionic 500
        500 http://ppa.launchpad.net/fish-shell/release-3/ubuntu bionic/main amd64 Packages
     2.7.1-3 500
        500 http://archive.ubuntu.com/ubuntu bionic/universe amd64 Packages
```