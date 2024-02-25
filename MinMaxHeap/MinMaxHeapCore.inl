//
// Created by KAVOSH on 2/24/2024.
//
#ifndef MINMAXHEAP_MINMAXHEAPCORE_INL
#define MINMAXHEAP_MINMAXHEAPCORE_INL
#include <memory>
#include <cmath>
#include "MinMaxHeap.hpp"


template<typename Comparable>
int MinMaxHeap<Comparable>::getHeight(int hole) const{
    return static_cast<int>(std::log2(hole));
}


template<typename Comparable>
void MinMaxHeap<Comparable>::percolateUp(int hole) {
    mmHeap[TEMP_IND] = std::move(mmHeap[hole]);
    int height{getHeight(hole)};

    while(true){

        if(hole < 0)
            break;

        // we are in an odd node
        if(height % 2 == 1){
            if(mmHeap[TEMP_IND] < mmHeap[hole/2])
                mmHeap[hole] = std::move(mmHeap[hole/2]);
            else if(mmHeap[TEMP_IND] > mmHeap[hole/4])
                mmHeap[hole] = std::move(mmHeap[hole/4]);
            else{
                mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
                break;
        }
        // we are in an even node
        }else if(height % 2 == 0){
            if(mmHeap[TEMP_IND] > mmHeap[hole/2])
                mmHeap[hole] = std::move(mmHeap[hole/2]);
            else if(mmHeap[TEMP_IND] < mmHeap[hole/4])
                mmHeap[hole] = std::move(mmHeap[hole/4]);
            else{
                mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
                break;
            }
        }

        hole /= 2;
        --height;
    }
}


template<typename Comparable>
void MinMaxHeap<Comparable>::expand() {
    if((currentSize + 1) == mmHeap.size()) {
        mmHeap.resize(currentSize + currentSize / 2 + 2);
    }
}

template<typename Comparable>
void MinMaxHeap<Comparable>::reduce() {
    if(currentSize/2 < mmHeap.size()){
        mmHeap.resize(currentSize/2 + 1);
    }
}

template<typename Comparable>
std::ostream& MinMaxHeap<Comparable>::printAsTree(int hole, std::ostream &outStream) const {
    if(hole > currentSize)
        return outStream;

    const int height{getHeight(hole)};
    for(int i{0}; i<height; ++i)
        outStream<<"  ";
    outStream<<mmHeap[hole]<<std::endl;

    printAsTree(hole*2, outStream);
    return printAsTree(hole*2 + 1, outStream);
}

#endif //MINMAXHEAP_MINMAXHEAPCORE_INL
