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

    int get_first_proc_by_state(std::vector<Process> const &v, std::string state) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i].io_time >= 0 and v[i].state == state) {
                return i;
            }
        }
        return -1;
    }

    void fcfs_old(std::vector<Process> pv, RandNumAccessor rnum) {
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
        int pvcur = 0;
        std::queue<Process*> running_queue;  
        std::vector<Process*> blocked_vect; 
        std::cout << "------ STARTING FCFS ------" << std::endl;
        int ctr = 0;
        do {
            while ((pvcur < size) && pv[pvcur].arrival_time == cycle) {
                pv[pvcur].state = READY;
                running_queue.push(&pv[pvcur]);
                pvcur++;
            }

            std::cout << "Before cycle " << ctr << std::endl;
            print_process_vect(pv);

            if (running_queue.front() -> state == READY) 
                running_queue.front() -> ready_to_run(rnum);
            running_queue.front() -> decr_cpu_burst(rnum);
            if (running_queue.front() -> state == BLOCKED) {
                blocked_vect.push_back(running_queue.front());
                running_queue.pop();
            }
            
            for (int i = 0; i < blocked_vect.size(); i++) {
                blocked_vect[i] -> decr_io_burst(rnum);
                if (blocked_vect[i] -> state == READY) {
                    running_queue.push(blocked_vect[i]);
                    blocked_vect.erase(blocked_vect.begin() + i);
                }
            }

            // if (cp -> cpu_time == 0 && cp -> io_time == 0) {
            //     cp -> state = TERMINATED;
            //     print_process(*cp);
            // }
            
            ctr++;
        } while (! s::is_procs_terminated(pv) && ctr < 10);

    }

    void fcfs(std::vector<Process> pv, RandNumAccessor rnum) {
        std::queue<Process*> running_queue;
        std::vector<Process*> blocked_vect;
        int cycle = 0;
        std::cout << "---------- FCFS ----------\n" << std::endl;
        while (!is_procs_terminated(pv) && cycle < 10) {
            print_process_vect_simp(pv, cycle);
            cycle++;
        }
    }

    void rr_scheduler() { }

    void uniprogrammed_scheduler() { }

    void sjf_scheduler() { }

    bool comp_proc(Process a, Process b) {
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
    std::vector<s::Process> procvect = s::read_file(fname);
    // int pcount = procvect.size();
    s::print_process_vect(procvect);
    std::sort(procvect.begin(), procvect.end(), s::comp_proc);
    std::cout << "After sorting" << std::endl;
    s::print_process_vect(procvect);

    s::RandNumAccessor rnum;

    s::fcfs(procvect, rnum);

    return 0;
}