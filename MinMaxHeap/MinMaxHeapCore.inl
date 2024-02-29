//
// Created by KAVOSH on 2/24/2024.
//
#ifndef MINMAXHEAP_MINMAXHEAPCORE_INL
#define MINMAXHEAP_MINMAXHEAPCORE_INL


#include <memory>
#include <cmath>
#include "MinMaxHeap.hpp"


template<typename Comparable>
int MinMaxHeap<Comparable>::getHeight(int hole){

    return static_cast<int>(std::log2(hole));
}

/*
 * find the correct position of an element by
 * moving it up each time. It is mainly used for
 * insertion of a new element.
 */
template<typename Comparable>
void MinMaxHeap<Comparable>::percolateUp(int hole) {

    // the element we want to find its correct position is
    // here to avoid unnecessary swaps.
    mmHeap[TEMP_IND] = std::move(mmHeap[hole]);

    int height{getHeight(hole)};

    while(true){

        if(hole < 0 || height < 0)
            break;

        // we are in an odd node(max level)
        if(height % 2 == 1){
            // check if the parent is greater. If so move it to the hole
            if(mmHeap[TEMP_IND] < mmHeap[parent(hole)]) {
                mmHeap[hole] = std::move(mmHeap[parent(hole)]);
                hole /= 2;
                --height;
            }
            // check if the grandparent is lesser. If so move it to the hole
            else if(mmHeap[TEMP_IND] > mmHeap[parent(parent(hole))]) {
                mmHeap[hole] = std::move(mmHeap[parent(parent(hole))]);
                hole /= 4;
                height -= 2;
            }
            // the correct position is found.
            else{
                mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
                break;
        }
        // we are in an even node (min level)
        }else if(height % 2 == 0){
            // checkout top comments since they are symmetric case of each other
            if(mmHeap[TEMP_IND] > mmHeap[parent(hole)]) {
                mmHeap[hole] = std::move(mmHeap[parent(hole)]);
                hole /= 2;
                --height;
            }
            else if(mmHeap[TEMP_IND] < mmHeap[parent(parent(hole))]) {
                mmHeap[hole] = std::move(mmHeap[parent(parent(hole))]);
                hole /= 4;
                height -= 2;
            }
            else{
                mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
                break;
            }
        }
    }
}

/*
 * The function is used in order to find
 * the correct position of an element already
 * in the queue.
 */
template<typename Comparable>
void MinMaxHeap<Comparable>::percolateDown(int holeq) {

    while(hasChild(holeq)){

        int tempq{holeq};

        // min level
        if(getHeight(tempq) % 2 == 0 ){
            holeq = minGCoC(tempq);

            // if the element is bigger than the parent then
            // we need to swap them because they violate the minMax property
            if(mmHeap[holeq] <mmHeap[tempq]){
                std::swap(mmHeap[holeq], mmHeap[tempq]);

                // if the holeq we just picked is a specifically grand child of the
                // tempq then it means the holeq must be less than its parent.
                if(isGCoI(holeq, tempq)){
                    if(mmHeap[holeq] > mmHeap[parent(holeq)]){
                        std::swap(mmHeap[holeq], mmHeap[parent(holeq)]);
                    }
                }else
                    break;
            }else
                break;
            // max level
        }else{

            // checkout above comments because these are symmetric case of each other
            holeq = maxGCoC(tempq);

            if(mmHeap[holeq] > mmHeap[tempq]){
                std::swap(mmHeap[holeq], mmHeap[tempq]);

                if(isGCoI(holeq, tempq)){
                    if(mmHeap[holeq] < mmHeap[parent(holeq)]){
                        std::swap(mmHeap[holeq], mmHeap[parent(holeq)]);
                    }
                }else
                    break;
            }else
                break;
        }
    }
}

template<typename Comparable>
void MinMaxHeap<Comparable>::buildHeap() {

    for(int i{currentSize/2}; i > 0; i--) {
        percolateDown(i);
    }
}


