#!/bin/bash

declare -A arr
arr[1,1]="Reduction.cpp"
arr[1,2]="NoReduction.cpp"  
arr[2,1]="Scalar.cpp"
arr[3,1]="Integral.cpp"
arr[4,1]="MaxMin.cpp"
arr[4,2]="MaxInMinWithNested.cpp"
arr[5,1]="TapeMatrix.cpp"
arr[5,2]="TriangleMatrix.cpp"
arr[6,1]="main.c"
arr[7,1]="reduction.c"
arr[7,2]="atomic.c"
arr[7,3]="critical.c"
arr[7,4]="lock.c"
arr[8,1]="main.c"
arr[9,1]="MaxMin.cpp"
arr[9,2]="MaxInMinWithNested.cpp"

# Проверяем количество аргументов
if [ $# -lt 2 ]; then
    echo "Usage: $0 <directory> <file_number>"
    exit 1
fi

dir=$1
num=$2

filename=${arr[$dir,$num]}

g++ -fopenmp "$dir/$filename" -o main

# Запускаем программу
mkdir results/$1_$2
for (( k=1; k <= 2; k++ ))
do
rm results/$1_$2/result$k.log
touch results/$1_$2/result$k.log
for (( i=4; i <= 16; i++ ))
do
export OMP_NUM_THREADS=$i
./main >> results/$1_$2/result$k.log 2>&1
done
done 
rm main