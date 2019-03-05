#ifndef SCHEDULER_HEADER
#define SCHEDULER_HEADER

#include <iostream>
#include <algorithm>
// #include <functional>
#include <queue>
#include <vector>
#include "../process/process.h"

namespace scheduler {

    void set_queue_front_to_running(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int quantum = QT_UNDEF
    );

    void do_arrival_process(
        std::vector<Process> &pv, 
        std::queue<Process*> &q, 
        int cycle
    );    

    void do_running_process(std::queue<Process*> &q, int quantum = QT_UNDEF);

    void running_process_to_blocked(
        std::queue<Process*> &q, 
        std::vector<Process*> &v, 
        RandNumAccessor &rnum,
        std::vector<Process*> &queuepool, 
        int quantum = QT_UNDEF
    );

    void do_blocked_process(std::vector<Process*> &v);

    void blocked_process_to_ready(
        std::queue<Process*> &q, 
        std::vector<Process*> &v,
        std::vector<Process*> &queuepool
    );

    void terminate_finished_processes(std::vector<Process> &pv, int cycle);

    void update_queue_waiting_time(std::vector<Process> &pv);

    void add_pool_to_queue(std::queue<Process*> &q, std::vector<Process*> &pool);

    void uni_do_queue_front_proc(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int &cpu_used_time,
        int &io_used_time
    );

    void uni_pop_finished_queue_front(std::queue<Process*> &q, const int cycle);

    void uni_alternate_run_blocked(std::queue<Process*> &q, RandNumAccessor &rnum);

    bool sjf_sort(Process* a, Process* b);

    void sjf_do_arrival_process(
        std::vector<Process> &pv, 
        std::vector<Process*> &readypool, 
        int cycle 
    );

    void sjf_ready_to_run(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &readypool, 
        RandNumAccessor &rnum
    );

    void sjf_do_running_process(std::vector<Process*> &runproc);

    void sjf_running_to_blocked(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &blocked_pool, 
        RandNumAccessor &rnum
    );

    void sjf_blocked_to_ready(
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    );

    void sjf_rm_terminated_from_vect(std::vector<Process*> &v);

    void sjf_clear_terminated_processes(
        std::vector<Process*> &runningproc, 
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    ); 

    void sjf_update_ready_time(std::vector<Process*> &readypool);

}

#endif