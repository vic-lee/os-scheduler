#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

#define RAND_NUM_FILE_SIZE 100000

int randomOS(int u) {
    ifstream file_rand_num("random-numbers.txt");
    if (file_rand_num) {
        int rand_line_num = rand() % RAND_NUM_FILE_SIZE + 1;
        int i = 0;
        string line; 
        while (i < rand_line_num) {
            getline(file_rand_num, line);
            i++;
        }
        file_rand_num.close();
        return stoi(line) + u;
    } else {
        cout << "Could not open random-numbers.txt. Terminating..." << endl;
        return -1;
    }
}


void print_process(process p) {
    cout << "Process arrival time: \t" << p.arrival_time << "\n"
        << "Process interval: \t" << p.interval << "\n"
        << "Process CPU time: \t" << p.cpu_time << "\n"
        << "Process I/O time: \t" << p.io_time << "\n" << endl;
}


void print_process_arr(process* p, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Process " << (i + 1) << endl;
        print_process(*(p + i));
    }
}


process* generate_process_arr(int size) {
    process* p = (process*) malloc(size * sizeof(process));
    if (p) {
        return p;
    } else {
        cout << "Could not assign memory to process array. Terminating..." << endl;
        return nullptr;
    }
}


// process* sort_parr_by_arrival(process* parr, int size) {
//     process* sorted_parr;
//     return sorted_parr;
// }
