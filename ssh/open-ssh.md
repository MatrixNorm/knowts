
# known_hosts

known_hosts file contains a list of all servers to which you connect.

### HashKnownHosts yes/no

If known_hosts is not hashed an attacker who gained access to your password or unencrypted private key would simply need to iterate down the known_hosts until your credentials were accepted.

https://security.stackexchange.com/a/236886
<blockquote>
I believe, that there are no benefits of hashing the hostname in the known_hosts file. That hash even provides a false feeling of security. It should be removed as soon as possible. The reason is, that ssh stores each host twice, both by name and by IP address. There are only 2^32 = 4294967296 different IP addresses. However, modern GPUs can brute force SHA-1 at a rate of 12 Gigahashes per second. In other words: A single GPU unhashes an IP address in less than one second.
</blockquote>