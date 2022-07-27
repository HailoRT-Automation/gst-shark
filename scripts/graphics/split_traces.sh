#!/bin/bash
set -e

split_traces_dir=$1

mkdir -p $split_traces_dir

# awk '!/gsttracer.c|gsttracerrecord.c/' $GST_DEBUG_FILE > $split_traces_dir/filtered.txt

#read value of environment variable GST_TRACERS and split it into an array of tracers
IFS=';' read -ra tracers <<< "$GST_TRACERS"

for trace in "${tracers[@]}"
do
    #check if trace is not graphic and if not, do next line
    if [[ $trace == "graphic" ]]; then
        continue
    fi
    
    cat $GST_DEBUG_FILE | awk '!/gsttracer.c|gsttracerrecord.c/' | grep $trace > $split_traces_dir/$trace.log
    # cat $split_traces_dir/filtered.txt | grep $trace > $split_traces_dir/$trace.log
done

# rm $split_traces_dir/filtered.txt

