#!/bin/bash
# Copyright 2016 ALbert, Janahan, Stuart copyright
<<COMMENT
The daily script is a scirpt that will simulate a day of transactions.
Ensure that if you are running this script you provide a number between 1 to 5 as a parameter.
The reason for this is because based on the number you enter it will run that days tests, if you are
running the script for the first time make sure you run day 1 test first as, it is the transaction that 
create the accounts. 
After creating the accounts you can run any day's tests and it will complete the test as it should.
Another note if you are running the daily script before running the weekly script make sure the folder
Accounts which can be found by:
	Application/Accounts
		has the txt files
			CurrentAccountFile.txt
			MasterAccountFile.txt
				These files need not have any information in them they just need to be created 
				If the files are already there that is fine and you can leave them there.
To run the script ensure that you are in the current directory of the script.
To run it:
	change permissions if not already done:
		chmod +x daily.sh (number between 1-5)
	start execution:
COMMENT

# Path locations we need
appLocation="Application/main.o"
# Picks the folder for the current day we are on
testData="frontendUse/$1"
tfFiles="frontendUse/TF/"
backend="FinalBackend/"
# Builds the banking system
g++ -std=c++11 $(pwd)/Application/main.cpp -o $(pwd)/Application/main.o
cd FinalBackend/
javac Backend.java
cd ..

# Runs the input file though the Banking program and stores the transaction files in a folder
function transactions() {
	# Deletes the merged file if one exists
	rm $(pwd)/merged.txt
	# Clears the folder where the transaction information is located 
	rm $(pwd)/frontendUse/TF/*

	# Loops for the number of files in the current directory 
	for inputFiles in $testData/*.txt
	do
		# path location to where the transaction files should be written
		transactionName=$(pwd)/frontendUse/TF/$(basename ${inputFiles%-*}.txt)
		# runs the program with the input files and writes the transaction files to the path specified by $transactionName
		./$appLocation ./Application/Accounts/CurrentAccountFile.txt $transactionName $inputFiles
	done
}

# Runs the backend of the banking system
function backend() {
	# Sets the location for where the merged file is located
	mergedFile=$(pwd)/merged.txt
	cd FinalBackend/
	# Runs the backend and passes in the merged file which contains all the transactions that happened that day
	java Backend $mergedFile
}
	transactions
	# Copies all the text in the files located at $tfFiles (this information is the transaction details)
	# to a new file called merged
	cat $tfFiles*.txt >> merged.txt
	# Adds on the terminate symbol (the backend we recieved requires this)
	echo "00                                       " >> merged.txt
	backend
	cd ..
	#the master file after every day is saved and written to a folder called MasterFiles
	cat Application/Accounts/MasterAccountFile.txt > MasterFiles/MastersFileDay$1.txt

