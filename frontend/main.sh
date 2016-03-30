#!/bin/bash

# CSCI 3060/ SOFE 3980 Course Project Front End
# Group: Untitled
# Member: Calvin Lo, Albert Fung, Karan Chandwaney

# Purpose: main testing script

# global variable, sets delay between each command if running all tests, doesn't get used if not all tests are run
DELAY=0.1

# function run
# arguments: name of the command to test, served to identify which command is being tested
# purpose: runs test 
function run { 
	# output the command that is being tested
	echo -e "\e[104mTesting $1...\e[0m"

	# change dir into the directory where all the input, output and transaction files are stored
	cd $1

	# stores the number of input files in the current directory (also number of tests)
	num_files_in_currentdir="$(ls *.in -1 | wc -l)"

	# number of output files that pass
	num_output_pass=0

	# number of output files that fail
	num_output_fail=0

	# number of transaction files that pass
	num_trans_pass=0
	
	# number of transactino files that fail
	num_trans_fail=0

	# prints out a file of the summary of the results inside the main results/timestamp/ folder
	echo "SUMMARY OF $1 FOR $timestamp" >> ../results/$timestamp/$1.summary

	# for loop to iterate through the number of input files in the current directory
	for ((i = 1; i <= $num_files_in_currentdir; i++))
	do
		# output the test that is being run
		echo -e "\e[95mRunning test $i\e[0m"

		# stores the name of the input file
		input_filename="$(ls 0$i\_*.in)"

		# go back to main directory
		cd ../

		# run the c++ program with input file as first argument, transaction file as second argument, and output the results
		# into an output file named testnumber.out
		./quit.sh & ./output $1/${input_filename} results/$timestamp/$1/$i.trans > results/$timestamp/$1/$i.out

		# change dir into the folder where all input, output and transaction files are stored for that command
		cd $1

		# stores the name of the expected output file
		output_filename="$(ls 0$i\_*.out)"

		# testing output files
		# run diff command on the output file generated from this test and the expected
		DIFF=$(diff ${output_filename} ../results/$timestamp/$1/$i.out) 

		# if there is a difference (diff returns something)
		if [ "$DIFF" != "" ] 
		then
			# print out that the output test failed
			echo -e "\e[41mTEST ${output_filename} FAILED.\e[0m" 
			# write to the summary file of the command and test that failed
			echo "TEST ${output_filename} FAILED." >> ../results/$timestamp/$1.summary
			# add 1 to the number of output file fails
			num_output_fail=$[num_output_fail+1]
		else # if there is no difference (diff returns nothing)
			# print out that the output file test passed
			echo -e "\e[42mTEST ${output_filename} PASSED.\e[0m" 
			# write to the summary file of the command and test that passed
			echo "TEST ${output_filename} PASSED." >> ../results/$timestamp/$1.summary
			# add 1 to the number of output file passes
			num_output_pass=$[num_output_pass+1]
		fi

		# stores the name of the expected transaction file
		transaction_filename="$(ls 0$i\_*.trans)"
		
		# testing transaction files
		# run diff command on the transaction file generated from this test and the expected
		DIFF2=$(diff ${transaction_filename} ../results/$timestamp/$1/$i.trans) 
		
		# if there is a difference (diff returns something)
		if [ "$DIFF2" != "" ] 
		then
			# print out that the transaction test failed
			echo -e "\e[41mTEST ${transaction_filename} FAILED.\e[0m" 
			# write to the summary file of the command and test that failed
			echo "TEST ${transaction_filename} FAILED." >> ../results/$timestamp/$1.summary
			# add 1 to the number of transaction file fails
			num_trans_fail=$[num_trans_fail+1]
		else # if there is no difference (diff returns nothing)
			# print out that the transaction file passed
			echo -e "\e[42mTEST ${transaction_filename} PASSED.\e[0m"
			# write to the summary file of the command and test that passed
			echo "TEST ${transaction_filename} PASSED." >> ../results/$timestamp/$1.summary
			# add 1 to the number of transactinon file passes
			num_trans_pass=$[num_trans_pass+1]
		fi
	done

	# change dir back to main directory
	cd ../

	# output completed test messages
	echo -e "\e[45m$1 test completed.\e[0m"
	echo -e "\e[45mOUTPUT PASSED: $num_output_pass/$num_files_in_currentdir\e[0m"
	echo -e "\e[45mOUTPUT FAILED: $num_output_fail/$num_files_in_currentdir\e[0m"
	echo -e "\e[45mTRANS PASSED: $num_trans_pass/$num_files_in_currentdir\e[0m"
	echo -e "\e[45mTRANS FAILED: $num_trans_fail/$num_files_in_currentdir\e[0m"
}

# function all
# arguments: none
# purpose: runs all tests with desired arguments
function all { 
	echo "Running all tests..."
	run 0_loginlogout
	sleep $DELAY
	run 1_withdrawal
	sleep $DELAY
	run 2_transfer
	sleep $DELAY
	run 3_paybill
	sleep $DELAY
	run 4_deposit
	sleep $DELAY
	run 5_create
	sleep $DELAY
	run 6_delete
	sleep $DELAY
	run 7_disable
	sleep $DELAY
	run 8_enable
	sleep $DELAY
	run 9_changeplan
	echo -e "\e[45mAll tests completed.\e[0m"
}

# welcome message
echo -e "\e[36m--------------------------------"
echo -e "\e[36m| Welcome to front - end tests |"
echo -e "\e[36m--------------------------------"

# gets the current date and time
timestamp=$( date +%Y-%m-%d_%H-%M-%S )

# create a directroy called results
mkdir results

# change directory into results
cd results

# delete old tests 
rm -rf *

# make directory with current runtime of the script
mkdir $timestamp

# change directory into where the results will be stored for each command
cd $timestamp

# print out the current time and date
echo $timestamp

# make all the subdirs for each command to store output and transaction files
mkdir "0_loginlogout"
mkdir "1_withdrawal"
mkdir "2_transfer"
mkdir "3_paybill"
mkdir "4_deposit"
mkdir "5_create"
mkdir "6_delete"
mkdir "7_disable"
mkdir "8_enable"
mkdir "9_changeplan"

# go back two directories from current dir, or main directory
cd ../../

# prompts the user with what tests to run
echo "Which tests would you like to run? Press enter to run all tests."

# while loop to prompt the user to run another test if they wish to do so
while true; do
	# prompt the user the options of what commands they want to run
	echo -e "\e[36m0) 0_login/logout    3) 3_paybill	 6) 6_delete	    9) 9_changeplan
1) 1_withdrawal	     4) 4_deposit	 7) 7_disable	    
2) 2_transfer	     5) 5_create	 8) 8_enable"
	# read in their choice
	read input
	# case statement, if they enter any number between 0 - 9, it calls the corresponding test, passing in name of command as argument
    case $input in 
        [0] ) run 0_loginlogout ;;
        [1] ) run 1_withdrawal ;; 
		[2] ) run 2_transfer ;; 
		[3] ) run 3_paybill ;; 
		[4] ) run 4_deposit ;; 
		[5] ) run 5_create ;; 
		[6] ) run 6_delete ;; 
		[7] ) run 7_disable ;; 
		[8] ) run 8_enable ;; 
		[9] ) run 9_changeplan;; 
		# if the user enters anything that is not 0 - 9, it runs all tests
		*) echo -e "\e[31m-------------------------------\nInvalid option, running all tests\e[0m"; all ; exit ;;
    esac
done