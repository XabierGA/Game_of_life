#!/bin/bash
N=$1
file=$2
n_steps=$3
delta=$4
theta=$5
graphics=$6
compare_file=$7
script=$8
n_threads=$9
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
	./first_optimization "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_threads"
	((counter++))
done
printf '\n \n \n'
echo "Result with O1 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean

make generate_with_02 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./second_optimization  "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_threads"
	((counter++))
done
printf '\n \n \n'
echo "Result with O2 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean
make generate_with_03 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./third_optimization  "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_threads"
	((counter++))
done
printf '\n \n \n'
echo "Result with O3 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean
make generate_with_ffast_math argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_math "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_threads"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean

make generate_with_ffast_native argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_native "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_threads"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math -march=native flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean

make generate_with_ffast_msse4 argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_msse4 "$N" "$file" "$n_steps" "$delta" "$theta" "$graphics" "$n_steps"
	((counter++))
done
printf '\n \n \n'
echo "Result with -O3 -ffast-math -msse4.2 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
mv result.gal ./compare_gal_files
cd compare_gal_files
./compare "$N" result.gal "$compare_file"
cd ..
make clean


rm print_mean_std.py
rm makefile
cd $directory
