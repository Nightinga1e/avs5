#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

clock_t start, stop;
int *Y,**X,*R,n,m,check;
pthread_mutex_t mutex;

void* vec_mat(void *arg){
  int fl = 0;
  	srand(time(0));
	int num = *(int*) arg;
	int start = num * (n/m);
	int end = (num+1)*(n/m);
	//	printf(" Thread # %ld \n", num);
	//	printf(" start = %d , end = %d \n",start,end);
	pthread_mutex_lock(&mutex);
	for (int i = start; i<end;i++){
	  //	  printf("test %d \n", i);
	  Y[i] = rand()%10;
	  R[i] = 0;
	  for (int j = 0; j<n; j++){
	    X[i][j] = rand()%10;
	  }
	}
	pthread_mutex_unlock(&mutex);
	check++;
	while(fl==0){
	  if(check==m){
	    pthread_mutex_lock(&mutex);
	    for (int i = start; i<end;i++)
		for(int j =0; j<n; j++){
		  R[i] += X[i][j] * Y[j]; 
		}
	    pthread_mutex_unlock(&mutex);
	    fl=1;
	  }
	}
//	printf("\n\n");
	return NULL;
}

int main(){
  check = 0;
	int status,status_addr;
	pthread_t *thread;

	printf("\n Enter matrix/vector size: \n");
	scanf("%lld", &n);
	printf("\n Enter number of threads: \n");
	scanf("%lld", &m);
	Y = (int*)malloc(n*sizeof(int));
	thread = (pthread_t*)malloc(m*sizeof(pthread_t));
	X = (int**)malloc(n*sizeof(int*));
	R = (int*)malloc(n*sizeof(int));
	for(int i = 0; i<n; i++){
		X[i] = (int*)malloc(n*sizeof(int));
	}
	/*
	for(int i = 0; i<m; i++){
		thread[i] = 0;
		threadfill[i] = 0;
		}*/

start = clock();
	for (int num=0; num<m; num++){
		int *tid;
		tid = (int *) malloc(sizeof(int));
		*tid = num;
		pthread_create(&thread[num], NULL, vec_mat, (void *) tid);
	}

	for (int num=0; num<m; num++){
		pthread_join(thread[num], NULL);
	}
stop = clock();

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
   

for (long int i =0; i<n; i++){
		printf("%lld ", R[i]);
	}
	printf("\n\n");
*/

	double timeresult_clock = (double)(stop-start)/(CLOCKS_PER_SEC*m);
	printf("\n\n timeresult = %6.10lf \n", timeresult_clock);
	pthread_mutex_destroy(&mutex);
	return 0;
}
