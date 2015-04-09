#!/bin/bash

# SED_CMD="\
# 	/^@@@*/p; \
# 	/Error.*;/p; \
#         /Total number of runs/p; \
#         /Sleepset killed runs/p;"
 SED_CMD="\
 /err=/p;
"

for f in *.check_result_race 
do 
   cp -v $f $f/check_result_race_sc
done

for   i in `seq 0 9`
do
    
 #mv  ~/src/examples/tso/checkresults/podwr00$i/result.autorace.filtered ~/src/examples/tso/regression-examples/podwr00$i/check_result_race
    
# mv  ~/src/examples/tso/checkresults/mix00$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix00$i/check_result_race
# mv  ~/src/examples/tso/checkresults/mix01$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix01$i/check_result_race
# mv  ~/src/examples/tso/checkresults/mix02$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix02$i/check_result_race
# mv  ~/src/examples/tso/checkresults/mix03$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix03$i/check_result_race
# mv  ~/src/examples/tso/checkresults/mix04$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix04$i/check_result_race
# mv  ~/src/examples/tso/checkresults/mix05$i/result.autorace.filtered ~/src/examples/tso/regression-examples/mix05$i/check_result_race

#  mv  ~/src/examples/tso/checkresults/rfi00$i/result.autorace.filtered ~/src/examples/tso/regression-examples/rfi00$i/check_result_race
# mv  ~/src/examples/tso/checkresults/rfi01$i/result.autorace.filtered  ~/src/examples/tso/regression-examples/rfi01$i/check_result_race

#mv  ~/src/examples/pso/checkresults/safe00$i/result.autorace.filtered ~/src/examples/pso/regression-examples/safe00$i/check_result_race
#mv  ~/src/examples/pso/checkresults/safe01$i/result.autorace.filtered  ~/src/examples/pso/regression-examples/safe01$i/check_result_race
#mv  ~/src/examples/pso/checkresults/safe02$i/result.autorace.filtered ~/src/examples/pso/regression-examples/safe02$i/check_result_race
#mv  ~/src/examples/pso/checkresults/safe03$i/result.autorace.filtered  ~/src/examples/pso/regression-examples/safe03$i/check_result_race
done
#sed -n "$SED_CMD"  $1 > ${1}.results.filtered;
#cut -d'=' -f2  ${1}.results.filtered >paint.txt;

#find -name "main.c" | wc -l main.c
#wc -l `find -name 'main.c'` 
