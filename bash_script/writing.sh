#!/bin/bash
N=$1
M=$2
n_steps=$3
script=$4
directory=$(pwd)
echo $directory
echo "$N"
echo "$file"
echo "$n_steps"
echo "$delta"
echo "$theta"
echo "$graphics"
echo "$compare_file"
cp print_mean_std.py "../"
cp makefile "../"
cd "../"&&pwd
make generate_with_01 argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 10 ]
do
	./first_optimization "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with O1 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_02 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./second_optimization "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with O2 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean
make generate_with_03 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./third_optimization "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with O3 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean
make generate_with_ffast_math argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_math "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_ffast_native argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_native "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math -march=native flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_ffast_msse4 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_native "$N" "$M" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math -msse4.2 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean


rm print_mean_std.py
rm makefile
cd $directory
