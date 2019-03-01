#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../header.h"

namespace scheduler {

    std::vector<Process> read_file(std::string fname) {
        /**
         * This function reads an formatted input file and stores processes 
         * specified in the file in an array. The array is of type struct process. 
         * Struct process is defined in `header.h`.
         * Input:   A string of file name
         * Output:  A tuple, containing:
         *              a pointer to the process array
         *              an int of the array's size
         */
        std::vector<Process> procvect; 
        std::ifstream input_file(fname);
        if (input_file.is_open()) {
            std::string val;
            input_file >> val;
            // int pcount = stoi(val);
            int pctr = 0;
            Process temp_process;
            temp_process.state = UNSTARTED;
            temp_process.remaining_io_burst = 0;
            temp_process.remaining_cpu_burst = 0;
            int ctr = 0;
            while (input_file >> val) {
                if (isalpha(val[0]) || input_file.eof()) break;
                switch (ctr) {
                    case 0: temp_process.arrival_time = stoi(val); break;
                    case 1: temp_process.cpu_interval = stoi(val); break;
                    case 2: temp_process.cpu_time = stoi(val); break;
                    case 3: temp_process.io_interval = stoi(val); break;
                    default: std::cout << "Error in parsing process." << std::endl; break;
                }
                if (ctr == EOPROCESS) {
                    temp_process.pid = pctr;
                    pctr++;
                    procvect.push_back(temp_process);
                }
                if (ctr < EOPROCESS) ctr++;
                else ctr = 0;
            }
            input_file.close();
        }
        return procvect;
    }

    bool is_procs_terminated(std::vector<Process> const &vect) {
        for (int i = 0; i < vect.size(); i++) {
            if (vect[i].state != TERMINATED) return false;
        }
        return true;
    }

    float avg_waiting_time(std::vector<Process> const &vect) {
        int total_wait = 0;
        for (int i = 0; i < vect.size(); i++) {
            total_wait += vect[i].waiting_time;
        }
        float avg = (float) total_wait / (float) vect.size();
        return avg;
    }

    float avg_turnaround_time(std::vector<Process> const &vect) {
        int total_turn = 0;
        for (int i = 0; i < vect.size(); i++) {
            total_turn += vect[i].turnaround_time;
        }
        float avg = (float) total_turn / (float) vect.size();
        return avg;
    }

}