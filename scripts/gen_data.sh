
for ((i = 1; i <= 100; i++))
do
	for ((j = 1; j <= 100; j++))
	do
		./mybins/cs296_exe_01 $i > ./data/out-$i-$j.txt
	done
done
