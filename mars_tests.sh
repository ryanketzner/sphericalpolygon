#!/bin/bash

mkdir -p articletests
mkdir -p articletests/Mars
mkdir -p articletests/Mars/log
mkdir -p articletests/Mars/output

# Mars Runtime Tests
for f in testpolygons/Mars/*.csv;
do base=$(basename $f .csv);
output=articletests/Mars/output/${base}_Output.csv;
log=articletests/Mars/log/${base}_Log.txt;
echo $output;
exe/PIP.exe $f testqueries/Mars_Queries.csv $output > $log;
done;
