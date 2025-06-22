#include "PMergeMe.hpp"

template <typename Container, typename T>
typename Container::iterator binaryInsert(Container& sorted, const T& value) {
    typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    return sorted.insert(pos, value);
}


template <typename Container>
void PMergeMe::mergeSort(Container& container) {
    if (container.size() <= 1)
        return;

    Container smallerHalf;
    Container largerHalf;

    typename Container::iterator it = container.begin();
    while (it != container.end()) {
        typename Container::iterator first = it++;
        if (it != container.end()) {
            if (*first <= *it) {
                smallerHalf.push_back(*first);
                largerHalf.push_back(*it);
            } else {
                smallerHalf.push_back(*it);
                largerHalf.push_back(*first);
            }
            ++it;
        } else {
            largerHalf.push_back(*first);
        }
    }

    // Ordenar recursivamente los menores
    mergeSort(smallerHalf);

    // Insertar los mayores usando inserción binaria (solo válido con vector)
    typename Container::iterator insertIt = largerHalf.begin();
    while (insertIt != largerHalf.end()) {
        binaryInsert(smallerHalf, *insertIt);
        ++insertIt;
    }

    container = smallerHalf;
}

template <typename Container>
void PMergeMe::printArray(Container &container) {
    typename Container::iterator it;
    for (it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
void PMergeMe::fillContainer(Container &container) {
    // I want to fill container with 3000 unique random integers
    int size = 2000;
    int mod = 10000;
    for (int i = 0; i < size; ++i) {
        container.push_back(rand() % mod); // Random integers between 0 and 9999
    }
}
