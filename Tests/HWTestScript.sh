#!/bin/bash
# Copyright 2016 Jason, Stuart, Muhammad copyright
 <<COMMENT
 The HHTestScript is a script that will automatically run though all tests for the
 Hard Water Banking system. 
 Ensure that each test folder is created and has the following sub-directories with 
 the appropriate files:
 	actual-ouput: no files required
 	actual-TF: no files required
 	compare:
 		output: no files required
 		TF: no files required
 	input: the input files to pipe into the program for the test
 		example of an input file:
	 		name: 01-login-admin-I.txt
	 		contents:
	 			login
	 			Admin
	 			logout
 	output: the expected std output of the program for the test
 		example of an output file
 			name: 01-login-admin-O.txt
 			contents:
 				Welcome to the Bank of Hard Water. Please enter login:
				Please enter Standard or Admin:
				Options: withdrawal, transfer, paybill, deposit, create, delete, disable, 
				changeplan, logout, enable
				Please enter a command:
				Welcome to the Bank of Hard Water. Please enter login:
	TF: the expected transaction file for the test
		example of a TF file:
			name: 01-login-admin-TF.txt
			contents:
				10                      00000 00000.00 A 
				00                      00000 00000.00 A 
To run the script ensure that you are in the current directory of the Test folder.
To run it:
	change permissions if not already done:
		chmod +x HWTestScript.sh
	start execution:
		./HWTestScript.sh
To modify the order of the test or add a unit test, call the checkTest function with the name of
the test folder:
	checkTest "login"
COMMENT
# Path locations we need
appLocation+="/../Application/main.o"
AccountFile="/../Application/Accounts/valid-accounts.txt"
# Counters used to let us know how many test passed or failed
passCounter=0
failCounter=0
# build the banking system
g++ -std=c++11 $(pwd)/../Application/main.cpp -o $(pwd)/../Application/main.o
# Runs the input file though the Banking program and compares the output and transaction files
function checkTest(){
	# Clears the comparing folders
	rm $(pwd)/$1/compare/output/*
	rm $(pwd)/$1/compare/TF/*
	echo -e "\e[1;97;46mRunning $1 Tests\e[0m"
	# Loops for the number of files in the current directory of input
	for inputFiles in $1/input/*.txt
	do
		# Sets the variable outputName to the directory and name of the file we want to write
		outputName=./$1/actual-output/$(basename ${inputFiles%-I*}"-AO.txt")
		# Sets the variable transactionName to the directory and name of the file we want to write
		transactionName=$(pwd)/$1/actual-TF/$(basename ${inputFiles%-I*}"-TFO.txt")
		# Creates the actual transaction files
		> $transactionName
		# Runs the program with the input files and writes the output of the program to the file specified by outputName
		./$appLocation ./Accounts/valid-accounts $transactionName $inputFiles > $outputName	
	done
	# Loops for the number of files in the current directory of actual-output
	for actualOutput in ./$1/actual-output/*.txt
	do
		# Sets the variable to the name of the file without the -AO at the end of it
		simpleName=${actualOutput%-AO*}
		printf "Checking output of test $(basename $simpleName)"
		# Compares the files with matching names from the actual-output directory and the output directory and write the difference to the compare/output directory
		diff $actualOutput ./$1/output/$(basename $simpleName-O.txt) > ./$1/compare/output/$(basename $simpleName-C.txt)
		# Checks to see if there is any difference between the two files being compare if so it will enter the if block
		if [ -s ./$1/compare/output/$(basename $simpleName-C.txt) ]
		then
			# Increases the failed counter by one
			((failCounter=failCounter+1))
			RED='\033[0;31m'
			NC='\033[0m'
			printf " ${RED}fail${NC}\n"
		# If the files being compared are the same it will enter the else block
		else
			# increased the pass counter by one
			((passCounter=passCounter+1))
			GREEN='\033[0;32m'
			NC='\033[0m'
			printf " ${GREEN}pass${NC}\n"
		fi
	done
	SEP='\033[0;34m'
	NM='\033[0m'
	printf "${SEP}----------------------------------------------------------------------${NM}\n"
	# Loops for the number of files in the specified TF directory 
	for TF in ./$1/TF/*.txt
	do
		simpleN=${TF%-TF*}
		printf "Checking Transaction File $(basename $simpleN)"
		# Compares two files with the same name from the specified actual-TF directory and the specified TF directory
		diff $TF $(pwd)/$1/actual-TF/$(basename $simpleN-TFO.txt) > ./$1/compare/TF/$(basename $simpleN-CTF.txt)
		# Checks to see if there is any difference between the two files being compared if so it will enter the if block
		if [ -s ./$1/compare/TF/$(basename $simpleN-CTF.txt) ]
		then
			((failCounter=failCounter+1))
			RED='\033[0;31m'
			NC='\033[0m' # No Color
			printf " ${RED}fail${NC}\n"
		# If the files being compared are the same it will enter the else block
		else
			((passCounter=passCounter+1))
			GREEN='\033[0;32m'
			NC='\033[0m'
			printf " ${GREEN}pass${NC}\n"
		fi
	done
	SEPERATOR='\033[0;33m'
	NN='\033[0m'
	printf "${SEPERATOR}======================================================================${NN}\n"
}
#Calls the function for every directory that involves test
checkTest "login"
checkTest "logout"
checkTest "withdrawal"
checkTest "transfer"
checkTest "paybill"
checkTest "deposit"	
checkTest "create"
checkTest "delete"
checkTest "disable"
checkTest "enable"
checkTest "changeplan"
echo -e "\e[1;97;42mThe number of test passed: $passCounter\e[0m"
echo -e "\e[1;97;41mThe number of test failed: $failCounter\e[0m " 