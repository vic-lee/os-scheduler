#ifndef HEADER_FILE
#define HEADER_FILE

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000

struct process {
    int arrival_time;
    int interval;
    int cpu_time;
    int io_time;
};

int randomOS(int u);
void print_process(process p);
void print_process_arr(process* p, int size);
process* generate_process_arr(int size);
process* sort_parr_by_arrival(process* parr, int size);

#endif