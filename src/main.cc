#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <iomanip>
#include <vector>
#include "header.h"
#include "process/process.h"
#include "utils/schedutil.h"
#include "utils/randnum/randnum.h"
#include "scheduler/scheduler.h"

namespace s = scheduler;

namespace scheduler {

    std::string OUT_MODE;

    void fcfs(std::vector<Process> pv, int quantum = QT_UNDEF) {
        RandNumAccessor rnum;
        std::queue<Process*> running_queue;
        std::vector<Process*> blocked_pool;
        std::vector<Process*> queue_wait_pool;
        int cycle = 0;
        int io_used_time = 0;
        int cpu_used_time = 0;

        std::cout << std::endl;

        if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)
            std::cout << PRINT_START_MSG << std::endl;

        while (!is_procs_terminated(pv)) {
            if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)            
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


    void first_come_first_served(std::vector<Process> pv) {
        fcfs(pv);
    }


    void roundrobin(std::vector<Process> pv) {
        int quantum = 2;
        fcfs(pv, quantum);
    }


    void uniprogrammed(std::vector<Process> pv) {
        RandNumAccessor rnum;
        std::queue<Process*> uniq;
        int cycle = 0;
        int io_used_time = 0;
        int cpu_used_time = 0;

        std::cout << std::endl;

        if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)
            std::cout << PRINT_START_MSG << std::endl;

        while (!is_procs_terminated(pv)) {
            if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)
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


    void shortest_job_first(std::vector<Process> pv) {
        RandNumAccessor rnum;
        std::vector<Process*> running_proc;
        std::vector<Process*> ready_pool;
        std::vector<Process*> blocked_pool;
        int cycle = 0; 
        int io_used_time = 0;
        int cpu_used_time = 0;

        std::cout << std::endl;

        if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)
            std::cout << PRINT_START_MSG << std::endl;

        while (!is_procs_terminated(pv) && cycle < 3000) {

            if (OUT_MODE == SHOWRAND || OUT_MODE == VERBOSE)
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
    std::string fname;
    s::OUT_MODE = s::DFTOUT;

    if (argc > 3) algo = argv[3];
    if (argc > 2) {
        std::string readin = argv[1];
        if (readin == s::VERBOSE || readin == s::SHOWRAND) {
            s::OUT_MODE = readin;
            fname = argv[2];
            // std::cout << s::OUT_MODE << std::endl;
            // std::cout << s::SHOWRAND << std::endl;
            // std::cout << (s::OUT_MODE == s::SHOWRAND) << std::endl;            
            // std::cout << (s::OUT_MODE.compare(s::SHOWRAND) == 0) << std::endl;            
        } else {
            fname = argv[1];
            algo = argv[2]; 
        }
    } else {
        fname = argv[1];
    } 
    
    std::vector<s::Process> pvect = s::read_file(fname);
    std::vector<s::Process> originalpvect = pvect;

    std::sort(pvect.begin(), pvect.end(), s::comp_proc);

    if (algo == "--fcfs") {
        s::unsorted_sorted_print(originalpvect, pvect);
        s::first_come_first_served(pvect);
    } else if (algo == "--rr") {
        s::unsorted_sorted_print(originalpvect, pvect);
        s::roundrobin(pvect);
    } else if (algo == "--uni") {
        s::unsorted_sorted_print(originalpvect, pvect);
        s::uniprogrammed(pvect);
    } else if (algo == "--sjf") {
        s::unsorted_sorted_print(originalpvect, pvect);
        s::shortest_job_first(pvect);
    } else {
        s::unsorted_sorted_print(originalpvect, pvect);
        s::first_come_first_served(pvect);

        s::unsorted_sorted_print(originalpvect, pvect);
        s::roundrobin(pvect);

        s::unsorted_sorted_print(originalpvect, pvect);
        s::uniprogrammed(pvect);

        s::unsorted_sorted_print(originalpvect, pvect);
        s::shortest_job_first(pvect);
    }

    return 0;
}