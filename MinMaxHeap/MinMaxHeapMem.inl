//
// Created by mzahr on 2/29/2024.
//
#ifndef MINMAXHEAP_MINMAXHEAPMEM_INL
#define MINMAXHEAP_MINMAXHEAPMEM_INL

#include "MinMaxHeap.hpp"

template<typename Comparable>
MinMaxHeap<Comparable>::MinMaxHeap()
        : mmHeap(DEFAULT_SIZE + 1)
{}


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

#endif //MINMAXHEAP_MINMAXHEAPMEM_INL
