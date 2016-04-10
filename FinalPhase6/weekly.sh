#!/bin/bash
# Copyright 2016 ALbert, Janahan, Stuart copyright
<<COMMENT
The weekly script is a script that will simulate a full 5 days of transactions
when first running this script it will clear/remake any MasterAccountFile and CurrentAccountFile that is in there
meaning you always get a fresh start.
To run the script ensure that you are in the current directory of the script.
To run it:
	change permissions if not already done:
		chmod +x wekkly.sh
	start execution:
COMMENT


#Clears/Creates the MasterAccountFile and CurrentAccountFile 
> $(pwd)/Application/Accounts/MasterAccountFile.txt
> $(pwd)/Application/Accounts/CurrentAccountFile.txt

#The current day is initalized to day 1
COUNTER=1
#The loop will run until it reaches 6
while [  $COUNTER -lt 6 ]; do
	# Will run the script daily with the current day it is on
    ./daily.sh $COUNTER
    # Increases the day by one
    let COUNTER=COUNTER+1 
done


