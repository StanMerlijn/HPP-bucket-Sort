#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <cstdint>
#include <math.h>

/**
 * @brief Calculates the number of digits in a given int.
 * 
 * This function computes the number of digits in number by taking the logarithm
 * base 10 of the value. If the number is 0, it returns 1.
 *
 * @tparam T Numerical type that can be used with std::log10.
 * @param number The number to calculate the digit count for.
 * @return int The number of digits in the number.
 */
template<typename T>
int nDigits(T& number) 
{
    if (number == 0)
        return 1;
    return int(std::log10(number) + 1);
}

/**
 * @brief Flattens a vector of vectors into a single vector.
 *
 * This function concatenates all the elements of a vector of vectors into one vector.
 *
 * @tparam T The type of elements stored in the vectors.
 * @param input The vector of vectors to flatten.
 * @return std::vector<T> A single vector containing all the elements.
 */
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

/**
 * @brief Distributes integers into buckets based on the digit at position i.
 * 
 * For each integer in the input vector, this function extracts the digit at the
 * specified position and places the number into the corresponding bucket.
 *
 * @param input A reference to the vector of integers to be sorted.
 * @param buckets A reference to the vector of buckets (vectors) that will receive the numbers.
 * @param i The current digit position (starting from the least significant digit).
 */
void gatheringPassInt(std::vector<int>& input, std::vector<std::vector<int>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = input[j];
        int digit = (num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

/**
 * @brief Distributes floats into buckets based on the digit at position i.
 * 
 * For each float in the input vector, the function casts the value to int, extracts
 * the digit at the specified position, and places it into the corresponding bucket.
 *
 * @param input A reference to the vector of floats to be sorted.
 * @param buckets A reference to the vector of buckets (vectors) that will receive the numbers.
 * @param i The current digit position (starting from the least significant digit).
 */
void gatheringPassFloat(std::vector<float>& input, std::vector<std::vector<float>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = static_cast<int>(input[j]);
        int digit = int(num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

/**
 * @brief Sorts an input vector using the bucket sort algorithm.
 *
 * This function implements a bucket sort algorithm that handles both integral
 * and floating point types. For integral types, it uses the number of digits in
 * the maximum element to determine the pass count. For floating point numbers,
 * it scales the values up, performs the sort, and then scales them back down.
 * Scaling the numbers up ensures that the decimal are used when sorting, When casted to int.
 *
 * @tparam T The type of elements in the vector. Supported types include integers and floats.
 * @param input The vector of elements to be sorted.
 * @return std::vector<T> The sorted vector.
 */
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