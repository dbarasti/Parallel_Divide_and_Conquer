//
// Created by dbara on 07/05/20.
//

#ifndef DIVIDEANDCONQUER_PARALLELFRAMEWORK_DCFRAMEWORK_HPP
#define DIVIDEANDCONQUER_PARALLELFRAMEWORK_DCFRAMEWORK_HPP

#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

template<typename Tin, typename Tout>
class DCFramework {
protected:
    virtual bool baseCase(Tin) = 0;

    virtual Tout solve(Tin) = 0;

    virtual std::vector<Tin> divide(Tin) = 0;

    virtual Tout conquer(std::vector<Tout>) = 0;

    virtual bool checkCutoff(Tin) = 0;

public:
    Tout run_parallel(Tin input) {
        std::cout << "Running run_parallel()" << std::endl;

        if (baseCase(input)) return solve(input);

        auto subProblems = divide(input);
        std::vector<Tout> subResults(subProblems.size());
        // list of threads
        std::vector<std::thread> threads;

        if (!checkCutoff(subProblems[0])) {
            auto threadLambda = [&subResults, &subProblems, this](const int i) {
                subResults[i] = run_parallel(subProblems[i]);
            };

            for (auto i = 0; i != subProblems.size(); i++) {
                threads.push_back(std::thread(threadLambda, i));
            }
        } else {
            std::cout << "cutting off" << std::endl;
            auto threadLambda = [&subResults, &subProblems, this](const int i) {
                subResults[i] = run_sequential(subProblems[i]);
            };
            for (auto i = 0; i != subProblems.size(); i++) {
                threads.push_back(std::thread(threadLambda, i));
            }
        }


        for (std::thread &t: threads) {
            t.join();
        }

        auto result = conquer(subProblems);
        return (result);
    }

    Tout run_sequential(Tin input) {
        // std::cout << "Running run_sequential()" << std::endl;

        if (baseCase(input)) return (solve(input));

        auto subProblems = divide(input);

        std::transform(subProblems.begin(),
                       subProblems.end(),
                       subProblems.begin(),
                       [&](Tin in) {
                           auto res = run_sequential(in);
                           return (res);
                       });

        auto result = conquer(subProblems);
        return (result);
    }
};


#endif //DIVIDEANDCONQUER_PARALLELFRAMEWORK_DCFRAMEWORK_HPP
