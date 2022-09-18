>egrep -c '(vmx|svm)' /proc/cpuinfo

#### Packages to install
* qemu-kvm
* libvirt-clients
* libvirt-daemon
* libvirt-daemon-system
* bridge-utils
  >This package contains utilities for configuring the Linux Ethernet bridge in Linux. The Linux Ethernet bridge can be used for connecting multiple Ethernet devices together. The connecting is fully  transparent: hosts connected to one Ethernet device see hosts connected to the other Ethernet devices directly.
* virtinst
  >Virtinst is a set of commandline tools to create virtual machines using libvirt
  - virt-install: provision new virtual machines
  - virt-clone: clone existing virtual machines
  - virt-image: create virtual machines from an image description
  - virt-convert: convert virtual machines between formats
* virt-manager
  > The virt-manager application is a desktop user interface for managing virtual machines through libvirt. 
