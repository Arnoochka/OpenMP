#include <omp.h>
#include <math.h>
#include <iostream>

#define n 1000000

double F(double x){
    // x^3 + 2x^2 - 5
    return std::pow(x, 3) + 2 * std::pow(x, 2) - 5;
}

int main(int argc, char* argv[]) {
    double a = -100.0, b = 100.0, h = (b - a) / n;
    double Integral = 0;
    double mean, x;
    
    double start = omp_get_wtime();
    #pragma omp parallel private(mean, x)
    {
        #pragma omp for schedule(static, 10) reduction(+:Integral)
        for (int i = 0; i < n; ++i){
            x = (a + i + 0.5) * h / 2;
            mean = F(x) * h;

            Integral += mean;
        }
    }

    double end = omp_get_wtime();

        if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            std::cout << "Integral: " << Integral << std::endl;
            break;
        
        case 2:
            std::cout << "a: " << a << std::endl;
            std::cout << "b: " << b << std::endl;
            std::cout << "n: " << n << std::endl;
            std::cout << "h: " << h << std::endl;
            std::cout << "F(x) = x^3 + 2x^2 - 5" << std::endl;
            std::cout << "Integral: " << Integral << std::endl;
            break;
        default:
            break;
        }
    }
    std::cout << "time: " << end - start << std::endl;

}