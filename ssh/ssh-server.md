### authorized_keys

The authorized_keys file is not a per-server thing - it's a per-user-on-server thing. If you want someone to access your server as "user1", you place their public key in /home/user1/.ssh/authorized_keys. Now they can login as user1, and only user1.