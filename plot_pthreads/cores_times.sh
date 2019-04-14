#!/bin/bash

N=$1 
M=$2 
n_steps=$3
script=$4
directory=$(pwd)
echo $directory 
echo "$N"
echo "$file"
echo "$delta"
echo "$theta"
echo "$graphics"
cp print_mean_complexity.py "../"
cp plot_cores_time.py "../"
cp makefile "../"
cd "../"&&pwd
echo "1 2 3 4 5 6 7 8" > number_of_cores.txt
make generate_cores_1 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./one_core "$N" "$M" "$n_steps" 1
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py > data.txt
rm -f time.txt


make generate_cores_2 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./two_core  "$N" "$M" "$n_steps" 2
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_3 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./third_core  "$N" "$M" "$n_steps" 3
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_4 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./fourth_core  "$N" "$M" "$n_steps" 4
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_5 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./fifth_core "$N" "$M " "$n_steps" 5
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_6 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./six_core  "$N" "$M" "$n_steps" 6
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_7 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./seven_core  "$N" "$M" "$n_steps" 7
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt


make generate_cores_8 argument="$script"
printf '\n \n \n'

counter=1
while [ $counter -le 10 ]
do
	./eigth_core  "$N" "$M" "$n_steps" 8
	((counter++))
done
printf '\n \n \n'
python3 print_mean_complexity.py >> data.txt
rm -f time.txt




python3 -W ignore plot_cores_time.py

rm print_mean_std_complexity.py
rm plot_cores_time.py
rm data.txt
rm number_of_cores.txt
make clean
rm makefile
cd $directory











