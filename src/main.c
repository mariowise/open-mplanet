#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _OPENMP
	#include <omp.h>
#endif

void * body(int params) {
	printf("I don't want no trouble Sir.. just doing the task no. %d!\n", params);
}

int main(int argc, char * argv[]) {

	int nthreads = 4;

	#pragma omp parallel num_threads(nthreads)
	{
		#pragma omp single 
		{
			int i;
			for(i = 0; i < 4; i++) {
				#pragma omp task
					body(i);
			}
		}
	}

	return EXIT_SUCCESS;
}