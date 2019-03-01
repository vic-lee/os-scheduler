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


    void set_queue_first_to_running(std::queue<Process*> &q, RandNumAccessor rnum) {
        if (q.size() == 0) {
            return;
        } else {
            if (q.front() -> state == READY) {
                q.front() -> ready_to_run(rnum);
            }
        }
    }


    void do_arrival_process(std::vector<Process> &pv, std::queue<Process*> &q, int cycle) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].arrival_time == cycle) {
                pv[i].state = READY;
                q.push(&pv[i]);
            }
        }
    }


    void do_running_process(std::queue<Process*> &q) {
        if (q.size() == 0) return;
        q.front() -> decr_cpu_burst();
    }


    void finished_running_process_to_blocked(std::queue<Process*> &q, std::vector<Process*> &v, RandNumAccessor rnum) {
        if (q.size() == 0) return;
        if (q.front() -> state == RUNNING && q.front() -> remaining_cpu_burst == 0) {
            if (!q.front() -> is_finished()) {
                q.front() -> running_to_blocked(rnum);
                v.push_back(q.front());
            }
            q.pop();
        }
    }


    void do_blocked_process(std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            v[i] -> decr_io_burst();
        }
    }


    void finished_blocked_process_to_ready(std::queue<Process*> &q, std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] -> remaining_io_burst == 0) {
                if (! v[i] -> is_finished()) {
                    v[i] -> blocked_to_ready();
                    q.push(v[i]);
                }
                v.erase(v.begin() + i);
            }
        }
    }


    void terminate_finished_processes(std::vector<Process> &pv) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].is_finished()) pv[i].state = TERMINATED;
        }
    }


    void fcfs(std::vector<Process> pv, RandNumAccessor rnum) {
        std::queue<Process*> running_queue;
        std::vector<Process*> blocked_vect;
        int cycle = 0;
        std::cout << "---------- FCFS ----------\n" << std::endl;
        while (!is_procs_terminated(pv) && cycle < 15) {

            print_process_vect_simp(pv, cycle);

            do_blocked_process(blocked_vect);
            do_running_process(running_queue);

            finished_blocked_process_to_ready(running_queue, blocked_vect);
            finished_running_process_to_blocked(running_queue, blocked_vect, rnum);            

            do_arrival_process(pv, running_queue, cycle);
            set_queue_first_to_running(running_queue, rnum);
            
            
            terminate_finished_processes(pv);

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