template<typename Comparable>
void MinMaxHeap<Comparable>::expand() {
    if(currentSize == 0)
        mmHeap.resize(DEFAULT_SIZE);
    else if(currentSize + 1 == mmHeap.size())
        mmHeap.resize(2*currentSize + 1);
}


template<typename Comparable>
void MinMaxHeap<Comparable>::reduce() {
#ifdef REDUCE_MINMAX_HEAP_SIZE
    if(2*currentSize < mmHeap.size()){
        mmHeap.resize(mmHeap.size()/2 + 1);
    }
#endif
}


template<typename Comparable>
std::ostream& MinMaxHeap<Comparable>::printAsTree(int hole, std::ostream &outStream) const {
    if(hole > currentSize)
        return outStream;

    const int height{getHeight(hole)};
    for(int i{0}; i<height; ++i)
        outStream<<"  ";
    outStream<<mmHeap[hole]<<std::endl;

    printAsTree(left(hole), outStream);
    return printAsTree(right(hole), outStream);
}


template<typename Comparable>
int MinMaxHeap<Comparable>::left(int hole){
    return 2*hole;
}


template<typename Comparable>
int MinMaxHeap<Comparable>::right(int hole){
    return 2*hole + 1;
}


template<typename Comparable>
int MinMaxHeap<Comparable>::parent(int hole){
    return hole/2;
}


template<typename Comparable>
bool MinMaxHeap<Comparable>::hasChild(int hole) const {
    if (left(hole) <= currentSize || right(hole) <= currentSize)
        return true;
    return false;
}


// return the minimum grand child or child of hole. -1 if there exist nothing.
template<typename Comparable>
int MinMaxHeap<Comparable>::minGCoC(int hole) const{
    const std::vector<int> lec{left(hole),
                               right(hole),
                               left(right(hole)),
                               right(left(hole)),
                               left(left(hole)),
                               right(right(hole))};

    int min{-1};
    bool init{true};

    for(auto ind: lec)
        if(ind <= currentSize){
            if(init){
                min = ind;
                init = false;
            }
            if(mmHeap[ind] < mmHeap[min])
                min = ind;
        }

    return min;
}


// return the maximum grand child or child of hole. -1 if there exist nothing.
template<typename Comparable>
int MinMaxHeap<Comparable>::maxGCoC(int hole) const{
    const std::vector<int> lec{left(hole),
                               right(hole),
                               left(right(hole)),
                               right(left(hole)),
                               left(left(hole)),
                               right(right(hole))};
    int max{-1};
    bool init{true};

    for(auto ind: lec)
        if(ind <= currentSize){
            if(init){
                max = ind;
                init = false;
            }
            if(mmHeap[ind] > mmHeap[max])
                max = ind;
        }

    return max;
}


// checks if hole is a grand child of i
template<typename Comparable>
bool MinMaxHeap<Comparable>::isGCoI(int hole, int i) const{
    const std::vector<int> lec{left(right(i)),
                               right(left(i)),
                               left(left(i)),
                               right(right(i))};

    for(auto ind: lec)
        if(ind <= currentSize && (hole == ind)){
            return true;
        }

    return false;
}


template<typename Comparable>
std::ostream &MinMaxHeap<Comparable>::printAsArray(std::ostream &outStream) const {
    for(int i{1}; i <= currentSize; ++i)
        outStream<<mmHeap[i]<<' ';
    outStream<<std::endl;
    return outStream;
}

template<typename Comparable>
const Comparable &MinMaxHeap<Comparable>::operator[](std::size_t index) const {
    return mmHeap[index];
}

template<typename Comparable>
int MinMaxHeap<Comparable>::getMinInd() const{
    return ROOT_IND;
}

template<typename Comparable>
int MinMaxHeap<Comparable>::getMaxInd() const{
    switch (size()) {
        case 1:
            return ROOT_IND;
        case 2:
            return left(ROOT_IND);
        default:
            return mmHeap[left(ROOT_IND)] > mmHeap[right(ROOT_IND)] ?
                   left(ROOT_IND) : right(ROOT_IND);
    }
}


#endif //MINMAXHEAP_MINMAXHEAPCORE_INL
