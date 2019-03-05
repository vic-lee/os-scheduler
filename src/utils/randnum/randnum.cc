#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
#include "randnum.h"
// #include "header.h"

namespace scheduler {

    int RandNumAccessor::cur_line = 1;

    std::tuple<int, int> RandNumAccessor::randomOS(int u) {
        std::ifstream file_rand_num("../src/random-numbers.txt");
        if (file_rand_num) {
            int i = 0;
            std::string line; 
            while (i < cur_line) {
                getline(file_rand_num, line);
                i++;
            }
            file_rand_num.close();
            cur_line++;
            int randnum = stoi(line);
            int ret = 1 + randnum % u;
            return std::make_tuple(ret, randnum);
        } else {
            std::cout 
                << "ERROR: Could not open random-numbers.txt. Terminating..." 
                << std::endl;
            return std::make_tuple(-1, -1);
        }
    }
}