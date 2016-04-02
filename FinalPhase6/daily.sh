#!/bin/bash
# Copyright 2016 ALbert, Janahan, Stuart copyright

appLocation="Application/main.o"
testData="frontendUse/input/"
tfFiles="frontendUse/TF/"
backend="FinalBackend/"

g++ -std=c++11 $(pwd)/Application/main.cpp -o $(pwd)/Application/main.o

function transactions() {
	rm $(pwd)/merged.txt
	rm $(pwd)/frontendUse/TF/*
	for inputFiles in $testData*.txt
	do
		echo $inputFiles
		transactionName=$(pwd)/frontendUse/TF/$(basename ${inputFiles%-*}.txt)
		./$appLocation ./Application/Accounts/CurrentAccountFile.txt $transactionName $inputFiles
	done
}

function backend() {
	mergedFile=$(pwd)/merged.txt
	cd FinalBackend/
	java Backend $mergedFile

}
	transactions
	cat $tfFiles*.txt >> merged.txt
	backend

