#ifndef HEADER_FILE
#define HEADER_FILE

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000
#define QT_UNDEF -1
#define UNSTARTED "unstarted"
#define READY "ready"
#define RUNNING "running"
#define BLOCKED "blocked"
#define TERMINATED "terminated"

#include <string>

namespace scheduler {

    const std::string VERBOSE = "--verbose";
    const std::string SHOWRAND = "--show-random";
    const std::string DFTOUT = "--default";
    static std::string OUT_MODE; 

    class RandNumAccessor {
        public: 
            int cur_line = 1;
            std::tuple<int, int> randomOS(int u);
    };

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
            int remaining_quantum = 0;
            bool is_preempted = false;
            int remaining_io_burst;
            int terminated_time = 0;
            int turnaround_time; 
            int blocked_time = 0;   // time in the blocked state
            int waiting_time = 0;   // time in the ready state
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
    };


    /*      utils/calcproc.cc       */
    bool comp_proc(Process a, Process b);
    bool comp_proc_ptr(Process* a, Process* b);
    bool comp_proc_id(Process a, Process b);

    /*      utils/printer.cc        */
    void input_out(std::vector<Process> const pv, bool sorted);
    void print_process_one_line(Process p);
    void print_process_vect(std::vector<Process> const &v);
    void print_process_vect_out(std::vector<Process> const &v);
    void print_process_vect_simp(std::vector<Process> const &v, int cycle, int quantum = QT_UNDEF);
    void print_summary_data(std::vector<Process> const &v, int cycle, int cpu_used_time, int io_used_time);

    /*      utils/util.cc        */
    std::vector<Process> read_file(std::string fname);
    bool is_procs_terminated(std::vector<Process> const &vect);
    float calc_avg_wait_time(std::vector<Process> const &vect);
    float calc_avg_turnaround_time(std::vector<Process> const &vect);
    float calc_throughput(std::vector<Process> const &vect, int cycle);
    float calc_cpu_util(int cpu_used_time, int cycle);
    float calc_io_util(int io_used_time, int cycle);

}

#endif