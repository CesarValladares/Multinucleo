#include <stdio.h>
#include <stdlib.h>
#include <math.h>

template <class T>
class vector3d
{
    public: 
        T x, y, z;

        vector3d()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        vector3d(T x_, T y_, T z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        inline vector3d& operator +=(const vector3d& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        inline vector3d& operator +(const vector3d& rhs)
        {
            *this += rhs;
            return *this;
        }

        inline vector3d& operator /=(const T& rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        inline vector3d& operator /(const T& rhs)
        {
            *this /= rhs;
            return *this;
        }

        __host__ __device__ inline void test()
        {
            int test = 0;
            test++;
        }
        
};

__global__ void vecAdd(vector3d<float> *a, vector3d<float> *b, vector3d<float> *c, int n)
{
    int id = blockIdx.x*blockDim.x+threadIdx.x;

    if (id < n)
    {
        c[id].x = a[id].x + b[id].x;
        c[id].y = a[id].y + b[id].y;
        c[id].z = a[id].z + b[id].z;

        c[id].test();
    }
}
 
int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 1000000;
    float n_f = 1000000.0f;
 		
    // Host input vectors
    vector3d<float> *h_a;
    vector3d<float> *h_b;
    
    //Host output vector
    vector3d<float> *h_c;
 
    // Device input vectors
    vector3d<float> *d_a;
    vector3d<float> *d_b;

    //Device output vector
    vector3d<float> *d_c;
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(vector3d<float>);
 
    // Allocate memory for each vector on host
    h_a = new vector3d<float>[bytes](); //(vector3d<float>*)malloc(bytes);
    h_b = new vector3d<float>[bytes](); //(vector3d<float>*)malloc(bytes);
    h_c = new vector3d<float>[bytes](); //(vector3d<float>*)malloc(bytes);
 
    // Allocate memory for each vector on GPU
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
 
    // Initialize vectors on host
    for(int i = 0; i <= n; i++ ) {
        h_a[i] = vector3d<float>(1,2,3);
        h_b[i] = vector3d<float>(1,2,3);
    }
 
    // Copy host vectors to device
    cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);
 
    int blockSize, gridSize;
 
    // Number of threads in each thread block
    blockSize = 1024;
 
    // Number of thread blocks in grid
    gridSize = (int)ceil((float)n/blockSize);
 
    // Execute the kernel
    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    // Copy array back to host
    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
 
    // Sum up vector c and print result divided by n, this should equal 1 within error
    vector3d<float> sum;
    for(int i=0; i<=n; i++)
        sum += h_c[i];

    printf("final result: %f, %f, %f\n", sum.x / n_f, sum.y / n_f, sum.z / n_f);
    printf("final result: %f, %f, %f\n", sum.x, sum.y, sum.z);
 
    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
 
    // Release host memory
    free(h_a);
    free(h_b);
    free(h_c);
 
    return 0;
}
