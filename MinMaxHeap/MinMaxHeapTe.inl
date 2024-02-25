//
// Created by KAVOSH on 2/24/2024.
//
#ifndef MINMAXHEAP_MINMAXHEAPTE_INL
#define MINMAXHEAP_MINMAXHEAPTE_INL
#include "MinMaxHeap.hpp"

template<typename Comparable>
void MinMaxHeap<Comparable>::insert(const Comparable &item) {
    expand();
    mmHeap[currentSize + 1] = item;
    percolateUp(++currentSize);
}

template<typename Comparable>
void MinMaxHeap<Comparable>::insert(Comparable&& item) {
    expand();
    mmHeap[currentSize + 1] = std::move(item);
    percolateUp(++currentSize);
}

template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap()
: mmHeap(DEFAULT_SIZE + 1)
{}

template<typename T>
std::ostream& operator<<(std::ostream &outStream, MinMaxHeap<T> &h) {
    return h.printAsTree(MinMaxHeap<T>::ROOT_IND, outStream);
}

template<typename Comparable>
void MinMaxHeap<Comparable>::makeEmpty() {
    mmHeap.clear();
    mmHeap.resize(1);
    currentSize = 0;
}

template<typename Comparable>
bool MinMaxHeap<Comparable>::empty() const {
    return currentSize == 0;
}

template<typename Comparable>
int MinMaxHeap<Comparable>::size() const {
    return currentSize;
}

template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::getMin() const {
    return mmHeap[ROOT_IND];
}

template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::getMax() const {
    switch (size()) {
        case 1:
            return mmHeap[ROOT_IND];
        case 2:
            return mmHeap[ROOT_IND*2];
        default:
            return mmHeap[ROOT_IND*2] > mmHeap[ROOT_IND*2+1] ? mmHeap[ROOT_IND * 2] : mmHeap[ROOT_IND * 2 + 1];
    }
}

#endif //MINMAXHEAP_MINMAXHEAPTE_INL
