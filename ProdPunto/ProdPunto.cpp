#include <iostream>
#include <pthread.h>
#include <omp.h>
#include <chrono>

using namespace std;

#define SIZE 10

int ProdP(int a[], int b[]){

    int res = 0;

    for (int i = 0; i < SIZE ; i++)
    {
        res += a[i] * b[i];
    }

    return res;

}

int ProdPomp(int a[], int b[]){

    int res = 0;
    int i = 0; int chunk = 1000;
    omp_set_num_threads(6);
    #pragma omp parallel for default(shared) private(i) schedule(static,chunk) reduction(+:res)    
    for ( i = 0; i < SIZE ; i++)
    {
        res += a[i] * b[i];
    }

    return res;
}

void fillVector(int * v, int num){

    for (int i = 0; i < SIZE; i++){
        v[i] = num;
    }    
}

int main(){

    int a[SIZE];
    int b[SIZE];

    fillVector(a, 1);
    fillVector(b, 2);

    auto startTime = chrono::high_resolution_clock::now();
    //int c = ProdP(a,b);
    int c = ProdPomp(a,b);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<float, std::milli> duration_ms = endTime - startTime;

    printf("Tiempo transcurrido:  %f ms \n", duration_ms.count());

    printf("%d\n", c);

    return 0;
}