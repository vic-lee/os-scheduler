#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "header.h"

namespace scheduler {

    void Process::ready_to_run(RandNumAccessor &rnum, int quantum = QT_UNDEF) {
        state = RUNNING;
        if (remaining_cpu_burst == 0) {
            int burst, randnum;
            std::tie(burst, randnum) = rnum.randomOS(cpu_interval);
            std::cout 
                << "Find burst when choosing ready process to run " << randnum
                << std::endl;
            remaining_cpu_burst = burst;
            assigned_cpu_burst = burst;

            if (quantum != QT_UNDEF) {
                if (burst > quantum) remaining_quantum = quantum; 
                else remaining_quantum = burst;
            } 
        } else {
            if (quantum != QT_UNDEF) {
                if (remaining_cpu_burst > quantum) remaining_quantum = quantum;
                else remaining_quantum = remaining_cpu_burst;
            }
        }
        
    }

    void Process::running_to_blocked(RandNumAccessor &rnum) {
        state = BLOCKED;
        int burst, randnum;
        std::tie(burst, randnum) = rnum.randomOS(io_interval);
        std::cout 
            << "Find I/O burst when blocking a process " << randnum 
            << std::endl;
        blocked_time += burst;
        remaining_io_burst = burst;
        assigned_cpu_burst = 0;
    }

    void Process::blocked_to_ready() {
        state = READY;
    }

    void Process::run_to_ready() {
        is_preempted = true;
        state = READY;
        if (remaining_cpu_burst == 0) {
            assigned_cpu_burst = 0;
            is_preempted = false;
        }
    }

    void Process::decr_cpu_burst() {
        if (remaining_cpu_burst >= 1) remaining_cpu_burst--;
        if (cpu_time >= 1) cpu_time--;
    }

    void Process::decr_io_burst() {
        if (remaining_io_burst >= 1) remaining_io_burst--;
    }

    bool Process::is_finished() {
        return cpu_time == 0;
    }

    void Process::terminate_process(int cycle) {
        state = TERMINATED;
        remaining_cpu_burst = 0;
        remaining_io_burst = 0;
        terminated_time = cycle;
    }

    void Process::calc_turnaround_time() {
        turnaround_time = terminated_time - arrival_time;
    }

    void Process::incr_cpu_time_used() { 
        cpu_time_used = assigned_cpu_burst - remaining_cpu_burst; 
    }

    void Process::decr_remaining_quantum(int quantum) {
        if (remaining_quantum >= 1) remaining_quantum--;
    }

    void Process::update_quantum_vars(int quantum) {
        incr_cpu_time_used();
        decr_remaining_quantum(quantum);
    }

    int Process::should_preempt(int quantum) {
        return remaining_quantum == 0;
    }

}