#include <iostream>
#include "MinMaxHeap/MinMaxHeap.hpp"

int main() {

    std::vector<int> y{5, 4, 3, 2, 2, 5, 6};;

    MinMaxHeap<int> x(y.begin(), y.end());

    std::cout<<x<<std::endl;
    x.deleteMax();
    x.deleteMax();
    x.deleteMax();
    std::cout<<x<<std::endl;
    return 0;
}
