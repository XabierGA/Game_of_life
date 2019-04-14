#!/bin/bash 

directory=$(pwd)
echo $directory
cp print_mean_std_complexity.py "../"
cp makefile "../"
cp complexity.py "../"
cd ".."&&pwd
script="$1"
echo "10 20 220 420 620 820 1020" > numbers.txt
make generate_with_ffast_native argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_native 10 10 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 20 20 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 220 220 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 420 420 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 620 620 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 820 820 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 1020 1020 1000
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt

python3 -W ignore complexity.py

rm print_mean_std_complexity.py
rm complexity.py
rm data.txt
rm numbers.txt
rm makefile
rm ffast_native
cd $directory



