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


    void print_process_one_line(Process p) {
        std::cout 
            << "ID: " << p.pid << '\t' 
            << "Arrival time: " << p.arrival_time << '\t' 
            << "Interval: " << p.interval << '\t'
            << "CPU Time: " << p.cpu_time << "\t"
            << "I/O Time: " << p.io_time << "\t"
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