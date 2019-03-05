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
#include "utils/printer.h"

namespace scheduler {

    const std::string VERBOSE = "--verbose";
    const std::string SHOWRAND = "--show-random";
    const std::string DFTOUT = "--default";
    static std::string OUT_MODE; 

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