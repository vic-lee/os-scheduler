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
