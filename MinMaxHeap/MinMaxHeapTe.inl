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


template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap()
: mmHeap(DEFAULT_SIZE + 1)
{}


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
    return getMinElement();
}


template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::findMax() const {
    return getMaxElement();
}


template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap(std::initializer_list<Comparable> init_list)
:mmHeap(init_list.size()+1) , currentSize(init_list.size())
{
    int i{1};
    for(auto x{init_list.begin()}; x < init_list.end(); ++x, ++i)
        mmHeap[i] = *x;
    buildHeap();
    expand();
}

template<typename Comparable>
template<typename Iterator>
MinMaxHeap<Comparable>::MinMaxHeap(Iterator begin, Iterator end)
: mmHeap(end - begin + 1), currentSize(end - begin)
{
    int i{1};
    for(auto element{begin}; element < end; ++element, ++i)
        mmHeap[i] = *element;
    buildHeap();
    expand();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMin() {
    getMinElement() = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}

template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMin(Comparable &item) {
    item = getMinElement();
    getMinElement() = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMax() {
    getMaxElement() = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}


template<typename Comparable>
void MinMaxHeap<Comparable>::deleteMax(Comparable &item) {
    item = getMaxElement();
    getMaxElement() = std::move(mmHeap[currentSize]);
    --currentSize;
    percolateDown(ROOT_IND);
    reduce();
}


template<typename Comparable>
Comparable &MinMaxHeap<Comparable>::getMinElement() {
    return mmHeap[ROOT_IND];
}


template<typename Comparable>
Comparable &MinMaxHeap<Comparable>::getMaxElement() {
    switch (size()) {
        case 1:
            return mmHeap[ROOT_IND];
        case 2:
            return mmHeap[left(ROOT_IND)];
        default:
            return mmHeap[left(ROOT_IND)] > mmHeap[right(ROOT_IND)] ?
                   mmHeap[left(ROOT_IND)] : mmHeap[right(ROOT_IND)];
    }
}


template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::getMinElement() const {
    return mmHeap[ROOT_IND];
}


template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::getMaxElement() const {
    switch (size()) {
        case 1:
            return mmHeap[ROOT_IND];
        case 2:
            return mmHeap[left(ROOT_IND)];
        default:
            return mmHeap[left(ROOT_IND)] > mmHeap[right(ROOT_IND)] ?
                   mmHeap[left(ROOT_IND)] : mmHeap[right(ROOT_IND)];
    }
}


template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap(const MinMaxHeap &other) {
    mmHeap = other.mmHeap;
    currentSize = other.size();
}

template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap(MinMaxHeap &&other) noexcept{
    mmHeap = std::move(other.mmHeap);
    currentSize = other.size();
    other.makeEmpty();
}

template<typename Comparable>
MinMaxHeap<Comparable>& MinMaxHeap<Comparable>::operator=(const MinMaxHeap &other) {
    if(&other != this) {
        mmHeap = other.mmHeap;
        currentSize = other.size();
    }
    return *this;
}

template<typename Comparable>
MinMaxHeap<Comparable>& MinMaxHeap<Comparable>::operator=(MinMaxHeap &&other) noexcept {
    if(&other != this) {
        mmHeap = std::move(other.mmHeap);
        currentSize = other.size();
        other.makeEmpty();
    }
    return *this;
}

template<typename Comparable>
void MinMaxHeap<Comparable>::setPrintType(MinMaxHeap::PrintType pt){
    currentPt = pt;
}


#endif //MINMAXHEAP_MINMAXHEAPTE_INL
