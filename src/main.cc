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
        int pvcur = 0;   // consider making sorted parr a queue
        int first_arrival_time = pv[0].arrival_time;
        std::cout << "First arrival time is: " << first_arrival_time << std::endl;
        int ctr = 0;
        do {
            while ((pvcur < size) && pv[pvcur].arrival_time == cycle) {
                pv[pvcur].state = READY;
                std::cout << "Adding process " << pv[pvcur].pid << std::endl;
                s::print_process(pv[pvcur]);
                pvcur++;
            }

            int active_cur = 0;
            while (pv[active_cur].cpu_time <= 0 || pv[active_cur].state != READY) active_cur++;

            process* cp = &pv[active_cur]; 
            if (cp -> remaining_cpu_burst == 0) {
                int burst = rnum.randomOS(cp -> interval);
                if (burst > cp -> cpu_time) burst = cp -> cpu_time;
                cp -> interval = burst;
                cp -> remaining_cpu_burst = burst;
                print_process(*cp);
            } 
            cp -> remaining_cpu_burst -= 1;
            cp -> cpu_time -= 1;
            
            if (cp -> remaining_cpu_burst == 0) cp -> state = BLOCKED;


            int blocked_cur = 0;
            while (pv[blocked_cur].io_time <= 0 || pv[blocked_cur].state != BLOCKED) blocked_cur++;
            process* bp = &pv[blocked_cur];

            
            if (bp -> remaining_io_burst == 0) {
                int burst = rnum.randomOS(bp -> interval);
                if (burst > bp -> io_time) burst = bp -> io_time;
                bp -> interval = burst;
                bp -> remaining_io_burst = burst;
            }
            bp -> remaining_io_burst -= 1;
            cp -> io_time -= 1;

            if (bp -> remaining_io_burst == 0) bp -> state = READY;


            if (cp -> cpu_time == 0 && cp -> io_time == 0) {
                cp -> state = TERMINATED;
                print_process(*cp);
            }
            std::cout << "ctr is " << ctr << std::endl;
            print_process(*cp);
            ctr++;
        } while (! s::is_procs_terminated(pv) && ctr < 10);

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