emptystr=""
csvfile="./data/lab05_g01_data.csv"
flag="0"
echo -n "" > $csvfile
for ((i=1;i<=100;i++))
	do
		for ((j=1;j<=100;j++))
		do
			filename="./data/out-$i-$j.txt"
			a=0
			output=""
			echo -n "$i,$j," >> $csvfile
			flag="0"
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
			done < $filename
			echo -e "" >> $csvfile
		done
	done

