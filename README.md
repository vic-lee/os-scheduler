# Lab 2: Scheduling 

1. FCFS: queue
2. RR w/ quantum 2
3. Uniprogrammed 
4. Shortest Job First (SJF) 

## Getting started

To compile the program, do:
```
cd src
make
```
Then, to run the program, do:
```
../bin/exec ../test/in/input-x                    // where x is the input number
../bin/exec --verbose ../test/in/input-x          // display detailed output
../bin/exec --show-random ../test/in/input-x      // display randomOS() output
```

## Project architecture

The project is in the `/src` folder. The project starting point is `main.cc`, and compiled by `makefile`. All symbols are stored under namespace `Scheduler`. 

```
.
├── header.h
├── main.cc
├── makefile
├── process             // The process class
│   ├── process.cc
│   └── process.h
├── random-numbers.txt
├── scheduler           // Scheduling algorithms
│   ├── scheduler.cc
│   └── scheduler.h
└── utils               // Supporting services
    ├── compproc.cc     // Comparing processes
    ├── printer.cc      // Scheduler output
    ├── randnum         // Random Number Accessor
    │   ├── randnum.cc
    │   └── randnum.h
    ├── schedutil.h
    ├── statcalc.cc     
    └── util.cc
```
