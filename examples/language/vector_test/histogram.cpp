// vector::operator[]
#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>

/*
Output:
myvector contains: 9 8 7 6 5 4 3 2 1 0
*/

int main ()
{
    //std::vector<int> myvector (10);   // 10 zero-initialized elements
    int arr[] = {2,5,5,6,8,8,11};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    std::cout << "The size of the array is: " << arrSize << std::endl;
    int minVal = INT_MAX;
    int maxVal = INT_MIN;

    for (int i=0; i<arrSize; i++) 
        std::cout << std::setw(2) << i << "...";
    std::cout << std::endl;
    for (int i=0; i<arrSize; i++) {
        std::cout << std::setw(2) << arr[i] << "...";
        minVal = std::min(arr[i], minVal);
        maxVal = std::max(arr[i], maxVal);
    }
    std::cout << std::endl;
    std::cout << "min " << minVal << " max " << maxVal << std::endl;

    // assign some values:
    std::vector<int> hist(maxVal+1);   // 10 zero-initialized elements
    for (int i=0; i<arrSize; i++) {
        hist[arr[i]]++;
    }

    //int vecSize = hist.size();

    for (int i=0; i<maxVal+1; i++) 
        std::cout << std::setw(2) << i << "...";
    std::cout << std::endl;
    for (int i=0; i<maxVal+1; i++) {
        std::cout << std::setw(2) << hist[i] << "...";
    }
    std::cout << std::endl;

    return 0;
}

