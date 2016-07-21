#!/usr/bin/env bash


usage() { echo "Usage: $0
    [-c] (to clean build directory before compile)
    [-t] (csv file to handle)
    [-r] (radius of spheres)"
    1>&2; exit 1; }


taskfile=""
radius=""

while getopts ":ct:r:" option; do
    case "${option}" in
        c)
            rm -rf build
            ;;
        t)
            taskfile=${OPTARG}
            ;;
        r)
            radius=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done


mkdir -p build
cd build
cmake ..
make

cd ..

./build/spheres -t $taskfile -rmin $radius -rmax $radius

output_filename=$taskfile"_result.csv"
gnuplot -e "filename='$output_filename'" tools/gnuplot.txt

#gnuplot -e \
#"unset key;\
#set datafile separator \";\";\
#set xlabel \"x\";\
#set ylabel \"y\";\
#set zlabel \"z\";\
#splot \"tasks/task1.csv_result.csv\" using 2:3:4:5  w p pt 5 ps 1 palette;\
#pause mouse keypress"


