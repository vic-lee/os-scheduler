#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../header.h"

namespace scheduler {


    std::tuple<process*, int> read_file(std::string fname) {
        /**
         * This function reads an formatted input file and stores processes 
         * specified in the file in an array. The array is of type struct process. 
         * Struct process is defined in `header.h`.
         * Input:   A string of file name
         * Output:  A tuple, containing:
         *              a pointer to the process array
         *              an int of the array's size
         */
        std::ifstream input_file(fname);
        if (input_file.is_open()) {
            std::string val;
            input_file >> val;
            int pcount = stoi(val);
            process temp_process;
            temp_process.state = UNSTARTED;
            temp_process.remaining_burst = 0;
            process* parr = generate_process_arr(pcount);
            int ctr = 0;
            int p_added = 0;
            while (input_file >> val) {
                if (isalpha(val[0]) || input_file.eof()) break;
                switch (ctr) {
                    case 0: temp_process.arrival_time = stoi(val); break;
                    case 1: temp_process.interval = stoi(val); break;
                    case 2: temp_process.cpu_time = stoi(val); break;
                    case 3: temp_process.io_time = stoi(val); break;
                    default: std::cout << "Error in parsing process." << std::endl; break;
                }
                if (ctr == EOPROCESS) {
                    parr[p_added] = temp_process;
                    p_added++;
                }
                if (ctr < EOPROCESS) ctr++;
                else ctr = 0;
            }
            input_file.close();
            return std::make_tuple(parr, pcount);

        } else {
            std::cout << "File " << fname << " could not be opened." << std::endl;
            return std::make_tuple(nullptr, -1);
        }
    }


    int randomOS(int u) {
        std::ifstream file_rand_num("random-numbers.txt");
        if (file_rand_num) {
            int rand_line_num = rand() % RAND_NUM_FILE_SIZE + 1;
            int i = 0;
            std::string line; 
            while (i < rand_line_num) {
                getline(file_rand_num, line);
                i++;
            }
            file_rand_num.close();
            return 1 + (stoi(line) % u);
        } else {
            std::cout << "Could not open random-numbers.txt. Terminating..." << std::endl;
            return -1;
        }
    }


    process* generate_process_arr(int size) {
        process* p = (process*) malloc(size * sizeof(process));
        if (p) {
            return p;
        } else {
            std::cout << "Could not assign memory to process array. Terminating..." << std::endl;
            return nullptr;
        }
    }

}