#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

clock_t start, stop;
long int *Y,**X,*R,n,m;
pthread_t *thread;

void* vec_mat(void *arg){
	int num = *(int*) arg;
	printf(" Thread # %ld \n", num);

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
	Y = (long int*)malloc(n*sizeof(long int*));
	thread = (pthread_t*)malloc(m*sizeof(pthread_t));
	X = (long int**)malloc(n*sizeof(long int*));
	R = (long int*)malloc(n*sizeof(long int*));
	for( int i = 0; i<n; i++){
		X[i] = (long int*)malloc(n*sizeof(long int));
	}
	for( long int i = 0; i<m; i++){
		thread[i] = 0;
	}
	for (long int i = 0; i<n;i++){
		for (long int j = 0; j<n; j++){
			Y[i] = rand()%10;
			X[i][j] = rand()%10;
			R[i] = 0;
		}
	}


/*
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
*/


	for (int num=0; num<m; num++){
		int *tid;
		tid = (int *) malloc(sizeof(int));
		*tid = num;
		pthread_create(&thread[num], NULL, vec_mat, (void *) tid);
	}

	for (int num=0; num<m; num++){
		pthread_join(thread[num], NULL);
	}


/*
for (long int i =0; i<n; i++){
		printf("%lld ", R[i]);
	}
	printf("\n\n");
*/

//	start = clock();
//	vec_mat(X,Y,R,n,m);
//	stop = clock();

//	double timeresult_clock = (double)(stop-start)/CLOCKS_PER_SEC;
//	printf("\n\n timeresult = %6.10lf \n", timeresult_clock);
	return 0;
}
