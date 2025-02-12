// #define CATCH_CONFIG_MAIN
#include "header/catch.hpp"
#include "header/bucketSort.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

#include <random> // random_device, mt19937, mersenne_engine
static int s_Allocations = 0;


void *operator new(size_t size)
{
    s_Allocations++;
    return malloc(size);
}

TEST_CASE("Bucket Sort integers") {
    std::vector<int> input = {97, 3, 100 ,2, -1005, 111, 1000 -3, -1000};
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());
    std::vector<int> result = bucketSort(input);
   
    REQUIRE(result == expected);
}

TEST_CASE("Bucket Sort floats") {
    
    std::vector<double> input = {97.1, 3.3, 100.1 ,2.1, -1000.0, 111, 1000, -3.3, 3.2, -1022.0, -1000001, -2.0, 132.0};
    std::vector<double> expected = input;
    std::sort(expected.begin(), expected.end());
    std::vector<double> result = bucketSort(input);

    REQUIRE(result == expected);
    BENCHMARK_ADVANCED("Bucket Sort floats") {
        return bucketSort(input);
    };

    std::cout << "\nAllocations: " << s_Allocations << std::endl;
}


// Baseline test 
// Bucket Sort floats
// -------------------------------------------------------------------------------
// /Users/stanislav/Github/HU-AI-year2/HPP/HPP-bucket-Sort/src/test.cpp:21
// ...............................................................................

// benchmark name                       samples       iterations    est run time
//                                      mean          low mean      high mean
//                                      std dev       low std dev   high std dev
// -------------------------------------------------------------------------------
// Bucket Sort floats                             100             1     5.5786 ms 
//                                         56.0088 us    55.8409 us    56.3296 us 
//                                          1.1434 us     663.79 ns    1.83543 us 

TEST_CASE("Bucket Sort Large ints")
{
    s_Allocations = 0;
    std::vector<int> ns = { 10, 100, 1000, 10000, 100000};
    std::vector<std::vector<int>> vecs;
    std::vector<std::vector<int>> results;

    for (int n : ns) {
        // Generate a random vector to sort
        std::random_device rnd_device;
        std::mt19937 mersenne_engine {rnd_device()};
        std::uniform_int_distribution<int> dist {1, 1000};
        auto gen = [&dist, &mersenne_engine]() {
            return dist(mersenne_engine);
        };
        std::vector<int> vec(n);
        generate(std::begin(vec), std::end(vec), gen);

        std::string name = "Bucket Sort " + std::to_string(n);

        BENCHMARK_ADVANCED(name.c_str()) {
            return bucketSort(vec);
        };

        vecs.emplace_back(vec); 
        results.emplace_back(bucketSort(vec));
    }

    for (auto& result : results) {
        CHECK(std::is_sorted(result.begin(), result.end()));
    }

    std::cout << "\nAllocations: " << s_Allocations << std::endl;
}

TEST_CASE("Bucket Sort Large floats")
{
    s_Allocations = 0;
    std::vector<int> ns = { 10, 100, 1000, 10000, 100000};
    std::vector<std::vector<float>> vecs;
    std::vector<std::vector<float>> results;

    for (int n : ns) {
        // Generate a random vector to sort
        std::random_device rnd_device;
        std::mt19937 mersenne_engine {rnd_device()};
        std::uniform_real_distribution<float> dist {1, 1000};
        auto gen = [&dist, &mersenne_engine]() {
            return dist(mersenne_engine);
        };
        std::vector<float> vec(n);
        generate(std::begin(vec), std::end(vec), gen);

        std::string name = "Bucket Sort " + std::to_string(n);

        BENCHMARK_ADVANCED(name.c_str()) {
            return bucketSort(vec);
        };

        vecs.emplace_back(vec); 
        results.emplace_back(bucketSort(vec));
    }

    for (auto& result : results) {
       CHECK(std::is_sorted(result.begin(), result.end()));
    }

    std::cout << "\nAllocations: " << s_Allocations << std::endl;
}