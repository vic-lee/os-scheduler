#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 
#include <iomanip>
#include "header.h"

// using namespace std;

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
        std::queue<process> q;
        int cycle = 0;

        int first_arrival_time = parr -> arrival_time;
        std::cout << "Fist arrival time is: " << first_arrival_time << std::endl;

        for (; cycle < first_arrival_time; cycle++) { 
            print_cycle_info(parr, size, cycle); 
        }

    }

    void rr_scheduler() { }

    void uniprogrammed_scheduler() { }

    void sjf_scheduler() { }

}


int main(int argc, char** argv) {
    namespace s = scheduler;
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
    s::print_process_arr(parr, pcount);
    process* sparr = s::sort_parr_by_arrival(parr, pcount);
    std::cout << "Array after sorting" << std::endl;
    s::print_process_arr(sparr, pcount);
    std::cout << s::randomOS(1) << std::endl;
    s::fcfs(sparr, pcount);
    return 0;
}