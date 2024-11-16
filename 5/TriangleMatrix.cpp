#include <iostream>
#include <omp.h>
#include <vector>
#include <limits>
#include "init.h"

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> matrix = initTapeMatrixWithSafeMemory();

    // std::vector<int> min_vals(NUM, MAX);
    int min_val = MAX;
    int max_val = MIN;
    double start = omp_get_wtime();
    #pragma omp parallel for firstprivate(min_val) reduction(max:max_val)
    for (int i = 0; i < NUM; ++i){
        #pragma omp parallel for reduction(min:min_val)
        for (int j=0; j < NUM; ++j){
            if (min_val > matrix[i][j]) min_val = matrix[i][j];
        }
        if (min_val > max_val) max_val = min_val; 
    }
    double end = omp_get_wtime();

    if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            std::cout << "max: " << max_val << std::endl; 
            break;
        
        case 2:
            for (int i = 0; i < NUM; ++i){
                std::cout << "[";
                for (int j = 0; j<matrix[i].size() - 1; ++j) {
                    std::cout << matrix[i][j] << ", ";
                }
                std::cout << matrix[i][matrix[i].size() - 1] << "]" << std::endl;
            }
            std::cout << "max: " << max_val << std::endl; 
            break;
        default:
            break;
        }
    }
    std::cout << "time: " << end - start << std::endl;
}