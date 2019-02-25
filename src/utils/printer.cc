#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../header.h"

using namespace std;

void print_process(process p) {
    cout << "Process arrival time: \t" << p.arrival_time << "\n"
        << "Process init interval: \t" << p.init_interval << "\n"
        << "Process CPU time: \t" << p.cpu_time << "\n"
        << "Process I/O time: \t" << p.io_time << "\n" 
        << "Process state: \t" << p.state << "\n"
        // << "Process remaining burst: \t" << p.remaining_burst << "\n"
        << endl;
}


void print_process_arr(process* p, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Process " << i << endl;
        print_process(*(p + i));
    }
}


void print_cycle_info(process* p, int size, int cycle_num) {
    cout << "Before cycle\t" << cycle_num << ":\t";
    for (int i = 0; i < size; i++) {
        cout << setw(11) << (p + i) -> state 
            << setw(3) << (p + i) -> remaining_burst;
    }
    cout << endl;
}