#!/bin/bash

if [ -z "$1" ]; then
	echo "Usage: $0 username"
	exit 1
fi

user $1

login_time = $(who | grep "^$user" | head -1 | awk'{print $4}')

if [-z "$login_time" ], then
	echo "User not currently logged in."
	exit 1
fi

login_minutes=$((10#${login_time:0:2}*60 + 10#${login_time:3:2}))
current_minutes=$((10#$(date +%H)*60 + 10#(date +%M))

elapsed =$((current_minutes - login_minutes))
if
