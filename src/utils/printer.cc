#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../header.h"

namespace scheduler {


    void print_process_one_line(Process p) {
        std::cout 
            << "ID: " << p.pid << '\t' 
            << "Arrival time: " << p.arrival_time << '\t' 
            << "CPU Interval: " << p.cpu_interval << '\t'
            << "CPU Time: " << p.cpu_time << "\t"
            << "I/O Interval: " << p.io_interval << "\t"
            << "State: " << p.state << "  \t"
            << "R IO Burst: " << p.remaining_io_burst << "\t"
            << "R CPU Burst: " << p.remaining_cpu_burst << "\t"
            << "Finishing time: " << p.terminated_time << "\t"
            << "I/O time (blocked): " << p.blocked_time << "\t"
            << "Waiting time: " << p.waiting_time << "\t"
            << std::endl;
    }


    void print_process_vect(std::vector<Process> const &v) {
        for (Process p : v) { print_process_one_line(p); }
    }

    void print_process_vect_simp(std::vector<Process> const &v, int cycle) {
        std::cout << "Before cycle " << std::setw(4) << cycle << ":";
        for (Process p : v) {
            std::cout << std::setw(12) << p.state;
            if (p.state == BLOCKED) {
                std::cout << std::setw(3) << p.remaining_io_burst << std::flush;
            }
            else {
                std::cout << std::setw(3) << p.remaining_cpu_burst << std::flush;
            }
        }
        std::cout << "." << std::endl;
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