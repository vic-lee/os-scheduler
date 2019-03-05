#include <iostream>
#include "../header.h"

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

}