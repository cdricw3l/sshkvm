# 1: installer KVM

Step 1: Install the required packages

```
$ sudo apt -y install bridge-utils cpu-checker libvirt-clients libvirt-daemon qemu qemu-kvm

```

Step 2: Check virtualisation capabilities

Execute the following command to make sure your processor supports virtualisation capabilities:

```
$ kvm-ok

``` 

The output of this command is pretty straightforward and clearly indicates whether KVM can be used or not:

INFO: /dev/kvm exists
KVM acceleration can be used


# 2: installer SQLite et la bibliothèque de développement SQLite

```
sudo apt update
sudo apt install sqlite3
sudo apt install libsqlite3-dev

```

libsqlite3-dev est la librairie de developement qui permet d'exploiter l'api SQLite.