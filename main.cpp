#include <iostream>
#include "MinMaxHeap/MinMaxHeap.hpp"

int main() {

    std::vector<int> y{81, 6, 8, 31, 17, 12, 28, 16, 25, 19,
                       20, 52, 87, 14, 42, 31, 59, 71, 24, 79, 63, 80, 19, 32, 15, 13, 48};

    MinMaxHeap<int> x(y.begin(), y.end());

    MinMaxHeap<int> b(MinMaxHeap<int>(y.begin(), y.end()));

    std::cout<<b.getMin();

    return 0;
}
