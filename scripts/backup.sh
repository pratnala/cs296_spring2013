#!/bin/bash
#Here we assume that the pendrive is mounted and the location given for the 
#backup is perfectly valid
#Also, we assume that the folder called "backup" is located here (in the path given) and that it is not included already in the
#path

mkdir -p $1/backup

for file in ./src/*
do
   cp -u $file $1/backup
done

