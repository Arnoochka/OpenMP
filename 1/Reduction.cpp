#include <iostream>
#include <omp.h>
#include <vector>
#include <limits>
#include <random>
#include "init.h"

int main(int argc, char* argv[]) {
    std::vector<int> vec(NUM);
    initVector(vec);

    int min_val, max_val;
    double start = omp_get_wtime();

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < min_val) min_val = vec[i];
        if (vec[i] > max_val) max_val = vec[i];
    }
    double end = omp_get_wtime();

    if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            std::cout << "min: " << min_val << std::endl;
            std::cout << "max: " << max_val << std::endl;
            break;
        
        case 2:
            std::cout << "[";
            for (int i = 0; i<NUM - 1; ++i) {
                std::cout << vec[i] << ", ";
            }
            std::cout << vec[NUM - 1] << "]" << std::endl;

            std::cout << "min: " << min_val << std::endl;
            std::cout << "max: " << max_val << std::endl;
            break;
        default:
            break;
        }
    }
    std::cout << "time: " << end - start << std::endl;
    return 0;
}
