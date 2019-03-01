#include <iostream>
#include <string>
#include <vector>
#include "header.h"

namespace scheduler {

    void Process::ready_to_run(RandNumAccessor rnum) {
        state = RUNNING;
        int burst = rnum.randomOS(interval);
        interval = burst;
        remaining_cpu_burst = burst;
    }

    void Process::running_to_blocked(RandNumAccessor rnum) {
        state = BLOCKED;
        int burst = rnum.randomOS(interval);
        interval = burst;
        remaining_io_burst = burst;
    }

    void Process::blocked_to_ready() {
        state = READY;
    }

    void Process::decr_cpu_burst() {
        if (remaining_cpu_burst >= 1) remaining_cpu_burst--;
        if (cpu_time >= 1) cpu_time--;
        // remaining_cpu_burst--;
        // cpu_time--;
    }

    void Process::decr_io_burst() {
        // std::cout << "in decr io burst, remaining io burst is " << remaining_io_burst << std::endl;
        if (remaining_io_burst >= 1) {
            // std::cout << "trying to decrement" << std::endl;
            remaining_io_burst--;
            // std::cout << "after decrement value: " << remaining_io_burst << std::endl;
        }
        if (io_time >= 1) io_time--;
    }

    bool Process::is_finished() {
        return cpu_time == 0 && io_time == 0;
    }

}