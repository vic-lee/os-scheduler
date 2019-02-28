#ifndef HEADER_FILE
#define HEADER_FILE

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000
#define UNSTARTED "unstarted"
#define READY "ready"
#define RUNNING "running"
#define BLOCKED "blocked"
#define TERMINATED "terminated"

struct process {
    std::string state;
    int pid;
    int arrival_time;
    int interval;
    int cpu_time;
    int io_time;
    int remaining_burst;
};

namespace scheduler {

    /*      utils/printer.cc        */
    void print_process(process p);
    void print_process_vect(std::vector<process> const &v);
    void print_cycle_info(process* p, int size, int cycle_num);

    /*      utils/util.cc        */
    std::vector<process> read_file(std::string fname);
    // process* generate_process_arr(int size);
    process* parrcpy(process* parr, int size);
    bool is_procs_terminated(process* parr, int size);

}

#endif