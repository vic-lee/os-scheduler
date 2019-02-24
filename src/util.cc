#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

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
        process* parr = generate_process_arr(pcount);
        int ctr = 0;
        int p_added = 0;

        while (input_file >> val) {
            if (isalpha(val[0]) || input_file.eof()) break;

            switch (ctr) {
                case 0: 
                    temp_process.arrival_time = stoi(val);
                case 1: 
                    temp_process.init_interval = stoi(val);
                case 2: 
                    temp_process.cpu_time = stoi(val);
                case 3: 
                    temp_process.io_time = stoi(val);
                    temp_process.state = UNSTARTED;
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


void print_process(process p) {
    cout << "Process arrival time: \t" << p.arrival_time << "\n"
        << "Process init interval: \t" << p.init_interval << "\n"
        << "Process CPU time: \t" << p.cpu_time << "\n"
        << "Process I/O time: \t" << p.io_time << "\n" 
        << "Process state: \t" << p.state << endl;
}


void print_process_arr(process* p, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Process " << i << endl;
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


process* merge(process* l, int left_size, process* r, int right_size) {
    /* An implementation of merge sort */
    process* sorted_parr = (process*) 
        malloc((left_size + right_size) * sizeof(process));
    int left_index = 0;
    int right_index = 0;
    int parr_index = 0;

    while (left_index < left_size and right_index < right_size) {
        int l_arrival_time = (l + left_index) -> arrival_time;
        int r_arrival_time = (r + right_index) -> arrival_time;
        if (l_arrival_time <= r_arrival_time) {
            sorted_parr[parr_index] = *(l + left_index);
            left_index ++;
        } else {
            sorted_parr[parr_index] = *(r + right_index);
            right_index ++;
        }
        parr_index ++;
    }

    while (left_index < left_size) {
        sorted_parr[parr_index] = *(l + left_index);
        left_index++; parr_index++;
    }

    while (right_index < right_size) {
        sorted_parr[parr_index] = *(r + right_index);
        right_index++; parr_index++;
    }
    
    return sorted_parr;
}


process* sort_parr_by_arrival(process* parr, int size) {
    /**
     * Implements sort by arrival time with merge sort, 
     * in conjunction with process* merge().
     * Note that if two processes have the same arrival time, 
     * the one listed earliest in the input has highest priority. 
     * 
     * Input:   pointer to process array, size of process array
     * Output:  pointer to process array, sorted by arrival time. 
     */
    if (size <= 1) return parr;
    int left_size = size / 2;
    int right_size = size - left_size;
    process* left = sort_parr_by_arrival(parr, left_size);
    process* right = sort_parr_by_arrival((parr + left_size), right_size);
    return merge(left, left_size, right, right_size);
}
