// http://www.easy-math.net/area-of-a-circle-and-derivation-of-pi/

#include <iostream>
#include <cmath>
#include <chrono>
#include <iomanip> 
#include <omp.h>

using namespace std;

int num_rects = 1000000;

void calculate_pi()
{
    float radius = 1.0;
    double sum = 0.0, width = radius / num_rects;

    int i = 0;
    #pragma omp parallel for private(i) reduction(+:sum)
    for(i = 0; i<num_rects; i++)
    {
        sum += width * sqrt(1 - ((i * width) * (i * width)));
    }

    cout << "Pi: " << 4 * sum << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    calculate_pi();
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<float, std::milli> duration_ms = end - start;
    chrono::duration<float> duration_sec = end-start;
    auto duration_int_ms = chrono::duration_cast<chrono::milliseconds>(end-start);

    cout.precision(20);
    // cout << setprecision(20);

    cout << "Elapsed in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << endl;
    cout << "Elapsed in microseconds: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << endl;
    cout << "Elapsed in milliseconds: " << duration_ms.count() << endl;
    cout << "Elapsed in milliseconds: " << duration_int_ms.count() << endl;
    cout << "Elapsed in seconds: " << chrono::duration_cast<chrono::seconds>(end-start).count() << endl;
    cout << "Elapsed in seconds: " << duration_sec.count() << endl;
}