
To check which users are in the kvm group, use
>grep kvm /etc/group
kvm:x:135:

>whoami
me
>sudo adduser me kvm

>grep kvm /etc/group
kvm:x:135:me
