#include <iostream>
#include "MinMaxHeap/MinMaxHeap.hpp"

int main() {

    MinMaxHeap<int> b{81, 6, 8, 31, 17, 12, 28, 16, 25, 19,
                                      20, 52, 87, 14, 42, 31, 59, 71, 24, 79,
                                      63, 80, 19, 32, 15, 13, 48};

    b.setPrintType(MinMaxHeap<int>::AS_TREE);

    std::cout<<b<<std::endl;

#ifdef TEST_IS_MIN_MAX_HEAP
    std::cout<<isMinMaxHeap(b)<<std::endl;
#endif
    return 0;
}
