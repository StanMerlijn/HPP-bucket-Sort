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
int nDigits(T& number);

/**
 * @brief Calculates the number of passes required to sort the input vector.
 *
 * This function determines the number of passes required to sort the input vector
 * by finding the maximum element and calculating the number of digits in that element.
 *
 * @tparam T The type of elements in the vector.
 * @param input The vector of elements to be sorted.
 * @return int The number of passes required to sort the vector.
 */
template<typename T>
int calculatePasses(const std::vector<T>& input);

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
std::vector<T> gatheringPass(const std::vector<std::vector<T>>& input);

/**
 * @brief Distributes T into buckets based on the digit at position i.
 * 
 * For each T in the input vector, this function extracts the digit at the
 * specified position and places the number into the corresponding bucket.
 *
 * @param input A reference to the vector of T to be sorted.
 * @param buckets A reference to the vector of buckets (vectors) that will receive the numbers.
 * @param i The current digit position (starting from the least significant digit).
 */
template<typename T>
void distributePass(std::vector<T>& input, std::vector<std::vector<T>>& buckets, int i);



/**
 * @brief Performs the distribution and gathering passes for the bucket sort algorithm.
 *
 * This function performs the distribution and gathering passes for the bucket sort
 * algorithm. It distributes the numbers into buckets based on the current digit
 * position and then gathers the numbers back into a single vector.
 *
 * @tparam T The type of elements in the vector.
 * @param input A reference to the vector of elements to be sorted.
 * @param buckets A reference to the vector of buckets used for sorting.
 * @param passes The number of passes to perform (equal to the number of digits).
 * @return std::vector<T> The sorted vector.
 */
template<typename T>
std::vector<T> bucketSortSteps(std::vector<T>& input, std::vector<std::vector<T>>& buckets, int passes);

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
std::vector<T> bucketSort(std::vector<T>& input);