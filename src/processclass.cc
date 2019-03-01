#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "header.h"

namespace scheduler {

    void Process::ready_to_run(RandNumAccessor &rnum) {
        state = RUNNING;
        int burst, randnum;
        std::tie(burst, randnum) = rnum.randomOS(cpu_interval);
        std::cout 
            << "Find burst when choosing ready process to run " << randnum
            << std::endl;
        // interval = burst;
        remaining_cpu_burst = burst;
    }

    void Process::running_to_blocked(RandNumAccessor &rnum) {
        state = BLOCKED;
        int burst, randnum;
        std::tie(burst, randnum) = rnum.randomOS(io_interval);
        std::cout 
            << "Find I/O burst when blocking a process " << randnum 
            << std::endl;
        // interval = burst;
        blocked_time += burst;
        remaining_io_burst = burst;
    }

    void Process::blocked_to_ready() {
        state = READY;
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

}