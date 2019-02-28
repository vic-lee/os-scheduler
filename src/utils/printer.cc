#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../header.h"

namespace scheduler {

    void print_process(process p) {
        std::cout 
            << "Process ID: \t\t" << p.pid << "\n"
            << "Process arrival time: \t" << p.arrival_time << "\n"
            << "Process init interval: \t" << p.interval << "\n"
            << "Process CPU time: \t" << p.cpu_time << "\n"
            << "Process I/O time: \t" << p.io_time << "\n" 
            << "Process state: \t" << p.state << "\n"
            // << "Process remaining burst: \t" << p.remaining_burst << "\n"
            << std::endl;
    }


    void print_process_arr(process* p, int size) {
        for (int i = 0; i < size; i++) {
            std::cout << "Process " << i << std::endl;
            print_process(*(p + i));
        }
    }

    void print_process_vect(std::vector<process> const &v) {
        for (process p : v) { print_process(p); }
    }


    void print_cycle_info(process* p, int size, int cycle_num) {
        std::cout << "Before cycle\t" << cycle_num << ":\t";
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(11) << (p + i) -> state 
                << std::setw(3) << (p + i) -> remaining_burst;
        }
        std::cout << std::endl;
    }

}