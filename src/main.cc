#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <tuple>
#include <string>
#include <chrono> 

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000

using namespace std;

struct process {
    int arrival_time;
    int interval;
    int cpu_time;
    int io_time;
};


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


tuple<process*, int> read_file(string fname) {

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
                case 0: temp_process.arrival_time = stoi(val);
                case 1: temp_process.interval = stoi(val);
                case 2: temp_process.cpu_time = stoi(val);
                case 3: temp_process.io_time = stoi(val);
            }

            if (ctr == 3) {
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
        return stoi(line) + u;
    } else {
        cout << "Could not open random-numbers.txt. Terminating..." << endl;
        return -1;
    }
}


void fcfs_scheduler(process* parr, int size) {
    /**
     * Input:   pointer to process array, array size, flag(s)
     * Output:  print on screen. 
     * Algorithm: 
     *      1. Enqueue processes by their entry time, given a process array
     *      2. While the queue is not empty:
     *          Alternate between CPU and I/O bursts (blocked).
     *          Blocked processes, when ready, join the end of the queue. 
     */
}


void rr_scheduler() { }

void uniprogrammed_scheduler() { }

void sjf_scheduler() { }

int main(int argc, char** argv) {
    string fname = argv[1];
    process* parr;
    int pcount;
    tie(parr, pcount) = read_file(fname);
    if (parr) cout << "Process array ptr:\t" << parr << endl;
    cout << "Process array len:\t" << pcount << endl;
    print_process_arr(parr, pcount);
    int rand_num = randomOS(3);
    cout << rand_num << endl;
    return 0;
}