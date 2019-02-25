#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../header.h"

using namespace std;


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
