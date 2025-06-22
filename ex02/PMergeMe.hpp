#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <sys/time.h>
#include <iterator>

class PMergeMe {
    public:
    PMergeMe(){
        
    };
    ~PMergeMe(){
        
    };
    template <typename Container>
    void mergeSort(Container &container);
    template <typename Container>
    void printArray(Container &container);
    template <typename Container>
    void fillContainer(Container &container);
};

#include "PMergeMe.tpp" 

#endif
