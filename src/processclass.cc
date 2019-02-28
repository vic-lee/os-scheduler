#include <string>
#include <vector>
#include "header.h"

namespace scheduler {

    void Process::decr_cpu_burst(RandNumAccessor rnum) {
        remaining_cpu_burst--;
        cpu_time--;
        if (remaining_cpu_burst == 0) {
            state = BLOCKED;
            int burst = rnum.randomOS(interval);
            interval = burst;
            remaining_io_burst = burst;
        }
    }

    void Process::decr_io_burst(RandNumAccessor rnum) {
        remaining_io_burst--;
        io_time--;
        if (remaining_io_burst == 0) {
            state = READY;
        }
    }

}