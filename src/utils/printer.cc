#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../header.h"

namespace scheduler {

    void print_process(Process p) {
        std::cout 
            << "Process ID: \t\t" << p.pid << "\n"
            << "Process arrival time: \t" << p.arrival_time << "\n"
            << "Process init interval: \t" << p.interval << "\n"
            << "Process CPU time: \t" << p.cpu_time << "\n"
            << "Process I/O time: \t" << p.io_time << "\n" 
            << "Process state: \t" << p.state << "\n"
            << "Remaining CPU burst: \t" << p.remaining_cpu_burst << "\n"
            << "Remaining IO burst: \t" << p.remaining_io_burst << "\n"
            << std::endl;
    }


    void print_process_vect(std::vector<Process> const &v) {
        for (Process p : v) { print_process(p); }
    }


    void print_cycle_info(Process* p, int size, int cycle_num) {
        std::cout << "Before cycle\t" << cycle_num << ":\t";
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(11) << (p + i) -> state 
                << std::setw(3) << (p + i) -> remaining_cpu_burst;
        }
        std::cout << std::endl;
    }

}