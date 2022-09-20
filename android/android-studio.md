## Installation on Linux

1. Download `android-studio-*-linux.tar.gz`. Extract archive. Move `android-studio` folder to desired location e.g. `~/opt/android`.

2. Run `android-studio/bin/studio.sh`. Select default Jre packaged with Android Studio. Choose folder for Android SDK e.g. `android-studio/SDK`

3. Add `android-studio/bin/studio.sh` to Gnome quick start via Main Menu app.

## Install qemu, kvm virtualization stuff

```shell
~$ sudo apt-get install qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils
~$ sudo apt-get install virtinst virt-manager
```

```shell
~$ sudo adduser me kvm
~$ grep kvm /etc/group
```


## Add android system image to AS

In latest versions of AS there is no image for Android 9.0 Google X86_ARM. How to add it:

1. Downdload archive of an image e.g. `x86-28_r10.zip`. Extract it.
2. Move `x86-28_r10` folder to `~/opt/android/SDK/system-images/android-28`

>What is this android-28 folder?

28 is API level. 
>What version of Android is API 28?

Android 9

Single Android version may correspond to one or many API versions, e.g. Android 9 (API level 28) or Android 12 (API levels 31, 32).

## Android Debug Bridge (ADB)

Located at `../SDK/platform-tools/adb`