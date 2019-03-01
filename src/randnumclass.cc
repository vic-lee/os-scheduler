#include <iostream>
#include <iomanip>
#include <fstream>

#include "header.h"

namespace scheduler {

    int RandNumAccessor::randomOS(int u) {
        std::ifstream file_rand_num("random-numbers.txt");
        if (file_rand_num) {
            int i = 0;
            std::string line; 
            while (i < cur_line) {
                getline(file_rand_num, line);
                i++;
            }
            file_rand_num.close();
            std::cout << std::setw(18)
                << "Random Number: " << line 
                << "\tRet: " << (1 + stoi(line) % u) 
                << std::endl;
            cur_line++;
            return 1 + (stoi(line) % u);
        } else {
            std::cout 
                << "Could not open random-numbers.txt. Terminating..." 
                << std::endl;
            return -1;
        }
    }
}