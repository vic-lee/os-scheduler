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


    void fcfs(std::vector<process> pv, RandNumAccessor rnum) {
        /**
         * Input:   pointer to sorted process array, array size, flag(s)
         * Output:  print on screen. 
         * Algorithm: 
         *      1. Enqueue processes by their entry time, given a process array
         *      2. While the queue is not empty:
         *              Alternate between CPU and I/O bursts (blocked).
         *              Blocked processes, when ready, join the end of the queue. 
         */

        int cycle = 0;
        int size = pv.size();
        int parr_cur = 0;   // consider making sorted parr a queue
        int first_arrival_time = pv[0].arrival_time;
        std::cout << "First arrival time is: " << first_arrival_time << std::endl;
        do {
            while ((parr_cur < size) && pv[parr_cur].arrival_time == cycle) {
                pv[parr_cur].state = READY;
                s::print_process(pv[parr_cur]);
                parr_cur++;
            }

            int active_cur = 0;
            while (pv[active_cur].state != READY) active_cur++;

            process* cp = &pv[active_cur]; 
            int burst = rnum.randomOS(cp -> interval);

            if (burst > cp -> cpu_time) burst = cp -> cpu_time;
            cp -> cpu_time -= burst;
            cp -> interval = burst;

            if (cp -> cpu_time == 0) {
                cp -> state = TERMINATED;
                print_process(*cp);
            }

        } while (! s::is_procs_terminated(pv));

    }

    void rr_scheduler() { }

    void uniprogrammed_scheduler() { }

    void sjf_scheduler() { }

    bool comp_proc(process a, process b) {
        if (a.arrival_time < b.arrival_time) return true;
        if (a.arrival_time == b.arrival_time) return a.pid < b.pid;
        return false;
    }

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
    s::print_process_vect(procvect);
    std::sort(procvect.begin(), procvect.end(), s::comp_proc);
    std::cout << "After sorting" << std::endl;
    s::print_process_vect(procvect);

    s::RandNumAccessor rnum;

    s::fcfs(procvect, rnum);

    return 0;
}