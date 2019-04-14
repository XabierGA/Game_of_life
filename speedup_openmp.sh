#!/bin/bash
counter=1
while [ $counter -le 8 ]
do
	export OMP_NUM_THREADS=$counter
	echo "Iteration"
	./openmp 2520 2520 200
	((counter++))
done

echo "Finished" 
