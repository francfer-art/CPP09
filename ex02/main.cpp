#include "PMergeMe.hpp"

long getTimeMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000L + tv.tv_usec);
}

int main()
{
    PMergeMe p;

    std::vector<int> vec;
    p.fillContainer(vec);
    std::deque<int> deq;
    p.fillContainer(deq);

    std::cout << "Vector antes:\n";
    p.printArray(vec);
    long startVec = getTimeMicroseconds();
    p.mergeSort(vec);
    long endVec = getTimeMicroseconds();
    std::cout << "Vector después:\n";
    p.printArray(vec);

    std::cout << "\nDeque antes:\n";
    p.printArray(deq);
    long startDeq = getTimeMicroseconds();
    p.mergeSort(deq);
    long endDeq = getTimeMicroseconds();
    std::cout << "Deque después:\n";
    p.printArray(deq);
    std::cout << std::endl;
    std::cout << "Vector sorted in " << (endVec - startVec) << " microseconds\n";
    std::cout << "Deque sorted in " << (endDeq - startDeq) << " microseconds\n";

    return 0;
}
