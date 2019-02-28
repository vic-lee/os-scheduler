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

    void fcfs(std::vector<Process> pv, RandNumAccessor rnum) {
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
        int pvcur = 0;   // consider making sorted parr a queue
        // int first_arrival_time = pv[0].arrival_time;
        // std::cout << "First arrival time is: " << first_arrival_time << std::endl;
        std::cout << "STARTING FCFS" << std::endl;
        int ctr = 0;
        do {
            while ((pvcur < size) && pv[pvcur].arrival_time == cycle) {
                pv[pvcur].state = READY;
                std::cout << "Adding process " << pv[pvcur].pid << std::endl;
                // s::print_process(pv[pvcur]);
                pvcur++;
            }

            int blocked_cur = get_first_proc_by_state(pv, BLOCKED);
            int running_cur = get_first_proc_by_state(pv, RUNNING);
            int ready_cur = -1;
            if (running_cur == -1)
                ready_cur = get_first_proc_by_state(pv, READY);

            if (ready_cur != -1) {

                Process* cp = &pv[ready_cur]; 
                
                if (cp -> remaining_cpu_burst == 0) {
                    int burst = rnum.randomOS(cp -> interval);
                    if (burst > cp -> cpu_time) burst = cp -> cpu_time;
                    cp -> interval = burst;
                    cp -> remaining_cpu_burst = burst;
                    cp -> state = RUNNING;
                } 
                
                if (cp -> remaining_cpu_burst == 0) cp -> state = BLOCKED;
            }

            if (blocked_cur != -1) {

                Process* bp = &pv[blocked_cur];

                if (bp -> remaining_io_burst == 0) {
                    int burst = rnum.randomOS(bp -> interval);
                    if (burst > bp -> io_time) burst = bp -> io_time;
                    bp -> interval = burst;
                    bp -> remaining_io_burst = burst;
                } else {
                    bp -> remaining_io_burst --;
                    bp -> io_time --;                   
                }

                if (bp -> remaining_io_burst == 0) bp -> state = READY;

            }

            std::cout << "Before cycle " << ctr << std::endl;
            print_process_vect(pv);
            
            running_cur = get_first_proc_by_state(pv, RUNNING);
            blocked_cur = get_first_proc_by_state(pv, BLOCKED);

            if (running_cur != -1) {
                // Process* ap = &pv[running_cur];
                // pv[running_cur].decr_cpu_burst();
            }

            if (blocked_cur != -1) {
                // Process* bp = &pv[blocked_cur];
                // pv[blocked_cur].decr_io_burst();
            }
            

        

            // if (cp -> cpu_time == 0 && cp -> io_time == 0) {
            //     cp -> state = TERMINATED;
            //     print_process(*cp);
            // }
            
            ctr++;
        } while (! s::is_procs_terminated(pv) && ctr < 10);

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