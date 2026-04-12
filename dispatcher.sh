#!/bin/bash


VM_CREATE="vmc"
VM_SNAP="vms"
VM_REBOOT="vmr"
VM_SHUTDOWN="vmsd"
EMPTY=""
#echo $SSH_ORIGINAL_COMMAND

if [ "$SSH_ORIGINAL_COMMAND" = "$VM_CREATE" ];then 
	echo start creation vm
elif [ "$SSH_ORIGINAL_COMMAND" = "$VM_SNAP" ];then
	echo start snapshot
elif [ "$SSH_ORIGINAL_COMMAND" = "$VM_REBOOT" ];then
	echo vm reboot
elif [ "$SSH_ORIGINAL_COMMAND" = "$VM_SHUTDOWN" ];then
	echo vm shutdown
elif [ -z "$SSH_OROGINAL_COMMAND"];then
	echo argument needed
else
	echo bad argument
fi
