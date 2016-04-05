#!/bin/bash
# Copyright 2016 ALbert, Janahan, Stuart copyright

COUNTER=2
while [  $COUNTER -lt 6 ]; do
    echo The counter is $COUNTER
    ./daily.sh $COUNTER
    let COUNTER=COUNTER+1 
done


