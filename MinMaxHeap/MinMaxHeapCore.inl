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


template<typename Comparable>
void MinMaxHeap<Comparable>::percolateUp(int hole) {
    mmHeap[TEMP_IND] = std::move(mmHeap[hole]);
    int height{getHeight(hole)};

    while(true){

        if(hole < 0 || height < 0)
            break;

        // we are in an odd node
        if(height % 2 == 1){
            if(mmHeap[TEMP_IND] < mmHeap[parent(hole)]) {
                mmHeap[hole] = std::move(mmHeap[parent(hole)]);
                hole /= 2;
                --height;
            }
            else if(mmHeap[TEMP_IND] > mmHeap[parent(parent(hole))]) {
                mmHeap[hole] = std::move(mmHeap[parent(parent(hole))]);
                hole /= 4;
                height -= 2;
            }
            else{
                mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
                break;
        }
        // we are in an even node
        }else if(height % 2 == 0){
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


template<typename Comparable>
void MinMaxHeap<Comparable>::percolateDown(int hole) {

    mmHeap[TEMP_IND] = std::move(mmHeap[hole]);

    while(hasChild(hole)){

        // we are in even level(min level)
        if(getHeight(hole) % 2 == 0)
        {
            int temp {minGCoC(hole)};
            if(mmHeap[temp] < mmHeap[TEMP_IND]) {
                mmHeap[hole] = std::move(mmHeap[temp]);
                if(isGCoI(temp, hole)) {
                    if (mmHeap[TEMP_IND] > mmHeap[parent(temp)])
                        mmHeap[temp] = std::move(mmHeap[parent(temp)]);
                }else {
                    hole = temp;
                    break;
                }
            }else
                break;
            hole = parent(temp);
            // we are in an odd level(max index)
        }else{
            int temp {maxGCoC(hole)};
            if(mmHeap[temp] > mmHeap[TEMP_IND]) {
                mmHeap[hole] = std::move(mmHeap[temp]);
                if(isGCoI(temp, hole)) {
                    if (mmHeap[TEMP_IND] < mmHeap[parent(temp)])
                        mmHeap[temp] = std::move(mmHeap[parent(temp)]);
                }else {
                    hole = temp;
                    break;
                }
            }else
                break;
            hole = parent(temp);
        }


    }
    mmHeap[hole] = std::move(mmHeap[TEMP_IND]);
}


template<typename Comparable>
void MinMaxHeap<Comparable>::buildHeap() {
    for(int i{static_cast<int>(mmHeap.size())/2}; i>0; --i)
        percolateDown(i);
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
    if(2*currentSize < mmHeap.size()){
        mmHeap.resize(mmHeap.size()/2 + 1);
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
#endif //MINMAXHEAP_MINMAXHEAPCORE_INL
