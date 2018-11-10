#!bin/bash
#cd /home/michele/Documenti/IE
gcc -o benchmarkO benchmarkO.c
gcc -o benchmarkI benchmarkI.c
#for fs in 10485760 104857600 1073741824 10737418240
#for fs in 10737418240
#do
#	for b in 1024 10240 102400 1048576
	#for b in 512
#	do
#		for i in {1..30}
		#for i in {1..5}
#		do
#			sync
#			echo 1 > /proc/sys/vm/drop_caches
#			./benchmarkO $fs $b
#		done
#	done
#done
#for fs in 10485760 104857600 1073741824 10737418240
for fs in 10485760 104857600 1073741824
#for fs in 1024
do
	for b in 1024 10240 102400 1048576
	#for b in 512
	do
		for i in {1..30}
		#for i in {1..5}
		do
			sync
			echo 1 > /proc/sys/vm/drop_caches
			./benchmarkI $fs $b
		done
	done
done
