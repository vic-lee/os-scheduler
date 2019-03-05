#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include <vector>
#include <iostream>

namespace schdeuler {

    void input_out(std::vector<Process> const pv, bool sorted);
    void print_process_one_line(Process p);
    void print_process_vect(std::vector<Process> const &v);
    void print_process_vect_out(std::vector<Process> const &v);
    void print_process_vect_simp(std::vector<Process> const &v, int cycle, int quantum = QT_UNDEF);
    void print_summary_data(std::vector<Process> const &v, int cycle, int cpu_used_time, int io_used_time);

}

#endif