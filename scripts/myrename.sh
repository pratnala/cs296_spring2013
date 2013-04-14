#!/bin/bash
#referred from http://www.commandlinefu.com/commands/view/8368/bulk-rename-files-with-sed-one-liner

if [ "$1" == "1" ]
then
	for file in src/*.cpp
	do
		mv "$file" "${file/.cpp/.cpp.bak}"
	done
elif [ "$1" == "2" ]
then
	ls ./src/*.cpp | sed -e 'p;s/cpp/cpp.bak/' | xargs -n2 mv
elif [ "$1" == "3" ]  # To rename the file back to .cpp
then
	ls ./src/*.cpp.bak | sed -e 'p;s/cpp.bak/cpp/' | xargs -n2 mv
fi
