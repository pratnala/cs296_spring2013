#!/bin/bash

echo -n "Number of files and directories is "
find $1 | wc -l
echo "List of executables "
find $1 -executable -type f
