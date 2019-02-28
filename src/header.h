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
    int arrival_time;
    int interval;
    int cpu_time;
    int io_time;
    std::string state;
    int remaining_burst;
};

namespace scheduler {

    /*      utils/printer.cc        */
    void print_process(process p);
    void print_process_arr(process* p, int size);
    void print_cycle_info(process* p, int size, int cycle_num);

    /*      utils/util.cc        */
    std::tuple<process*, int> read_file(std::string fname);
    int randomOS(int u, int ln);
    process* generate_process_arr(int size);

    /*      utils/sort.cc        */
    process* sort_parr_by_arrival(process* parr, int size);

}

#endif