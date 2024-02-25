//
// Created by KAVOSH on 2/24/2024.
//
#ifndef MINMAXHEAP_MINMAXHEAP_HPP
#define MINMAXHEAP_MINMAXHEAP_HPP
#include <ostream>
#include <initializer_list>
#include <vector>


template <typename Comparable>
class MinMaxHeap{

public:

    MinMaxHeap();
    MinMaxHeap(std::initializer_list<Comparable> init_list);

    template<typename Iterator>
    MinMaxHeap(Iterator begin, Iterator end);

    MinMaxHeap(const MinMaxHeap& other);
    MinMaxHeap(MinMaxHeap&& other) noexcept;

    MinMaxHeap& operator=(const MinMaxHeap& other);
    MinMaxHeap& operator=(MinMaxHeap&& other) noexcept;

    void insert(const Comparable& item);
    void insert(Comparable&& item);

    void deleteMin();
    void deleteMin(Comparable& item);

    void deleteMax();
    void deleteMax(Comparable& item);

    const Comparable& getMax() const;
    const Comparable& getMin() const;

    void makeEmpty();
    bool empty() const;
    int size() const;

    template<typename T>
    friend std::ostream& operator << (std::ostream& outStream, MinMaxHeap<T>& h);

private:

    static constexpr int ROOT_IND{1}; // index of the root
    static constexpr int TEMP_IND{0}; // the first index of the heap.
    // it is used for keeping the element to avoid unnecessary swaps
    static constexpr int DEFAULT_SIZE{10};

    int currentSize{0};
    std::vector<Comparable> mmHeap;

    static int getHeight(int hole);

    // percolating an element from bottom to top
    // to find its correct position
    void percolateUp(int hole);

    // percolating an element from top to bottom
    // to find its correct position
    void percolateDown(int hole);

    void buildHeap();
    std::ostream& printAsTree(int hole, std::ostream& outStream) const;

    // resizing the vector when we need more space, or
    // we do not need some space.
    void expand();
    void reduce();

    bool hasChild(int hole) const;
    bool isGCoI(int hole, int i) const;

    int minGCoC(int hole) const;
    int maxGCoC(int hole) const;

    Comparable& getMinElement();
    Comparable& getMaxElement();

    // internal methods to get a constant reference to the min/max element
    const Comparable& getMinElement() const;
    const Comparable& getMaxElement() const;

    static int left(int hole);
    static int right(int hole);
    static int parent(int hole);

};

#include "MinMaxHeapCore.inl"
#include "MinMaxHeapTe.inl"

#endif //MINMAXHEAP_MINMAXHEAP_HPP
