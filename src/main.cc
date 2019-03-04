#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>
#include "header.h"

namespace s = scheduler;

namespace scheduler {

    bool comp_proc(Process a, Process b) {
        if (a.arrival_time < b.arrival_time) return true; 
        if (a.arrival_time == b.arrival_time) return a.pid < b.pid;
        return false;
    }


    bool comp_proc_ptr(Process* a, Process* b) {
        if (a -> arrival_time < b -> arrival_time) return true;
        if (a -> arrival_time == b -> arrival_time) return a -> pid < b -> pid;
        return false;
    }


    bool comp_proc_id(Process a, Process b) { return a.pid < b.pid; }


    bool sjf_sort(Process* a, Process* b) {
        if (a -> cpu_time < b -> cpu_time) return true;
        else if (a -> cpu_time == b -> cpu_time) return a -> pid < b -> pid;
        return false;
    }


    void set_queue_front_to_running(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int quantum = QT_UNDEF
    ) {
        if (q.size() == 0) {
            return;
        } else {
            if (q.front() -> state == TERMINATED) q.pop();
            if (q.size() > 0 && q.front() -> state == READY) 
                q.front() -> ready_to_run(rnum, quantum);
        }
    }


    void do_arrival_process(
        std::vector<Process> &pv, 
        std::queue<Process*> &q, 
        int cycle
    ) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].arrival_time == cycle) {
                pv[i].state = READY;
                q.push(&pv[i]);
            }
        }
    }


    void do_running_process(std::queue<Process*> &q, int quantum = QT_UNDEF) {
        if (q.size() == 0) return;
        q.front() -> decr_cpu_burst();
        if (quantum != QT_UNDEF) q.front() -> update_quantum_vars(quantum);
    }


    void running_process_to_blocked(
        std::queue<Process*> &q, 
        std::vector<Process*> &v, 
        RandNumAccessor &rnum,
        std::vector<Process*> &queuepool, 
        int quantum = QT_UNDEF
    ) {
        if (q.size() == 0) return;
        if (q.front() -> state == RUNNING && 
            (q.front() -> remaining_cpu_burst == 0 || 
            (quantum != QT_UNDEF && q.front() -> should_preempt(quantum)))
        ) {
            if (!q.front() -> is_finished()) {
                if (q.front() -> remaining_cpu_burst == 0) {
                    q.front() -> running_to_blocked(rnum);
                    v.push_back(q.front());
                } else {
                    if (quantum != QT_UNDEF) {
                        q.front() -> run_to_ready();
                        queuepool.push_back(q.front());
                    }
                }
            } 
            q.pop();
            std::sort(v.begin(), v.end(), comp_proc_ptr);
        }
    }


    void do_blocked_process(std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            v[i] -> decr_io_burst();
        }
    }


    void blocked_process_to_ready(
        std::queue<Process*> &q, 
        std::vector<Process*> &v,
        std::vector<Process*> &queuepool
    ) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] -> remaining_io_burst == 0) {
                if (! v[i] -> is_finished()) {
                    v[i] -> blocked_to_ready();
                    queuepool.push_back(v[i]);
                }
                v.erase(v.begin() + i);
                i--;
            }
        }
    }


    void terminate_finished_processes(std::vector<Process> &pv, int cycle) {
        std::cout << "Cycle: " << cycle << std::endl; 
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].state != TERMINATED && pv[i].is_finished()) {
                pv[i].terminate_process(cycle); 
                pv[i].calc_turnaround_time();
            }
        }
    }


    void update_queue_waiting_time(std::vector<Process> &pv) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].state == READY) pv[i].waiting_time++;
        }
    }


    void add_pool_to_queue(std::queue<Process*> &q, std::vector<Process*> &pool) {
        std::sort(pool.begin(), pool.end(), comp_proc_ptr);
        for (int i = 0; i < pool.size(); i++) {
            q.push(pool[i]);
            pool.erase(pool.begin() + i); i--;
        }
    }


    void first_come_first_serve(
        std::vector<Process> pv, 
        std::string outmode,
        int quantum = QT_UNDEF
    ) {
        RandNumAccessor rnum;
        std::queue<Process*> running_queue;
        std::vector<Process*> blocked_pool;
        std::vector<Process*> queue_wait_pool;
        int cycle = 0;
        int io_used_time = 0;
        int cpu_used_time = 0;

        while (!is_procs_terminated(pv)) {

            print_process_vect_simp(pv, cycle, quantum);
            
            do_blocked_process(blocked_pool);
            do_running_process(running_queue, quantum);

            blocked_process_to_ready(   
                running_queue, blocked_pool, queue_wait_pool);
            running_process_to_blocked(
                running_queue, blocked_pool, rnum, queue_wait_pool, quantum);
            add_pool_to_queue(
                running_queue, queue_wait_pool);

            do_arrival_process(pv, running_queue, cycle);

            terminate_finished_processes(pv, cycle); 

            set_queue_front_to_running(running_queue, rnum, quantum);

            update_queue_waiting_time(pv);
            
            if (running_queue.size() > 0) cpu_used_time++;
            if (blocked_pool.size() > 0) io_used_time++;

            cycle++;
        }
        cycle--;

        std::string algo_name = quantum != QT_UNDEF ? 
            "Round Robin" : "First Come First Served";
        std::cout 
            << "The scheduling algorithm used was " << algo_name
            << std::endl;

        print_process_vect_out(pv);
        print_summary_data(pv, cycle, cpu_used_time, io_used_time);
    }


    void roundrobin(std::vector<Process> pv, std::string outmode) {
        int quantum = 2;
        first_come_first_serve(pv, outmode, quantum);
    }


    void uni_do_queue_front_proc(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int &cpu_used_time,
        int &io_used_time
    ) {
        if (q.size() == 0) return;
        if (q.front() -> state == READY) {
            q.front() -> ready_to_run(rnum);
        } else {
            if (q.front() -> state == BLOCKED) {
                q.front() -> decr_io_burst(); io_used_time++;
            } else if (q.front() -> state == RUNNING) {
                q.front() -> decr_cpu_burst(); cpu_used_time++;
            }
        }
    }


    void uni_pop_finished_queue_front(std::queue<Process*> &q, const int cycle) {
        if (q.size() == 0) return;
        if (q.front() -> is_finished()) {
            q.front() -> terminate_process(cycle);
            q.front() -> calc_turnaround_time();
            q.pop(); 
        }
    }


    void uni_alternate_run_blocked(std::queue<Process*> &q, RandNumAccessor &rnum) {
        if (q.size() == 0) return;
        bool is_run_finished = q.front() -> state == RUNNING && q.front() -> remaining_cpu_burst == 0;
        bool is_block_finished = q.front() -> state == BLOCKED && q.front() -> remaining_io_burst == 0;
        if (!q.front() -> is_finished()) {
            if (is_run_finished) {
                q.front() -> running_to_blocked(rnum);
            } else if (q.front() -> state == READY || is_block_finished) {
                q.front() -> blocked_to_ready();
                q.front() -> ready_to_run(rnum); 
            }
        }
    }


    void uniprogrammed(std::vector<Process> pv, std::string outmode) {
        RandNumAccessor rnum;
        std::queue<Process*> uniq;
        int cycle = 0;
        int io_used_time = 0;
        int cpu_used_time = 0;
        while (!is_procs_terminated(pv)) {
            print_process_vect_simp(pv, cycle);
            do_arrival_process(pv, uniq, cycle);
            uni_do_queue_front_proc(uniq, rnum, cpu_used_time, io_used_time);
            uni_pop_finished_queue_front(uniq, cycle);
            uni_alternate_run_blocked(uniq, rnum);
            update_queue_waiting_time(pv);
            cycle++;
        }
        std::cout << "The scheduling algorithm used was Uniprocessor" << std::endl;
        cycle--;
        print_process_vect_out(pv);
        print_summary_data(pv, cycle, cpu_used_time, io_used_time);
    }


    void sjf_do_arrival_process(
        std::vector<Process> &pv, 
        std::vector<Process*> &readypool, 
        int cycle 
    ) {
        for (int i = 0; i < pv.size(); i++) {
            if ( pv[i].arrival_time == cycle ) {
                pv[i].state = READY;
                readypool.push_back(&pv[i]);
            }
        }
        std::sort(readypool.begin(), readypool.end(), sjf_sort);
    }


    void sjf_ready_to_run(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &readypool, 
        RandNumAccessor &rnum
    ) {
        if (runproc.size() == 0 && readypool.size() > 0) {  
            runproc.push_back(readypool[0]);
            runproc[0] -> ready_to_run(rnum);
            readypool.erase(readypool.begin());
        }
    }


    void sjf_do_running_process(std::vector<Process*> &runproc) {
        if (runproc.size() > 0) {
            runproc[0] -> decr_cpu_burst();
            if (runproc[0] -> is_finished()) runproc.erase(runproc.begin());
        }
    }


    void sjf_running_to_blocked(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &blocked_pool, 
        RandNumAccessor &rnum
    ) {
        if (runproc.size() == 0) return;
        if (!runproc[0] -> is_finished() && runproc[0] -> is_cpu_burst_finished()) {
            runproc[0] -> running_to_blocked(rnum);
            blocked_pool.push_back(runproc[0]);
            runproc.erase(runproc.begin());
        }
    }


    void sjf_blocked_to_ready(
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    ) {
        for (int i = 0; i < blockedpool.size(); i++) {
            if (blockedpool[i] -> is_io_burst_finished()) {
                blockedpool[i] -> blocked_to_ready();
                readypool.push_back(blockedpool[i]);
                blockedpool.erase(blockedpool.begin() + i); 
                i--;
            }
        }
        std::sort(readypool.begin(), readypool.end(), sjf_sort);
    }


    void print_proc_ptr(std::vector<Process*> p, std::string name) {
        if (p.size() > 0)
            std::cout << "Printing " << name << std::endl;
        for (int i = 0; i < p.size(); i++) {
            std::cout << "PID: " << p[i] -> pid
            << "\tCPU TIME: " << p[i] -> cpu_time
            << "\tSTATE: " << p[i] -> state
            << "\tR C BURST: " << p[i] -> remaining_cpu_burst
            << "\tR IO BURST: " << p[i] -> remaining_io_burst
            << std::endl;
        }
    }

    void sjf_rm_terminated_from_vect(std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] -> state == TERMINATED) {
                v.erase(v.begin() + i);
                i--;
            }
        }
    }


    void sjf_clear_terminated_processes(
        std::vector<Process*> &runningproc, 
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    ) {
        sjf_rm_terminated_from_vect(runningproc);
        sjf_rm_terminated_from_vect(blockedpool);
        sjf_rm_terminated_from_vect(readypool);
    }


    void sjf_update_ready_time(std::vector<Process*> &readypool) {
        for (int i = 0; i < readypool.size(); i++) {
            readypool[i] -> waiting_time++;
        }
    }


    void shortest_job_first(std::vector<Process> pv, std::string outmode) {
        RandNumAccessor rnum;
        std::vector<Process*> running_proc;
        std::vector<Process*> ready_pool;
        std::vector<Process*> blocked_pool;
        int cycle = 0; 
        int io_used_time = 0;
        int cpu_used_time = 0;
        while (!is_procs_terminated(pv) && cycle < 2000) {
            print_process_vect_simp(pv, cycle);

            do_blocked_process(blocked_pool);
            sjf_do_running_process(running_proc);

            sjf_running_to_blocked(running_proc, blocked_pool, rnum);
            sjf_blocked_to_ready(blocked_pool, ready_pool);

            sjf_do_arrival_process(pv, ready_pool, cycle);
            sjf_ready_to_run(running_proc, ready_pool, rnum);

            sjf_update_ready_time(ready_pool);
            terminate_finished_processes(pv, cycle); 
            if (running_proc.size() > 0) cpu_used_time++;
            if (blocked_pool.size() > 0) io_used_time++;
            cycle++;
        }
        cycle--;
        std::cout << "The scheduling algorithm used was Shortest Job First" << std::endl;
        print_process_vect_out(pv);
        print_summary_data(pv, cycle, cpu_used_time, io_used_time);
    }


}


int main(int argc, char** argv) {

    std::string algo = "";
    std::string outmode = s::DFTOUT;
    std::string fname;

    if (argc > 3) algo = argv[3];
    if (argc > 2) {
        outmode = argv[1];
        fname = argv[2];
    } else {
        fname = argv[1];
    }

    // NOTE: REMOVE FOR FINAL PRODUCTION
    // if (argc > 2) algo = argv[2]; 
    
    std::vector<s::Process> pvect = s::read_file(fname);

    s::print_process_vect(pvect);
    std::sort(pvect.begin(), pvect.end(), s::comp_proc);
    std::cout << "After sorting" << std::endl;
    s::print_process_vect(pvect);


    if (algo == "--fcfs") {
        s::first_come_first_serve(pvect, outmode);
    } else if (algo == "--rr") {
        s::roundrobin(pvect, outmode);
    } else if (algo == "--uni") {
        s::uniprogrammed(pvect, outmode);
    } else if (algo == "--sjf") {
        s::shortest_job_first(pvect, outmode);
    } else {
        s::first_come_first_serve(pvect, outmode);
        s::roundrobin(pvect, outmode);
        s::uniprogrammed(pvect, outmode);
        s::shortest_job_first(pvect, outmode);
    }

    return 0;
}