#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 
#include "header.h"

using namespace std;

tuple<process*, int> read_file(string fname) {

    ifstream input_file(fname);

    if (input_file.is_open()) {
        string val;
        input_file >> val;
        int pcount = stoi(val);
        process temp_process;
        process* parr = generate_process_arr(pcount);
        int ctr = 0;
        int p_added = 0;
        while (input_file >> val) {
            if (isalpha(val[0]) || input_file.eof()) break;

            switch (ctr) {
                case 0: temp_process.arrival_time = stoi(val);
                case 1: temp_process.interval = stoi(val);
                case 2: temp_process.cpu_time = stoi(val);
                case 3: temp_process.io_time = stoi(val);
            }

            if (ctr == 3) {
                parr[p_added] = temp_process;
                p_added++;
            }
            if (ctr < EOPROCESS) ctr++;
            else ctr = 0;
        }
        input_file.close();
        return make_tuple(parr, pcount);

    } else {
        cout << "File " << fname << " could not be opened." << endl;
        return make_tuple(nullptr, -1);
    }
}


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
    queue<process> q;
}


void rr_scheduler() { }

void uniprogrammed_scheduler() { }

void sjf_scheduler() { }

int main(int argc, char** argv) {
    string fname = argv[1];
    process* parr;
    int pcount;
    tie(parr, pcount) = read_file(fname);
    cout << "Array before sorting" << endl;
    print_process_arr(parr, pcount);
    process* sparr = sort_parr_by_arrival(parr, pcount);
    cout << "Array after sorting" << endl;
    print_process_arr(sparr, pcount);
    return 0;
}