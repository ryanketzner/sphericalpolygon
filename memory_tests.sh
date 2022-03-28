#!/bin/bash

# Memory Profile Tests
mkdir -p memorytests/preprocessing

for f in testpolygons/Tennessee/*.csv;
do base=$(basename $f .csv);
valgrind --tool=massif --massif-out-file=massif_out/massif.out.${base} exe/PreprocessMain.exe $f
numEdges=$(echo $base | tr -dc '0-9')
numBytes=$(grep mem_heap_B massif_out/massif.out.${base} | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1)
echo $numEdges $numBytes >> massif_out/memlog.txt
done;
