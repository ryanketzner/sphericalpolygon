#!/bin/bash

mkdir -p articletests
mkdir -p articletests/Tennessee
mkdir -p articletests/Tennessee/log
mkdir -p articletests/Tennessee/output

# Tennessee Runtime Tests
for f in testpolygons/Tennessee/*.csv;
do base=$(basename $f .csv);
output=articletests/Tennessee/output/${base}_Output.csv;
log=articletests/Tennessee/log/${base}_Log.txt;
echo $output;
exe/PIP.exe $f testqueries/Tennessee_Queries.csv $output > $log;
done;
