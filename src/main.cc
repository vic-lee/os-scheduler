#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 
#include <iomanip>
#include <vector>
#include "header.h"

namespace s = scheduler;

namespace scheduler {

    class RandNumAccessor {
        public:
            int cur_line = 1;

            int randomOS(int u) {
                std::ifstream file_rand_num("random-numbers.txt");
                if (file_rand_num) {
                    int i = 0;
                    std::string line; 
                    while (i < cur_line) {
                        getline(file_rand_num, line);
                        i++;
                    }
                    file_rand_num.close();
                    std::cout 
                        << "Randum Number: " << line 
                        << "\tRet: " << (1 + stoi(line) % u) 
                        << std::endl;
                    cur_line++;
                    return 1 + (stoi(line) % u);
                } else {
                    std::cout 
                        << "Could not open random-numbers.txt. Terminating..." 
                        << std::endl;
                    return -1;
                }
            }
    };


    void fcfs(process* p, int size, RandNumAccessor rnum) {
        /**
         * Input:   pointer to sorted process array, array size, flag(s)
         * Output:  print on screen. 
         * Algorithm: 
         *      1. Enqueue processes by their entry time, given a process array
         *      2. While the queue is not empty:
         *              Alternate between CPU and I/O bursts (blocked).
         *              Blocked processes, when ready, join the end of the queue. 
         */
        process* parr = s::parrcpy(p, size);
        if (!parr) {
            std::cout << "BAD PARR" << std::endl;
            return;
        }
        std::cout << "new parr: " << parr << std::endl;
        int cycle = 0;
        int parr_cur = 0;   // consider making sorted parr a queue
        int first_arrival_time = parr -> arrival_time;
        std::cout << "First arrival time is: " << first_arrival_time << std::endl;

        for (; cycle < first_arrival_time; cycle++) { 
            s::print_cycle_info(parr, size, cycle); 
        }

        do {
            while ((parr_cur < size) && (parr + parr_cur) -> arrival_time == cycle) {
                (parr + parr_cur) -> state = READY;
                s::print_process(*(parr + parr_cur));
                parr_cur++;
            }
            int active_cur = 0;
            while ((parr + active_cur) -> state != READY) active_cur++;

            process* cp = parr + active_cur;
            int burst = rnum.randomOS(cp -> interval);

            if (burst > cp -> cpu_time) burst = cp -> cpu_time;
            cp -> cpu_time -= burst;
            cp -> interval = burst;

            if (cp -> cpu_time == 0) {
                cp -> state = TERMINATED;
            }

        } while (! s::is_procs_terminated(parr, size));
        delete [] parr;

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
    std::vector<process> procvect = s::read_file(fname);
    // int pcount = procvect.size();
    for (int i = 0; i < procvect.size(); i++) {
        s::print_process(procvect[i]);
    }
    // parr = s::sort_parr_by_arrival(parr, pcount);
    // s::RandNumAccessor rnum;
    // std::cout << "parr: " << parr << std::endl;

    // s::fcfs(parr, pcount, rnum);

    return 0;
}