#include <chrono>

#include "Solvers.h"

int main() {

    uint64_t res;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    std::chrono::duration<double> elapsed_seconds;

    // Day 1
    {
        std::cout << "================== Day 1 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d1t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d1t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 2
    {
        std::cout << "================== Day 2 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d2t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d2t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t Time elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 3
    {
        std::cout << "================== Day 3 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d3t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d3t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 4
    {
        std::cout << "================== Day 4 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d4t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d4t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 5
    {
        std::cout << "================== Day 5 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d5t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d5t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 6
    {
        std::cout << "================== Day 6 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d6(80);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d6(256);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 7
    {
        std::cout << "================== Day 7 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d7t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d7t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 8
    {
        std::cout << "================== Day 8 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d8t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d8t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 9
    {
        std::cout << "================== Day 9 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d9t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d9t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 10
    {
        std::cout << "================== Day 10 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d10t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d10t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 11
    {
        std::cout << "================== Day 11 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d11t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d11t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 12
    {
        std::cout << "================== Day 12 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d12t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d12t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 13
    {
        std::cout << "================== Day 13 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d13t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d13t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << "EFJKZLBL (in outputs/day13.txt)" << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 14
    {
        std::cout << "================== Day 14 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d14(10);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d14(40);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 15
    {
        std::cout << "================== Day 15 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d15t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d15t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 16
    {
        std::cout << "================== Day 16 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d16t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d16t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 17
    {
        std::cout << "================== Day 17 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d17t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d17t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 18
    {
        std::cout << "================== Day 18 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d18t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d18t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 19
    /*
    {
        std::cout << "================== Day 19 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d19t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d19t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
     */
    // Day 20
    {
        std::cout << "================== Day 20 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d20(2);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d20(50);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }
    // Day 21
    {
        std::cout << "================== Day 21 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d21t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        /*
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d21t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
         */
    }
    // Day 22
    {
        std::cout << "================== Day 22 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d22t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        /*
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d22t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
         */
    }
    // Day 23
    {
        std::cout << "================== Day 23 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d23t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
        /*
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d23t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
         */
    }

    // Day 24
    {
        std::cout << "================== Day 24 ==================" << std::endl;
        std::cout << RED << " THESE TASKS CAN TAKE SOME TIME TO COMPUTE,\n        PLEASE WAIT PATIENTLY!"  << NC << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d24t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count() << "s"<< std::endl;
        std::cout << "Task 2:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d24t2();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count() << "s"<< std::endl;
    }
    // Day 25
    {
        std::cout << "================== Day 25 ==================" << std::endl;
        std::cout << "Task 1:" << std::endl;
        start = std::chrono::system_clock::now();
        res = Solvers::d25t1();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Result: " << GREEN << res << NC << "\t\tTime elapsed: " << elapsed_seconds.count()*1000 << "ms"<< std::endl;
    }

    return 0;
}