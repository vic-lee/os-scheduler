#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 
#include "header.h"

using namespace std;

void fcfs_scheduler(process* parr, int size) {
    /**
     * Input:   pointer to sorted process array, array size, flag(s)
     * Output:  print on screen. 
     * Algorithm: 
     *      1. Enqueue processes by their entry time, given a process array
     *      2. While the queue is not empty:
     *              Alternate between CPU and I/O bursts (blocked).
     *              Blocked processes, when ready, join the end of the queue. 
     */
    // queue<process> q;
    // int cycle = 0;
    // int first_arrival_time = parr -> arrival_time;
    // for (cycle; cycle < first_arrival_time; cycle++) {
    //     print_cycle_info(parr, size, cycle);
    // }
}

void rr_scheduler() { }

void uniprogrammed_scheduler() { }

void sjf_scheduler() { }

int main(int argc, char** argv) {
    string fname = argv[1];
    process* parr;
    int pcount;
    tie(parr, pcount) = read_file(fname);
    // cout << "Array before sorting" << endl;
    print_process_arr(parr, pcount);
    // process* sparr = sort_parr_by_arrival(parr, pcount);
    // cout << "Array after sorting" << endl;
    // print_process_arr(sparr, pcount);
    // cout << randomOS(1) << endl;
    return 0;
}