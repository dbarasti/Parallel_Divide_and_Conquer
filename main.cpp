#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <chrono>
#include "MergeSort.hpp"



/* ------------------------------------------------------------------ */
//maximum value for arrays elements

static bool isArraySorted(const int *a, int n) {
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            return false;
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <num_elements> <par/seq>" << std::endl;
        exit(-1);
    }

    int num_elem = atoi(argv[1]);
    std::string version = argv[2];
    //generate a random array
    std::cout << "Generating random values" << std::endl;
    int *numbers = generateRandomArray(num_elem);

    auto ms = new MergeSort();

    //build the operand
    Operand op;
    op.array = numbers;
    op.left = 0;
    op.right = num_elem - 1;
    Result res;

    auto start = std::chrono::high_resolution_clock::now();
    if (version == "seq") {
        std::cout << "Running sequential" << std::endl;
        res = ms->run_sequential(op);
    }
    if (version == "par") {
        std::cout << "Running parallel" << std::endl;
        res = ms->run_parallel(op);
    }
    if (version != "par" && version != "seq") {
        std::cout<<"version " << version << " is not in an accepted format. Use par or seq" << std::endl;
        return 1;
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    auto usec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    std::cout << "Checking correction of the result" << std::endl;
    if (!isArraySorted(res.array, res.right - res.left + 1)) {
        fprintf(stderr, "Error: array is not sorted!!\n");
        exit(-1);
    }
    printf("Time (usecs): %ld\n", usec);

    return 0;
}