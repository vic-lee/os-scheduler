#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../header.h"

using namespace std;

tuple<process*, int> read_file(string fname) {
    /**
     * This function reads an formatted input file and stores processes 
     * specified in the file in an array. The array is of type struct process. 
     * Struct process is defined in `header.h`.
     * Input:   A string of file name
     * Output:  A tuple, containing:
     *              a pointer to the process array
     *              an int of the array's size
     */
    ifstream input_file(fname);
    if (input_file.is_open()) {
        string val;
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
                case 1: temp_process.init_interval = stoi(val); break;
                case 2: temp_process.cpu_time = stoi(val); break;
                case 3: temp_process.io_time = stoi(val); break;
                default: cout << "Error in parsing process." << endl; break;
            }

            if (ctr == EOPROCESS) {
                parr[p_added] = temp_process;
                p_added++;
            }
            if (ctr < EOPROCESS) ctr++;
            else ctr = 0;
        }
        input_file.close();
        return make_tuple(parr, pcount);

    } else {
        cout << "File " << fname << " could not be opened." << endl;
        return make_tuple(nullptr, -1);
    }
}


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
        return 1 + (stoi(line) % u);
    } else {
        cout << "Could not open random-numbers.txt. Terminating..." << endl;
        return -1;
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
