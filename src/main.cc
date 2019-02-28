#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 
#include <iomanip>
#include "header.h"

namespace s = scheduler;

namespace scheduler {

    void fcfs(process* parr, int size) {
        /**
         * Input:   pointer to sorted process array, array size, flag(s)
         * Output:  print on screen. 
         * Algorithm: 
         *      1. Enqueue processes by their entry time, given a process array
         *      2. While the queue is not empty:
         *              Alternate between CPU and I/O bursts (blocked).
         *              Blocked processes, when ready, join the end of the queue. 
         */
        std::deque<process> d;
        int cycle = 0;
        int parr_cur = 0;   // consider making sorted parr a queue
        int dcur = 0;
        int first_arrival_time = parr -> arrival_time;
        std::cout << "First arrival time is: " << first_arrival_time << std::endl;

        for (; cycle < first_arrival_time; cycle++) { 
            s::print_cycle_info(parr, size, cycle); 
        }
        int ctr = 0;
        int ln = 1;
        do {
            while ((parr_cur < size) && (parr + parr_cur) -> arrival_time == cycle) {
                (parr + parr_cur) -> state = READY;
                s::print_process(*(parr + parr_cur));
                d.push_back(*(parr + parr_cur));
                parr_cur++;
            }
            std::cout << "Finish pushing onto deque" << std::endl;
            while (d.at(dcur).state != READY) dcur++;
            process curproc = d.at(dcur);
            int burst = s::randomOS(curproc.interval, ln);
            ln++;
            if (burst > curproc.cpu_time) burst = curproc.cpu_time;
            curproc.interval = burst;
            std::cout << burst << std::endl;
            ctr++;
        } while (!d.empty() && ctr < 10);

    }

    void rr_scheduler() { }

    void uniprogrammed_scheduler() { }

    void sjf_scheduler() { }

}


int main(int argc, char** argv) {
    std::string fname;
    try {
        fname = argv[1];
    } catch (std::exception& e) {
        std::cout << "Please provide a filename as an argument." << std::endl;
        return 0;
    }
    process* parr;
    int pcount;
    std::tie(parr, pcount) = s::read_file(fname);
    std::cout << "Array before sorting" << std::endl;
    // s::print_process_arr(parr, pcount);
    process* sparr = s::sort_parr_by_arrival(parr, pcount);
    std::cout << "Array after sorting" << std::endl;
    // s::print_process_arr(sparr, pcount);
    s::fcfs(sparr, pcount);
    free(parr);
    free(sparr);
    return 0;
}