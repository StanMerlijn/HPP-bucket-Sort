#include "header/bucketSort.hpp"

template<typename T>
int nDigits(T& number) 
{
    if (number == 0)
        return 1;
    return int(std::log10(number) + 1);
}

template<typename T>
int calculatePasses(const std::vector<T>& input)
{
    T max = *std::max_element(input.begin(), input.end());

    if constexpr (std::is_floating_point_v<T>) {
        max = static_cast<int>(max);
    }
    return nDigits(max);
}

template<typename T>
std::vector<T> gatheringPass(const std::vector<std::vector<T>>& input)
{       
    // Flatten the buckets
    std::vector<T> output;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++){
            output.emplace_back(input[i][j]);
        }
    }
   return output;
}

void distributePassInt(std::vector<int>& input, std::vector<std::vector<int>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = input[j];
        int digit = (num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

void distributePassFloat(std::vector<float>& input, std::vector<std::vector<float>>& buckets, int i)
{
    for (int j = 0; j < input.size(); j++) {
        int num = static_cast<int>(input[j]);
        int digit = int(num / int(std::pow(10, i))) % 10;
        buckets[digit].emplace_back(num);
    }
}

template<typename T>
std::vector<T> bucketSortSteps(std::vector<T>& input, std::vector<std::vector<T>> buckets, int passes)
{
    // 3. Loop through the digits
    for (int i = 0; i < passes; i++) {
        // 1. Distribution pass
        if constexpr (std::is_integral_v<T>) 
            distributePassInt(input, buckets, i);
        else if constexpr (std::is_floating_point_v<T>)
            distributePassFloat(input, buckets, i);
        
        // 2. Gathering pass: flatten the buckets
        input = gatheringPass(buckets);

        // Clear the buckets
        for (int j = 0; j < 10; j++) {
            buckets[j].clear();
        }
    }
    return input;
}

template<typename T>
std::vector<T> bucketSort(std::vector<T> input) 
{   
    if (input.empty()) {
        return input;
    };

    const float scaleFactor = 1000.0f;

    if constexpr (std::is_integral_v<T>) {
        std::vector<T> negatives, nonNegatives;
        for (auto num : input) {
            if (num < 0) {
                // Store the absolute value for sorting the negatives
                negatives.push_back(-num);
            } else {
                nonNegatives.push_back(num);
            }
        }

        // Create the buckets for the numbers
        std::vector<std::vector<T>> buckets(10, std::vector<T>(0));

        // Bucket sort the negative numbers
        if (!negatives.empty()) {
            bucketSortSteps(negatives, buckets, calculatePasses(negatives));
        }
        
        // Bucket sort the non-negative numbers
        if (!nonNegatives.empty()) {
            bucketSortSteps(nonNegatives, buckets, calculatePasses(nonNegatives));
        }

        // Reverse the negative numbers
        std::reverse(negatives.begin(), negatives.end());
        for (int i = 0; i < negatives.size(); i++) {
            negatives[i] = -negatives[i];
        }
        
        // Concatenate the negative and non-negative numbers
        negatives.insert(negatives.end(), nonNegatives.begin(), nonNegatives.end());
        return negatives;        

    } else if constexpr (std::is_floating_point_v<T>) {
        std::vector<T> negatives, nonNegatives;
        for (auto num : input) {
            if (num < 0) {
                negatives.push_back(-num * scaleFactor);
            } else {
                nonNegatives.push_back(num * scaleFactor);
            }
        }

        // Create the buckets for the numbers
        std::vector<std::vector<T>> buckets(10, std::vector<T>(0));

        // Bucket sort the negative numbers
        if (!negatives.empty()) {
            bucketSortSteps(negatives, buckets, calculatePasses(negatives));
        }
        
        // Bucket sort the non-negative numbers
        if (!nonNegatives.empty()) {
            bucketSortSteps(nonNegatives, buckets, calculatePasses(nonNegatives));
        }

        // Reverse the negative numbers
        std::reverse(negatives.begin(), negatives.end());
        for (int i = 0; i < negatives.size(); i++) {
            negatives[i] = -negatives[i];
        }

        // Concatenate the negative and non-negative numbers
        negatives.insert(negatives.end(), nonNegatives.begin(), nonNegatives.end());

        // Divide each float by scaleFactor
        for (int i = 0; i < negatives.size(); i++) {
            negatives[i] = negatives[i] / scaleFactor;
        }
        return negatives;  
    }

    return input;
}


// Explicit instantiation of the template
template std::vector<int> bucketSort<int>(std::vector<int> input);
template std::vector<float> bucketSort<float>(std::vector<float> input);