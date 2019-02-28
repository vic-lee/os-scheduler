#include <string>
#include <vector>
#include "header.h"

namespace scheduler {

    void Process::decr_cpu_burst() {
        remaining_cpu_burst--;
        cpu_time--;
        if (remaining_cpu_burst == 0) state = BLOCKED;
    }

    void Process::decr_io_burst() {
        remaining_io_burst--;
        io_time--;
        if (remaining_io_burst == 0) state = READY;
    }

}