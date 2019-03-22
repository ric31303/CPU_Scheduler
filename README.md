# CPU Scheduler(without Genetic Algorithm)

## Introduction

This program is to simulate how a single CPU schedule threads through 7(code:0~6) non-machine learning algorithms. The program was implemented by C++.

---

## Schedule Algorithms

FIFO, SJF, SRTF, RR, Priority,Preemtive Priority, Lottery

    code 0: FIFO
    code 1: RR
    code 2: SJF
    code 3: SRTF  
    code 4: Priority
    code 5: PreemptPriority
    code 6: Lottery

---

## Outline

build: The exec file of the program

commands: Contain .sh files of testing script

config: Contain config file

CPU_Scheduler: Program code

results: The output of the program json files for visual interface

tests: Test cases

createTest.py: create random test cases(implemented by Python3)

---

## How to run our code by your own case?

step1:  run the commands below in terminal.

    "python createTest.py test_path threads_num MaxAmountOfBurstsAndIO "

step2:  Modify commands/dev.sh.

    strategy= algorithm code
    fileName="fileName"
    Folder="folderName"

step3: create the same folder in results folder to make sure the program will output to the correct folder after executing

step4: run "sh dev.sh" in terminal

step5: Check results

## How to run our case?

Pick one and run "sh filename.sh" in terminal and check results after running
