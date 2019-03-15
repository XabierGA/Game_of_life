#!/bin/bash 

directory=$(pwd)
echo $directory
cp print_mean_std_complexity.py "../"
cp makefile "../"
cp complexity.py "../"
cd ".."&&pwd
script="$1"
echo "10 200 400 600 800 1000 1500" > numbers.txt
make generate_with_ffast_native argument="$script"
counter=1
while [ $counter -le 10 ]
do
	./ffast_native 10 ellipse_N_00010.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 200 ellipse_N_00200.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 400 ellipse_N_00400.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 600 ellipse_N_00600.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 800 ellipse_N_00800.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 1000 ellipse_N_01000.gal 100 0.00001 0.2555 0
	((counter++))
done
printf '\n \n \n'
python3 print_mean_std_complexity.py >> data.txt
rm -f time.txt


counter=1
while [ $counter -le 10 ]
do
	./ffast_native 1500 ellipse_N_01500.gal 100 0.00001 0.2555 0
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



