emptystr=""
csvfile="./data/lab05_g01_data.csv"
flag="0"
temp=""
echo -n "" > $csvfile
for ((i=1;i<=100;i++))
   do
	for ((j=1;j<=100;j++))
           do 
	      temp=`./mybins/cs296_exe_01 $i`
	      output=""
	      echo -n "$i,$j," >> $csvfile
	      flag="0"
	      echo "$temp" |
	      while read line			
	      do
	 	output=$(echo $line | grep -oE '[0-9]+.[0-9]+|[0-9]+')
	 	if [ "$flag" == "1" ] 
		then   
	        	echo -n $output >> $csvfile
			if [ "$output" != "$emptystr" ]
			then
				echo -n "," >> $csvfile
			fi
		fi
				flag="1"
	      done
	      echo -e "" >> $csvfile
	   done
   done

