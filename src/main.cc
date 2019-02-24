#include <iostream>
#include <fstream>
#include <queue> 
#include <locale>
#include <string>

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


process* read_file(string fname) {

	ifstream input_file(fname);

	if (input_file.is_open()) {
		string val;
        input_file >> val;
        int pcount = stoi(val);
        process temp_process;        
        process* parr = (process*)malloc(pcount * sizeof(process));
        if (!parr) {
            cout << "Could not assign memory to process array. Terminating..." << endl;
            return nullptr;
        }
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
                print_process(temp_process);
                p_added++;
            }
            if (ctr < 4) ctr++;
            else ctr = 0;
		}
	    input_file.close();        
        return parr;

	} else {
		cout << "File " << fname << " could not be opened." << endl;
        return nullptr;
	}
}


void fifo_scheduler() {
	
}


int main(int argc, char** argv) {
	string fname = argv[1];
	process* parr = read_file(fname);
    cout << parr << endl;
	return 0;
}