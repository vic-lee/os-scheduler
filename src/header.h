#ifndef HEADER_FILE
#define HEADER_FILE

#define EOPROCESS 3
#define RAND_NUM_FILE_SIZE 100000
#define QT_UNDEF -1
#define UNSTARTED "unstarted"
#define READY "ready"
#define RUNNING "running"
#define BLOCKED "blocked"
#define TERMINATED "terminated"

#include <string>

namespace scheduler {

    const std::string VERBOSE = "--verbose";
    const std::string SHOWRAND = "--show-random";
    const std::string DFTOUT = "--default";
    static std::string OUT_MODE; 

    const std::string PRINT_START_MSG = "This detailed printout gives the state and remaining burst for each process\n";

}

#endif