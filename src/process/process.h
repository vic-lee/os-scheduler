#ifndef PROCESS_CLASS_HEADER
#define PROCESS_CLASS_HEADER

#include <string>
#include "../header.h"
#include "../utils/randnum/randnum.h"

namespace scheduler {
    class Process {
        public: 
            std::string state;
            int pid;
            int arrival_time;
            int cpu_interval;
            int cpu_time;
            int io_interval;
            int remaining_cpu_burst;
            int assigned_cpu_burst;
            int cpu_time_used;
            int remaining_quantum;
            bool is_preempted;
            int remaining_io_burst;
            int terminated_time;
            int turnaround_time; 
            int blocked_time;       // time in the blocked state
            int waiting_time;       // time in the ready state
            int cpu_time_assigned;
            void set_state();
            void ready_to_run(RandNumAccessor &rnum, int quantum = QT_UNDEF);
            void running_to_blocked(RandNumAccessor &rnum);
            void blocked_to_ready();
            void run_to_ready();
            void decr_cpu_burst();
            void decr_io_burst();
            bool is_finished();
            bool is_cpu_burst_finished();
            bool is_io_burst_finished();
            void terminate_process(int cycle);
            void calc_turnaround_time();
            void incr_cpu_time_used();
            void decr_remaining_quantum(int quantum);
            void update_quantum_vars(int quantum);
            int should_preempt(int quantum);

            Process() {
                remaining_quantum = 0;
                is_preempted = false;
                terminated_time = 0;
                blocked_time = 0;
                waiting_time = 0; 
            }
    };
}

#endif