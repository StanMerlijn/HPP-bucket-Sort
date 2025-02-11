#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <cstdint>
#include <math.h>

template<typename T>
int nDigits(T& number) 
{
    if (number == 0)
        return 1;
    return int(std::log10(number) + 1);
}

template<typename T>
std::vector<T> FlattenBuckets(const std::vector<std::vector<T>>& input)
{       
    std::vector<T> output;
    // Flatten the buckets
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++){
            output.emplace_back(input[i][j]);
        }
    }
   return output;
}

void gatheringPassInt(std::vector<int>& input, std::vector<std::vector<int>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = input[j];
        int digit = (num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

void gatheringPassFloat(std::vector<float>& input, std::vector<std::vector<float>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = static_cast<int>(input[j]);
        int digit = int(num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

template<typename T>
std::vector<T> bucketSort(std::vector<T> input) 
{   
    if (input.empty()) {
        return input;
    };

    if constexpr (std::is_integral_v<T>) {
        // Create the buckets for the numbers
        std::vector<std::vector<T>> buckets(10, std::vector<T>(0));

        // Find the maximum number in order to know how many digits to loop through
        T max = *std::max_element(input.begin(), input.end());

        // Loop through the digits
        for (int i = 0; i < nDigits(max); i++) {
            // Distribution pass
            gatheringPassInt(input, buckets, i);
            
            // Flatten the buckets
            input = FlattenBuckets(buckets);

            // Clear the buckets
            for (int j = 0; j < 10; j++) {
                buckets[j].clear();
            }
        }
    } else if constexpr (std::is_floating_point_v<T>) {
        // Multiply each float by 10^6 
        const float scaleFactor = 1000000.0f;
        for (int i = 0; i < input.size(); i++){
            input[i] = input[i] * scaleFactor;
        }
        // Create the buckets for the numbers
        std::vector<std::vector<T>> buckets(10, std::vector<T>(0));
        
        // Find the maximum number in order to know how many digits to loop through
        T max = *std::max_element(input.begin(), input.end());

        // Cast the float to an int to get the number of digits
        int passes = static_cast<int>(nDigits(max));

        // Loop through the digits
        for (int i = 0; i < passes; i++) {
            // Distribution pass
            // Distribution pass: place each value into a bucket based on its normalized value.
            gatheringPassFloat(input, buckets, i);
            
            // Flatten the buckets
            input = FlattenBuckets(buckets);

            // Clear the buckets
            for (int j = 0; j < 10; j++) {
                buckets[j].clear();
            }
        }

        // Divide each float by 10^6
        for (int i = 0; i < input.size(); i++) {
            input[i] = input[i] / scaleFactor;
        }
        
    }

    return input;
}