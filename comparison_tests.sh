#!/bin/bash

mkdir -p articletests
mkdir -p articletests/comparisons
mkdir -p articletests/comparisons/GMATmain/log
mkdir -p articletests/comparisons/GMATmain/output
mkdir -p articletests/comparisons/PIP/log
mkdir -p articletests/comparisons/PIP/output
mkdir -p articletests/comparisons/PIP/output_prep

# Radiometer
outputPIP=articletests/comparisons/PIP/output/Radiometer_Output.csv;
outputPIPprep=articletests/comparisons/PIP/output_prep/Radiometer_Output.csv;
logPIP=articletests/comparisons/PIP/log/Radiometer_Log.txt;
outputGMAT=articletests/comparisons/GMATmain/output/Radiometer_Output.csv;
logGMAT=articletests/comparisons/GMATmain/log/Radiometer_Log.txt;
exe/PIP.exe testpolygons/Radiometer.csv testqueries/Radiometer_Queries.csv $outputPIPprep $outputPIP > $logPIP;
echo $outputPIP;
exe/GMATmain.exe testpolygons/Radiometer.csv testqueries/Radiometer_Queries.csv $outputGMAT > $logGMAT;
echo $outputGMAT

# 72 deg Square Sensor
outputPIP=articletests/comparisons/PIP/output/Square_72_Output.csv;
outputPIPprep=articletests/comparisons/PIP/output_prep/Square_72_Output.csv;
logPIP=articletests/comparisons/PIP/log/Square_72_Log.txt;
outputGMAT=articletests/comparisons/GMATmain/output/Square_72_Output.csv;
logGMAT=articletests/comparisons/GMATmain/log/Square_72_Log.txt;
exe/PIP.exe testpolygons/Square_72.csv testqueries/Square_72_Queries.csv $outputPIPprep $outputPIP > $logPIP;
echo $outputPIP;
exe/GMATmain.exe testpolygons/Square_72.csv testqueries/Square_72_Queries.csv $outputGMAT > $logGMAT;
echo $outputGMAT

# Tennessees
outputPIP=articletests/comparisons/PIP/output/Tennessee_Output.csv;
outputPIPprep=articletests/comparisons/PIP/output_prep/Tennessee_Output.csv;
logPIP=articletests/comparisons/PIP/log/Tennessee_Log.txt;
outputGMAT=articletests/comparisons/GMATmain/output/Tennessee_Output.csv;
logGMAT=articletests/comparisons/GMATmain/log/Tennessee_Log.txt;
exe/PIP.exe testpolygons/Tennessee.csv testqueries/Tennessee_Queries.csv $outputPIPprep $outputPIP > $logPIP;
echo $outputPIP;
exe/GMATmain.exe testpolygons/Tennessee.csv testqueries/Tennessee_Queries.csv $outputGMAT > $logGMAT;
echo $outputGMAT
