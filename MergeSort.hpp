//
// Created by dbara on 09/05/20.
//

#ifndef DIVIDEANDCONQUER_PARALLELFRAMEWORK_MERGESORT_HPP
#define DIVIDEANDCONQUER_PARALLELFRAMEWORK_MERGESORT_HPP


#define CUTOFF 125000000
#define STOPTAILREC 500

#include <cstring>
#include "DCFramework.hpp"

//maximum value for arrays elements
const int MAX_NUM = 99999.9;

static int *generateRandomArray(int n) {
    srand((time(0)));
    int *numbers = new int[n];
    for (int i = 0; i < n; i++)
        numbers[i] = (int) (rand()) / ((RAND_MAX / MAX_NUM));
    return numbers;
}

// Operand and Results share the same format
struct ops {
    int *array = nullptr;            //array (to sort/sorted)
    int left = 0;                     //left index
    int right = 0;                    //right index
};

typedef struct ops Operand;
typedef struct ops Result;

class MergeSort: public DCFramework<Operand , Result>{
protected:
    bool baseCase(Operand op) override {
        // std::cout << "base case reached" << std::endl;
        return (op.right - op.left <= STOPTAILREC);
    }

    Result solve(Operand op) override {
        // std::cout << "sorting array using std::sort" << std::endl;
        std::sort(&(op.array[op.left]), &(op.array[op.right + 1]));
        return op;
    }

    std::vector<Operand> divide(Operand op) override {
        std::vector<Operand> result;
        int mid = (op.left + op.right) / 2;
        Operand a;
        a.array = op.array;
        a.left = op.left;
        a.right = mid;
        result.push_back(a);

        Operand b;
        b.array = op.array;
        b.left = mid + 1;
        b.right = op.right;
        result.push_back(b);
        return result;
    }

    Result conquer(std::vector<Result> res) override {
        Operand ret;
        int *a = res[0].array;
        int mid = res[0].right;
        int left = res[0].left, right = res[1].right;
        int size = right - left + 1;
        int *tmp = new int[size];
        int i = left, j = mid + 1;

        //merge in order
        for (int k = 0; k < size; k++) {
            if (i <= mid && (j > right || a[i] <= a[j])) {
                tmp[k] = a[i];
                i++;
            } else {
                tmp[k] = a[j];
                j++;
            }
        }

        //copy back
        memcpy(a + left, tmp, size * sizeof(int));

        delete[] tmp;

        //build the result
        ret.array = a;
        ret.left = left;
        ret.right = right;
        return ret;
    }

    bool checkCutoff(Operand op) override {
        return (op.right - op.left <= CUTOFF);
    }
};


#endif //DIVIDEANDCONQUER_PARALLELFRAMEWORK_MERGESORT_HPP
