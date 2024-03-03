#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>

typedef struct bound{
int start;
int end;
long long res
} bound;

void* sum_runner(void* arg)
{
	long long sum = 0;
    bound *limit_ptr = (bound *) arg;
	long long start = limit_ptr->start;
    long long end = limit_ptr->end;
	for (long long i = start; i <= end; i++) {
		sum += i;
	}
    limit_ptr->res=sum;
	pthread_exit(0);
}

int main(int argc, char **argv)
{
clock_t start, end;
 double cpu_time_used;

	if (argc < 2) {
		printf("Usage: %s <num>\n", argv[0]);
		exit(-1);
	}

	long long limit = atoll(argv[1]);
   bound limits[2];
limits[0].start=0;
limits[1].start=limit/2+1;
limits[0].end=limit/2;
limits[1].end=limit;
	// Thread ID:
start = clock();
	pthread_t tid[2];

	// Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid[0], &attr, sum_runner, &limits[0]);
    pthread_create(&tid[1], &attr, sum_runner, &limits[1]);

	
	pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

	printf("Sum is %lld\n", limits[0].res+limits[1].res);
end = clock();

printf("time taken %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

}
