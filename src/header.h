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
            void set_state();
    };

    class RandNumAccessor {
        public: 
            int cur_line = 1;
            int randomOS(int u);
    };

    /*      utils/printer.cc        */
    void print_process(Process p);
    void print_process_vect(std::vector<Process> const &v);
    void print_cycle_info(Process* p, int size, int cycle_num);

    /*      utils/util.cc        */
    std::vector<Process> read_file(std::string fname);
    // process* generate_process_arr(int size);
    bool is_procs_terminated(std::vector<Process> const &vect);

}

#endif