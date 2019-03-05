#ifndef RAND_NUM_ACCESSOR_HEADER
#define RAND_NUM_ACCESSOR_HEADER

#include <tuple>

namespace scheduler {
    class RandNumAccessor {
        public: 
            int cur_line = 1;
            std::tuple<int, int> randomOS(int u);
    };
}

#endif