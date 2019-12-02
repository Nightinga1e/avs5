#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

clock_t start, stop;
long int *Y,**X,*R,n,m;
int fl = 0;
pthread_t *thread,*threadfill;

void* fill(void *arg){
	
	long int num = *(int*) arg;

//	printf(" Thread # %ld \n", num);
	for (long int i = num; i<n;i=i+m){
		Y[i] = rand()%10;
		R[i] = 0;
		for (long int j = 0; j<n; j++){
			X[i][j] = rand()%10;
		}
	}
	return NULL;
}

void* vec_mat(void *arg){
	long int num = *(int*) arg;
//	printf(" Thread # %ld \n", num);

	for(long int i = num; i<n; i=i+m)
		for(long int j =0; j<n; j++){
			R[i] += X[i][j] * Y[j]; 
	}

	printf("\n\n");
	return NULL;
}

int main(){
	long int status,status_addr;
	srand(time(0));
	printf("\n Enter matrix/vector size: \n");
	scanf("%lld", &n);
	printf("\n Enter number of threads: \n");
	scanf("%lld", &m);
	Y = (long int*)malloc(n*sizeof(long int));
	thread = (pthread_t*)malloc(m*sizeof(pthread_t));
	threadfill = (pthread_t*)malloc(m*sizeof(pthread_t));
	X = (long int**)malloc(n*sizeof(long int));
	R = (long int*)malloc(n*sizeof(long int));
	for( int i = 0; i<n; i++){
		X[i] = (long int*)malloc(n*sizeof(long int));
	}
	for( long int i = 0; i<m; i++){
		thread[i] = 0;
		threadfill[i] = 0;
	}

/*output
	for (long int i=0;i<n;i++){
		printf("%lld ", Y[i]);
	}
	printf("\n");
	for (long int j=0; j<n; j++){
		printf("\n");
		for(long int i=0; i<n; i++)
			printf("%lld ", X[i][j]);
	}
	printf("\n\n");
output*/ 
start = clock();
	for (long int num=0; num<m; num++){
		long int *filltid;
		filltid = (long int *) malloc(sizeof(long int));
		*filltid = num;
		pthread_create(&threadfill[num], NULL, fill, (void *) filltid);
	}
	for (long int num=0; num<m; num++){
		pthread_join(threadfill[num], NULL);
	}

	for (long int num=0; num<m; num++){
		long int *tid;
		tid = (long int *) malloc(sizeof(long int));
		*tid = num;
		pthread_create(&thread[num], NULL, vec_mat, (void *) tid);
	}

	for (long int num=0; num<m; num++){
		pthread_join(thread[num], NULL);
	}
stop = clock();
/* result
for (long int i =0; i<n; i++){
		printf("%lld ", R[i]);
	}
	printf("\n\n");
result*/

	double timeresult_clock = (double)(stop-start)/CLOCKS_PER_SEC;
	printf("\n\n timeresult = %6.10lf \n", timeresult_clock);
	return 0;
}
