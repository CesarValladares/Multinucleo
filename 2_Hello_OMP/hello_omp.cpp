// To enable openmp support: https://msdn.microsoft.com/en-us/library/fw509c3b.aspx

#include <iostream>
#include <omp.h>

using namespace std;

void allThreads()
{
	int threadID, totalThreads;

	// Openmp pragma indicates that the following block is going to be parallel, and that 
	// the threadID variable is private in this block
	#pragma omp parallel private(threadID) //num_threads(4)
	{
		threadID = omp_get_thread_num();
		cout << "Hello world from thread: " << (int)threadID << endl;

		if (threadID == 0)
		{
			cout << "Master thread" << endl;
			totalThreads = omp_get_num_threads();
			cout << "Total threads: " << totalThreads << endl;
		}

	}
}

int main()
{
	// omp_set_num_threads(4);
	allThreads();
	return 0;
}
