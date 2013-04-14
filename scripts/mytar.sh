#!/bin/bash

if [ "$1" == "1" ]
then
	tar -zcvf src.tar.gz src/
elif [ "$1" == "2" ]
then
	cd src
	for file in *
	do
		tar -zcvf "${file}.gz" "$file"
	done 
	cd ..
	tar -cvf src.tar src/*.gz
elif [ "$1" == "3" ]
then
	rm src/*.gz
	rm -f src.tar src.tar.gz
fi
