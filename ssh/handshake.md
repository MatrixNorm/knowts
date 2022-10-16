



```bash
>ssh -Tv git@github.com

OpenSSH_7.6p1 Ubuntu-4ubuntu0.5, OpenSSL 1.0.2n  7 Dec 2017
debug1: Reading configuration data /home/me/.ssh/config
debug1: /home/me/.ssh/config line 4: Applying options for *
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: /etc/ssh/ssh_config line 19: Applying options for *
debug1: Connecting to github.com [140.82.114.4] port 22.
debug1: Connection established.
debug1: identity file /home/me/.ssh/id_rsa type 0
debug1: key_load_public: No such file or directory
debug1: identity file /home/me/.ssh/id_rsa-cert type -1
```

`id_rsa-cert` is only necessary when your ssh infrastructure requires server and client keys that are signed by a Certificate Authority. I have encountered only one entity that utilized this level of security (military). Most entities will not use this feature. It's only required when someone in IT is super paranoid (military). (https://serverfault.com/a/929093)

```
debug1: Local version string SSH-2.0-OpenSSH_7.6p1 Ubuntu-4ubuntu0.5
debug1: Remote protocol version 2.0, remote software version babeld-f33ee42f
debug1: no match: babeld-f33ee42f
debug1: Authenticating to github.com:22 as 'git'
debug1: SSH2_MSG_KEXINIT sent
debug1: SSH2_MSG_KEXINIT received
debug1: kex: algorithm: curve25519-sha256
debug1: kex: host key algorithm: ecdsa-sha2-nistp256
debug1: kex: server->client cipher: chacha20-poly1305@openssh.com MAC: <implicit> compression: none
debug1: kex: client->server cipher: chacha20-poly1305@openssh.com MAC: <implicit> compression: none
debug1: expecting SSH2_MSG_KEX_ECDH_REPLY
debug1: Server host key: ecdsa-sha2-nistp256 SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM
debug1: Host 'github.com' is known and matches the ECDSA host key.
debug1: Found key in /home/me/.ssh/known_hosts:1
```

The last part of the key exchange has the client extract the host public key (or certificate) from SSH_MSG_KEX_ECDH_REPLY and verifies the signature of exchange hash HS proving ownership of the host private key. To prevent Man-in-the-Middle (MITM) attacks, once the signature is validated the host public key (or certificate) is checked against a local database of known hosts; if this key (or certificate) is not trusted the connection is terminated.

```
debug1: rekey after 134217728 blocks
debug1: SSH2_MSG_NEWKEYS sent
debug1: expecting SSH2_MSG_NEWKEYS
debug1: SSH2_MSG_NEWKEYS received
debug1: rekey after 134217728 blocks
debug1: SSH2_MSG_EXT_INFO received
debug1: kex_input_ext_info: server-sig-algs=<ssh-ed25519-cert-v01@openssh.com,ecdsa-sha2-nistp521-cert-v01@openssh.com,ecdsa-sha2-nistp384-cert-v01@openssh.com,ecdsa-sha2-nistp256-cert-v01@openssh.com,sk-ssh-ed25519-cert-v01@openssh.com,sk-ecdsa-sha2-nistp256-cert-v01@openssh.com,rsa-sha2-512-cert-v01@openssh.com,rsa-sha2-256-cert-v01@openssh.com,ssh-rsa-cert-v01@openssh.com,sk-ssh-ed25519@openssh.com,sk-ecdsa-sha2-nistp256@openssh.com,ssh-ed25519,ecdsa-sha2-nistp521,ecdsa-sha2-nistp384,ecdsa-sha2-nistp256,rsa-sha2-512,rsa-sha2-256,ssh-rsa>
debug1: SSH2_MSG_SERVICE_ACCEPT received
debug1: Authentications that can continue: publickey
debug1: Next authentication method: publickey
debug1: Offering public key: RSA SHA256:7erB122JF3CLo18KRq6AOlDGUQYtV+1Yh2uPcTcGZnQ /home/me/.ssh/id_rsa
debug1: Server accepts key: pkalg rsa-sha2-512 blen 535
debug1: Authentication succeeded (publickey).
Authenticated to github.com ([140.82.114.4]:22).
debug1: channel 0: new [client-session]
debug1: Entering interactive session.
debug1: pledge: network
debug1: client_input_global_request: rtype hostkeys-00@openssh.com want_reply 0
debug1: Sending environment.
debug1: Sending env LC_IDENTIFICATION = ru_RU.UTF-8
debug1: Sending env LC_TIME = ru_RU.UTF-8
debug1: Sending env LC_NUMERIC = ru_RU.UTF-8
debug1: Sending env LC_PAPER = ru_RU.UTF-8
debug1: Sending env LC_MEASUREMENT = ru_RU.UTF-8
debug1: Sending env LC_ADDRESS = ru_RU.UTF-8
debug1: Sending env LC_MONETARY = ru_RU.UTF-8
debug1: Sending env LANG = en_US.UTF-8
debug1: Sending env LC_NAME = ru_RU.UTF-8
debug1: Sending env LC_TELEPHONE = ru_RU.UTF-8
debug1: Sending env LC_CTYPE = en_US.UTF-8
debug1: client_input_channel_req: channel 0 rtype exit-status reply 0
Hi MatrixNorm! You've successfully authenticated, but GitHub does not provide shell access.
debug1: channel 0: free: client-session, nchannels 1
Transferred: sent 3964, received 2904 bytes, in 0.4 seconds
Bytes per second: sent 10519.6, received 7706.6
debug1: Exit status 1
```