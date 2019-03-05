# include<cmath>
#include <vector>
#include <string>

#include "schedutil.h"

namespace scheduler {

    float calc_avg_wait_time(std::vector<Process> const &vect) {
        int total_wait = 0;
        for (unsigned int i = 0; i < vect.size(); i++) {
            total_wait += vect[i].waiting_time;
        }
        float avg = (float) total_wait / (float) vect.size();
        return avg;
    }


    float calc_avg_turnaround_time(std::vector<Process> const &vect) {
        int total_turn = 0;
        for (unsigned int i = 0; i < vect.size(); i++) {
            total_turn += vect[i].turnaround_time;
        }
        float avg = (float) total_turn / (float) vect.size();
        return avg;
    }


    float calc_throughput(std::vector<Process> const &vect, int cycle) {
        float throughput = (float) vect.size() / ((float) cycle / (float) 100);
        return throughput;
    }


    float calc_cpu_util(int cpu_used_time, int cycle) {
        float u = (float) cpu_used_time / (float) cycle;
        return u;
    }


    float calc_io_util(int io_used_time, int cycle) {
        float u = (float) io_used_time / (float) cycle;
        return u;
    }


}