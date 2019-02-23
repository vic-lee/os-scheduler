#include <iostream>
#include <fstream>
#include <queue> 

using namespace std;


string read_file(string fname) {
	string out = "";

	ifstream input_file(fname);
	if (input_file.is_open()) {
		string val;
		while (input_file >> val) {
			if (input_file.eof()) break;
			std::cout << val;
		}
	} else {
		std::cout << "File " << fname << " could not be opened." << std::endl;
	}
	input_file.close();

	return out;
}


void fifo_scheduler() {
	
}


int main(int argc, char** argv) {
	string fname = argv[1];
	std::cout << fname << std::endl;
	read_file(fname);
	return 0;
}