#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../header.h"

namespace scheduler {

    void input_out(std::vector<Process> const pv, bool sorted) {
        if (!sorted) std::cout << "The original input was: ";
        else std::cout << "The (sorted) input is:  ";
        std::cout << pv.size() << " " << std::flush;
        for (int i = 0; i < pv.size(); i++) {
            std::printf(" %d %d %d %d ", 
                pv[i].arrival_time, pv[i].cpu_interval, 
                pv[i].cpu_time_assigned, pv[i].io_interval);
        }
        std::cout << std::endl;
    }

    void print_process_out(Process p, int index) {
        std::cout << "\nProcess " << index  << ":" << std::endl;
        std::printf("\t(A,B,C,IO) = (%d,%d,%d,%d)\n", 
            p.arrival_time, p.cpu_interval, p.cpu_time_assigned, p.io_interval);
        std::cout 
            << "\tFinishing time: " << p.terminated_time << "\n"
            << "\tTurnaround time: " << p.turnaround_time << "\n"
            << "\tI/O time: " << p.blocked_time << "\n"
            << "\tWaiting time: " << p.waiting_time
            << std::endl;
    }


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


    void print_process_vect_out(std::vector<Process> const &v) {
        for (int i = 0; i < v.size(); i++) {
            print_process_out(v[i], i);
        }
    }


    void print_process_vect_simp(std::vector<Process> const &v, int cycle, int quantum) {
        std::cout << "Before cycle " << std::setw(4) << cycle << ":";
        for (Process p : v) {
            std::cout << std::setw(12) << p.state;
            if (p.state == BLOCKED) {
                std::cout << std::setw(3) << p.remaining_io_burst << std::flush;
            }
            else {
                if (quantum != QT_UNDEF) {
                    std::cout << std::setw(3) << p.remaining_quantum << std::flush;
                } else {
                    std::cout << std::setw(3) << p.remaining_cpu_burst << std::flush;
                }
            }
        }
        std::cout << "." << std::endl;
    }


    void print_summary_data(
        std::vector<Process> const &v, 
        int cycle, 
        int cpu_used_time, 
        int io_used_time
    ) {
        std::cout << "\nSummary Data:" << "\n"
            << "\tFinishing time: " << cycle << "\n"
            << "\tCPU Utilization: " << calc_cpu_util(cpu_used_time, cycle) << "\n"
            << "\tI/O Utilization: " << calc_io_util(io_used_time, cycle) << "\n"
            << "\tThroughput: " 
                << calc_throughput(v, cycle) 
                << " processes per hundred cycles" << "\n"
            << "\tAverage turnaround time: " << calc_avg_turnaround_time(v) << "\n"
            << "\tAverage waiting time: " << calc_avg_wait_time(v) << "\n"
            << std::endl;
    }

}