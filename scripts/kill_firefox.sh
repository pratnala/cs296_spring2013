#!/bin/bash

firefox_pid=`pidof firefox`
if [[ "$firefox_pid" == "" ]]
then
	echo "Firefox is not running"
else
	firefox_owner=`ps aux | grep $firefox_pid | awk '{print $1 " " $2}' | grep $firefox_pid | awk '{print $1}'`
	if [[ $firefox_owner =~ ^[0-9]+$ ]]
	then
		firefox_owner=`awk -v val=$firefox_owner -F ":" '$3==val{print $1}' /etc/passwd`
	fi
	if [[ "$firefox_owner" == `whoami` ]]
	then
		read -p "Hello $firefox_owner, do you want to kill Firefox? (y/Y for Yes)" decision
		case $decision in
			[Yy] ) kill $firefox_pid; echo "Firefox killed";;
			* ) echo "Firefox not killed"; exit;;
		esac
	else
		echo "You don't have permission to kill Firefox"
	fi
fi
