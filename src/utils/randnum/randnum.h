#ifndef RAND_NUM_ACCESSOR_HEADER
#define RAND_NUM_ACCESSOR_HEADER

#include <tuple>

namespace scheduler {
    class RandNumAccessor {
        public: 
            static int cur_line;
            std::tuple<int, int> randomOS(int u);
    };
}

#endif