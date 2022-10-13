
# known_hosts

known_hosts file contains a list of all servers to which you connect.

### HashKnownHosts yes/no

If known_hosts is not hashed an attacker who gained access to your password or unencrypted private key would simply need to iterate down the known_hosts until your credentials were accepted.

https://security.stackexchange.com/a/236886
<blockquote>
I believe, that there are no benefits of hashing the hostname in the known_hosts file. That hash even provides a false feeling of security. It should be removed as soon as possible. The reason is, that ssh stores each host twice, both by name and by IP address. There are only 2^32 = 4294967296 different IP addresses. However, modern GPUs can brute force SHA-1 at a rate of 12 Gigahashes per second. In other words: A single GPU unhashes an IP address in less than one second.
</blockquote>

E.g. first push to github.com:
```
> git push
The authenticity of host 'github.com (140.82.112.3)' can't be established.
ECDSA key fingerprint is SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added 'github.com,140.82.112.3' (ECDSA) to the list of known hosts.
```

**ECDSA - Elliptic Curve Digital Signature Algorithm**

When using ssh to connect to a remote server, the server will present public key that can be used to identify the server. As part of session key negotiations, the client will ask the server to prove possession of the private key that goes with this public key.

The fingerprint is a short version of the server's public key; it is easier for you to verify than the full key. Public key fingerprints can be used to validate a connection to a remote server. It is very hard to spoof another public key with the same fingerprint. 

Fingerprints are generated from a hashing of the public key using either the md5 or sha256 hashing algorithm. When you connect to a machine for the first time you do not have the fingerprint in your known_hosts, so ssh has nothing to compare it to, so it asks you. GitHub for example publish it's SSH public key fingerprints on a [web page](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/githubs-ssh-key-fingerprints)

These are GitHub's public key fingerprints:

* SHA256:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8 (RSA)
* SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM (ECDSA)
* SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU (Ed25519)

### [Securely add a host (e.g. GitHub) to the SSH known_hosts file](https://serverfault.com/questions/856194/securely-add-a-host-e-g-github-to-the-ssh-known-hosts-file)

The most important part of "securely" adding a key to the known_hosts file is to get the key fingerprint from the server administrator. In the case of GitHub, normally we can't talk directly to an administrator. However, they put the key on their web pages so we can recover the information from there.

### ssh-keyscan

ssh-keyscan is a command for gathering the public host keys. For successful host key collection, you do not need login access to the machines that are being scanned, nor does the scanning process involve any encryption. If a machine being scanned is down or is not running sshd, the public key information cannot be collected for that machine.

```
> ssh-keyscan github.com

github.com ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAq2A7hRGmdnm9tUDbO9IDSwBK6TbQa+PXYPCPy6rbTrTtw7PHkccKrpp0yVhp5HdEIcKr6pLlVDBfOLX9QUsyCOV0wzfjIJNlGEYsdlLJizHhbn2mUjvSAHQqZETYP81eFzLQNnPHt4EVVUh7VfDESU84KezmD5QlWpXLmvU31/yMf+Se8xhHTvKSCZIFImWwoG6mbUoWf9nzpIoaSjB+weqqUUmpaaasXVal72J+UX2B+2RPW3RcT0eOzQgqlJL3RKrTJvdsjE3JEAvGq3lGHSZXy28G3skua2SmVi/w4yCE6gbODqnTWlg7+wC604ydGXA8VJiS5ap43JXiUFFAaQ==
# github.com:22 SSH-2.0-babeld-133f2b0d
github.com ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBEmKSENjQEezOmxkZMy7opKgwFB9nkt5YRrYMjNuG5N87uRgg6CLrbo5wAdT/y6v0mKV0U2w0WZ2YB/++Tpockg=
# github.com:22 SSH-2.0-babeld-133f2b0d
github.com ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIOMqqnkVzrm0SdG6UOoqKLsabgH5C9okWi0dh2l9GKJl
```

### ssh-keygen

```
> ssh-keyscan github.com | ssh-keygen -lf -

2048 SHA256:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8 github.com (RSA)
256 SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM github.com (ECDSA)
256 SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU github.com (ED25519)
```

```
> echo "github.com ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBEmKSENjQEezOmxkZMy7opKgwFB9nkt5YRrYMjNuG5N87uRgg6CLrbo5wAdT/y6v0mKV0U2w0WZ2YB/++Tpockg=" > /tmp/key.pub

> ssh-keygen -lf /tmp/key.pub
256 SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM github.com (ECDSA)
```