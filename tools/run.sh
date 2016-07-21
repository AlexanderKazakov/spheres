#!/usr/bin/env bash


usage() { echo "Usage: $0
    [-c]  (to clean build directory before compile)
    [-t]  (csv file to handle)
    [-s] (minimal radius of spheres)
    [-b] (maximal radius of spheres)"
    1>&2; exit 1; }


taskfile=""
radius1=""
radius2=""

while getopts ":ct:s:b:" option; do
    case "${option}" in
        c)
            rm -rf build
            ;;
        t)
            taskfile=${OPTARG}
            ;;
        s)
            radius1=${OPTARG}
            ;;
        b)
            radius2=${OPTARG}
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

./build/spheres -t $taskfile -rmin $radius1 -rmax $radius2

output_filename=$taskfile"_result.csv"
gnuplot -e "filename='$output_filename'" tools/gnuplot.txt


# 1 250
# 2 50 250
# 3 150
# 4 50 150

