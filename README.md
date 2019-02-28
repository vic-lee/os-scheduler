# Lab 2: Scheduling 

1. FCFS: queue
2. RR w/ quantum 2
3. Uniprogrammed 
4. Shortest Job First (SJF) 

## Getting started

```
cd src
g++ -Wall -std=c++11 main.cc utils/*
./a.out ../test/in/input-x
```

## Notes on lab2 
- Altering b/t CPU bursts and IO bursts
- B is used to calculate the next CPU burst time
- IO is used to calculate the next IO burst time
- To ensure deterministic results, read _one by one_ from the `random-numbers.txt` file

```
while (!all process terminated) {
  do_blocked_process();
  do_running_process();
  do_arriving_process();
  do_ready_process();
}
```

Thoughts: 
- Implement a data structure similar to a process table? (Is there a better way to implement this table other than an array?)