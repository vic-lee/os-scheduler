#ifndef HEADER_FILE
#define HEADER_FILE

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000
#define UNSTARTED "unstarted"
#define READY "ready"
#define RUNNING "running"
#define BLOCKED "blocked"
#define TERMINATED "terminated"

namespace scheduler {

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
            int interval;
            int cpu_time;
            int io_time;
            int remaining_cpu_burst;
            int remaining_io_burst;
            int terminated_time;
            int blocked_time = 0;   // time in the blocked state
            int waiting_time = 0;   // time in the ready state
            void set_state();
            void ready_to_run(RandNumAccessor &rnum);
            void running_to_blocked(RandNumAccessor &rnum);
            void blocked_to_ready();
            void decr_cpu_burst();
            void decr_io_burst();
            bool is_finished();
            void terminate_process(int cycle);
    };


    /*      utils/printer.cc        */
    void print_process(Process p);
    void print_process_one_line(Process p);
    void print_process_vect(std::vector<Process> const &v);
    void print_process_vect_simp(std::vector<Process> const &v, int cycle);
    void print_cycle_info(Process* p, int size, int cycle_num);

    /*      utils/util.cc        */
    std::vector<Process> read_file(std::string fname);
    // process* generate_process_arr(int size);
    bool is_procs_terminated(std::vector<Process> const &vect);

}

#endif