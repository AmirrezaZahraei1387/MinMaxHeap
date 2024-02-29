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
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::insert(Comparable&& item) {
    expand();
    mmHeap[currentSize + 1] = std::move(item);
    percolateUp(++currentSize);
}


template<typename T>
std::ostream& operator<<(std::ostream &outStream, MinMaxHeap<T> &h) {
    switch (h.currentPt) {
        case MinMaxHeap<T>::AS_TREE:
            return h.printAsTree(MinMaxHeap<T>::ROOT_IND, outStream);
        case MinMaxHeap<T>::AS_ARRAY:
            return h.printAsArray(outStream);
        default: // disabled
            return outStream;
    }
}


template<typename Comparable>
void MinMaxHeap<Comparable>::makeEmpty() {
    mmHeap.clear();
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
const Comparable &MinMaxHeap<Comparable>::findMin() const {
    return mmHeap[getMinInd()];
}


template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::findMax() const {
    return mmHeap[getMaxInd()];
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMin() {
    mmHeap[getMinInd()] = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}

template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMin(Comparable &item) {
    item = std::move(mmHeap[getMinInd()]);
    mmHeap[getMinInd()] = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMax() {
    int max{getMaxInd()};
    mmHeap[max] = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(max);
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMax(Comparable &item) {
    int max{getMaxInd()};
    item = std::move(mmHeap[max]);
    mmHeap[max] = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(max);
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::setPrintType(MinMaxHeap::PrintType pt){
    currentPt = pt;
}

#ifdef TEST_IS_MIN_MAX_HEAP
template<typename T>
bool isMinMaxHeap(const MinMaxHeap<T>& heap, int node) {

    using mmh = MinMaxHeap<T>;


    while (heap.hasChild(node)) {

        if (mmh::getHeight(node) % 2 == 0) {
            int temp{heap.minGCoC(node)};

            if (heap[temp] < heap[node])
                return false;

            if (heap.isGCoI(temp, node))
                if(heap[node] > heap[mmh::parent(temp)])
                    return false;
        }else{
            int temp{heap.maxGCoC(node)};

            if (heap[temp] > heap[node])
                return false;

            if (heap.isGCoI(temp, node))
                if(heap[node] < heap[mmh::parent(temp)])
                    return false;
        }

        if(mmh::right(node) <= heap.size())
            if(!isMinMaxHeap(heap, mmh::right(node)))
                return false;
        if(mmh::left(node) <= heap.size())
            if(!isMinMaxHeap(heap, mmh::left(node)))
                return false;
        break;
    }

    return true;
}
template<typename T>
bool isMinMaxHeap(const MinMaxHeap<T> &heap) {
    // starting with the root index
    return isMinMaxHeap(heap, MinMaxHeap<T>::ROOT_IND);
}

template<typename Comparable>
template<typename Iterator>
void MinMaxHeap<Comparable>::reBuild(Iterator begin, Iterator end) {
    makeEmpty();
    currentSize = end - begin;
    expand();

    int i{1};
    for(auto element{begin}; element < end; ++element, ++i)
        mmHeap[i] = *element;
    buildHeap();
}

#endif

#endif //MINMAXHEAP_MINMAXHEAPTE_INL
