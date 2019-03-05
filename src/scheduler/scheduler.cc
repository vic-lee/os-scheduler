#include "../utils/schedutil.h"
#include "scheduler.h"

namespace scheduler {

    void set_queue_front_to_running(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int quantum
    ) {
        if (q.size() == 0) {
            return;
        } else {
            if (q.front() -> state == TERMINATED) q.pop();
            if (q.size() > 0 && q.front() -> state == READY) 
                q.front() -> ready_to_run(rnum, quantum);
        }
    }


    void do_arrival_process(
        std::vector<Process> &pv, 
        std::queue<Process*> &q, 
        int cycle
    ) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].arrival_time == cycle) {
                pv[i].state = READY;
                q.push(&pv[i]);
            }
        }
    }


    void do_running_process(std::queue<Process*> &q, int quantum) {
        if (q.size() == 0) return;
        q.front() -> decr_cpu_burst();
        if (quantum != QT_UNDEF) q.front() -> update_quantum_vars(quantum);
    }


    void running_process_to_blocked(
        std::queue<Process*> &q, 
        std::vector<Process*> &v, 
        RandNumAccessor &rnum,
        std::vector<Process*> &queuepool, 
        int quantum
    ) {
        if (q.size() == 0) return;
        if (q.front() -> state == RUNNING && 
            (q.front() -> remaining_cpu_burst == 0 || 
            (quantum != QT_UNDEF && q.front() -> should_preempt(quantum)))
        ) {
            if (!q.front() -> is_finished()) {
                if (q.front() -> remaining_cpu_burst == 0) {
                    q.front() -> running_to_blocked(rnum);
                    v.push_back(q.front());
                } else {
                    if (quantum != QT_UNDEF) {
                        q.front() -> run_to_ready();
                        queuepool.push_back(q.front());
                    }
                }
            } 
            q.pop();
            std::sort(v.begin(), v.end(), comp_proc_ptr);
        }
    }


    void do_blocked_process(std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            v[i] -> decr_io_burst();
        }
    }


    void blocked_process_to_ready(
        std::queue<Process*> &q, 
        std::vector<Process*> &v,
        std::vector<Process*> &queuepool
    ) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] -> remaining_io_burst == 0) {
                if (! v[i] -> is_finished()) {
                    v[i] -> blocked_to_ready();
                    queuepool.push_back(v[i]);
                }
                v.erase(v.begin() + i);
                i--;
            }
        }
    }


    void terminate_finished_processes(std::vector<Process> &pv, int cycle) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].state != TERMINATED && pv[i].is_finished()) {
                pv[i].terminate_process(cycle); 
                pv[i].calc_turnaround_time();
            }
        }
    }


    void update_queue_waiting_time(std::vector<Process> &pv) {
        for (int i = 0; i < pv.size(); i++) {
            if (pv[i].state == READY) pv[i].waiting_time++;
        }
    }


    void add_pool_to_queue(std::queue<Process*> &q, std::vector<Process*> &pool) {
        std::sort(pool.begin(), pool.end(), comp_proc_ptr);
        for (int i = 0; i < pool.size(); i++) {
            q.push(pool[i]);
            pool.erase(pool.begin() + i); i--;
        }
    }


    void uni_do_queue_front_proc(
        std::queue<Process*> &q, 
        RandNumAccessor &rnum, 
        int &cpu_used_time,
        int &io_used_time
    ) {
        if (q.size() == 0) return;
        if (q.front() -> state == READY) {
            q.front() -> ready_to_run(rnum);
        } else {
            if (q.front() -> state == BLOCKED) {
                q.front() -> decr_io_burst(); io_used_time++;
            } else if (q.front() -> state == RUNNING) {
                q.front() -> decr_cpu_burst(); cpu_used_time++;
            }
        }
    }


    void uni_pop_finished_queue_front(std::queue<Process*> &q, const int cycle) {
        if (q.size() == 0) return;
        if (q.front() -> is_finished()) {
            q.front() -> terminate_process(cycle);
            q.front() -> calc_turnaround_time();
            q.pop(); 
        }
    }


    void uni_alternate_run_blocked(std::queue<Process*> &q, RandNumAccessor &rnum) {
        if (q.size() == 0) return;
        bool is_run_finished = q.front() -> state == RUNNING && q.front() -> remaining_cpu_burst == 0;
        bool is_block_finished = q.front() -> state == BLOCKED && q.front() -> remaining_io_burst == 0;
        if (!q.front() -> is_finished()) {
            if (is_run_finished) {
                q.front() -> running_to_blocked(rnum);
            } else if (q.front() -> state == READY || is_block_finished) {
                q.front() -> blocked_to_ready();
                q.front() -> ready_to_run(rnum); 
            }
        }
    }


    bool sjf_sort(Process* a, Process* b) {
        /**
         * This function sorts based on lowest remaining cpu time. 
         * CPU time attr. is decremented every cycle, if a process uses cpu. 
         * Input:   2 process pointers
         * Output:  true if 1st process should have a lower index than the 2nd.
         */
        if (a -> cpu_time < b -> cpu_time) return true;
        else if (a -> cpu_time == b -> cpu_time) return a -> pid < b -> pid;
        return false;
    }


    void sjf_do_arrival_process(
        std::vector<Process> &pv, 
        std::vector<Process*> &readypool, 
        int cycle 
    ) {
        for (int i = 0; i < pv.size(); i++) {
            if ( pv[i].arrival_time == cycle ) {
                pv[i].state = READY;
                readypool.push_back(&pv[i]);
            }
        }
        std::sort(readypool.begin(), readypool.end(), sjf_sort);
    }


    void sjf_ready_to_run(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &readypool, 
        RandNumAccessor &rnum
    ) {
        if (runproc.size() == 0 && readypool.size() > 0) {  
            runproc.push_back(readypool[0]);
            runproc[0] -> ready_to_run(rnum);
            readypool.erase(readypool.begin());
        }
    }


    void sjf_do_running_process(std::vector<Process*> &runproc) {
        if (runproc.size() > 0) {
            runproc[0] -> decr_cpu_burst();
            if (runproc[0] -> is_finished()) runproc.erase(runproc.begin());
        }
    }


    void sjf_running_to_blocked(
        std::vector<Process*> &runproc, 
        std::vector<Process*> &blocked_pool, 
        RandNumAccessor &rnum
    ) {
        if (runproc.size() == 0) return;
        if (!runproc[0] -> is_finished() && runproc[0] -> is_cpu_burst_finished()) {
            runproc[0] -> running_to_blocked(rnum);
            blocked_pool.push_back(runproc[0]);
            runproc.erase(runproc.begin());
        }
    }


    void sjf_blocked_to_ready(
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    ) {
        for (int i = 0; i < blockedpool.size(); i++) {
            if (blockedpool[i] -> is_io_burst_finished()) {
                blockedpool[i] -> blocked_to_ready();
                readypool.push_back(blockedpool[i]);
                blockedpool.erase(blockedpool.begin() + i); 
                i--;
            }
        }
        std::sort(readypool.begin(), readypool.end(), sjf_sort);
    }


    void sjf_rm_terminated_from_vect(std::vector<Process*> &v) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] -> state == TERMINATED) {
                v.erase(v.begin() + i);
                i--;
            }
        }
    }


    void sjf_clear_terminated_processes(
        std::vector<Process*> &runningproc, 
        std::vector<Process*> &blockedpool, 
        std::vector<Process*> &readypool
    ) {
        sjf_rm_terminated_from_vect(runningproc);
        sjf_rm_terminated_from_vect(blockedpool);
        sjf_rm_terminated_from_vect(readypool);
    }


    void sjf_update_ready_time(std::vector<Process*> &readypool) {
        for (int i = 0; i < readypool.size(); i++) {
            readypool[i] -> waiting_time++;
        }
    }


}

