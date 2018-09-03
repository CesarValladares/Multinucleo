#include <cstdio>
#include "vector3d.h"

#include <chrono>
#include <iomanip> 

#include <string>

using namespace std;

void vectorAdd(vector3d<int> *a, vector3d<int> *b, vector3d<int> *c, int size)
{
    int i = 0;
    for(i = 0; i<size; i++)
    {
        c[i] = a[i] + b[i];
    }
}

int main(int argc, char const *argv[])
{
    vector3d<int> *a, *b, *c;

    int size = 0;
    
    if(argc < 2)
        size = 1000;
    else
        size = stoi(argv[1]);

    a = new vector3d<int>[size]();
    b = new vector3d<int>[size]();
    c = new vector3d<int>[size]();

    for(int i = 0; i<size; i++)
    {
        a[i] = vector3d<int>(1,2,3);
        b[i] = vector3d<int>(1,2,3);
    }
    
    auto start = chrono::high_resolution_clock::now();
    vectorAdd(a, b, c, size);
    // vectorAddThread(a, b, c, size);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<float, std::milli> duration_ms = end - start;
    printf("time seq (ms): %f\n", duration_ms.count());

    vector3d<int> sum;

    for(int i=0; i<size; i++)
        sum += c[i];

    printf("final result: %f, %f, %f\n", sum.x / (float)size, sum.y / (float)size, sum.z / (float)size);
    printf("final result: %d, %d, %d\n", sum.x, sum.y, sum.z);
    
    return 0;
}
