# MinMaxHeap

### Definition
____
A min-max heap is a data structure that supports both deleteMin and deleteMax in O(log N) per
operation. The structure is identical to a binary heap, but the heap-order property is that for any node, X,
at even depth, the element stored at X is smaller than the parent but larger than the grandparent (where
this makes sense), and for any node X at odd depth, the element stored at X is larger than the parent
but smaller than the grandparent.

### Build
___
In order to test the library you can use the outer makefile or
CmakeLists.txt to do so; However if you want to use it for internal
use in another project you can use the cmake inside the MinMaxH to link
to your project.

### How to Use the App

In order to use the small console application provided mostly for
testing purposes first build the whole project. Then you can run the
executable and use the following commands:

1- buildHeap arguments

2- insertHeap arguments

3- deleteMin

4- deleteMax

5- findMin

6- findMax

7- check (it checks if the heap is actually a minmax heap or not)

8- print

9- getSize

10- exit (exit the app)

11- clear

### Using the MinMaxH library

#### Initialization
To make a new heap you should make a new instance of MinMaxHeap template class.
The class requires a comparable object meaning the object must at least overload
comparison operators including >, <, >=, <=.

You can initialize your newly created heap in the following methods:

```c++
int main(){

    // using default constructor. 
    // in this case the heap will be initlized with
    // a default size.
    MinMaxHeap<int> heap;
   
    //  using initlizer list
    // in this particular case the heap will be filled 
    // will the values provided and then buildHeap operation
    // is invoked
    MinMaxHeap<int> heap1{5, 4, 3, 2, 1, 45};
    
    // using iterators
    // the same as initlizing with initilizer list
    MinMaxHeap<int> heap2();
    
    return 0;
}
```

#### Useful Operations

```c++
int main(){
    MinMaxHeap<int> heap{50, 56, 44, 33, 22};
    
    // insert 6 to the heap. uses percolate up mechanism
    heap.insert(6);
    
    std::vector<int> e{5, 4, 3, 2, 1, 3};
    // clear the whole heap and rebuild it from the 
    // array segment given to it
    heap.reBuild(e.begin(), e.end());
    
    // deleteMin/ deleteMax deletes the min or max element
    //in the heap. the second version gets a reference to a variable
    // and put the min or max value before deleting in it.
    heap.deleteMin();
    int hello{};
    heap.deleteMax(hello);
    
    // findMin/ findMax return a constant reference to the max
    // or min element
    int max = heap.findMax();
    
    // returns the number of elements in the heap. it is
    // not equal with the length of the internal array
    // representaion of the heap.
    heap.size();
    
    // true if the heap is emty, false otherwise
    heap.empty();
    
    // completely clear the heap
    heap.makeEmpty();
    return 0;
}
```

#### Printing the Heap
for testing purposes it is a good flexibility to be able to 
print the heap to the console. The << operator is overloaded, so
you can use std::ostream to print the heap.

```c++
int main(){
    MinMaxHeap<int> heap{50, 56, 44, 33, 22};
    std::cout<<heap<<std::endl;
    
    //prints
    //22
    //  56
    //    33
    //    50
    //  44
    return 0;
}
```

There three types of printing that we support.

AS_ARRAY: prints the heap flat on one single line.

AS_TREE: Prints the heap in the form of a tree. It is the default
printing type.

DISABLED: Completely disable printing.

you can set the printing type via setPrintType method.
```c++
int main(){
    MinMaxHeap<int> heap{50, 56, 44, 33, 22};
    heap.setPrintType(MinMaxHeap<int>::AS_ARRAY);
    std::cout<<heap<<std::endl;
    return 0;
}
```

#### OtherUseFul Features

#### reduce
Each that you delete an element from the heap the size of the
heap decreases. MeanWhile, the internal array will not change in size.
By default, we use reduce operation that checks if the heap is half empty,
shrink it. If this operation is not desirable for performance reasons you can
remove the "REDUCE_MINMAX_HEAP_SIZE" directive from the ConfigDir.hpp. This will 
disable this operation.

#### isMinMaxHeap

```c++
template<typename T>
friend bool isMinMaxHeap(const MinMaxHeap<T>& heap);
```

the function isMinMaxHeap is a friend function of the class
which checks if the heap is really MinMax or not. This function is
used for testing purposes while developing the class more and more.
It is by default present, but you can remove by removing the directive
"TEST_IS_MIN_MAX_HEAP" from ConfigDir.hpp.










