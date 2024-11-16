#include <iostream>
#include <omp.h>
#include <vector>
#include <limits>
#include <random>
#include "init.h"

int main(int argc, char* argv[]) {
    std::vector<int> vec_1 = initVector();
    std::vector<int> vec_2 = initVector();

    long long result = 0;

    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < NUM; ++i){
        result += vec_1[i] * vec_2[i];
    }
    double end = omp_get_wtime();

    if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            std::cout << result << std::endl;
            break;
        
        case 2:
            std::cout << "[";
            for (int i = 0; i<NUM - 1; ++i) {
                std::cout << vec_1[i] << ", ";
            }
            std::cout << vec_1[NUM - 1] << "]" << std::endl;

            std::cout << "[";
            for (int i = 0; i<NUM - 1; ++i) {
                std::cout << vec_2[i] << ", ";
            }
            std::cout << vec_2[NUM - 1] << "]" << std::endl;

            std::cout << result << std::endl;
            break;
        default:
            break;
        }
    }
    std::cout << "time: " << end - start << std::endl;

    return 0;
}
