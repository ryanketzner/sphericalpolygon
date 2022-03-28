#!/bin/bash

# Memory Profile Tests
outdir=memorytests/setup
logfile=$outdir/memlog.txt
mkdir -p outdir

for f in testpolygons/Tennessee/*.csv;
do base=$(basename $f .csv);
outfile=$outdir/massif.out.${base}
valgrind --tool=massif --massif-out-file=$outfile exe/LoadInputMain.exe $f
numEdges=$(echo $base | tr -dc '0-9')
numBytes=$(grep mem_heap_B $outfile | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1)
echo $numEdges $numBytes >> $logfile
done;
