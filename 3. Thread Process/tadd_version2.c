#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int sum1=0;
static int sum2=0;

void *Tsum(void *arg){
        int num= *(int *)arg;
        int start, end;
	if(num==0){
		for(int i=1; i<=50; i++)
			sum1+=i;
	}
	else{
		for(int i=51; i<=100; i++)
			sum2+=i;
	}
        pthread_exit(NULL);

}	

int main(){
	pthread_t tid[2];
	int num[2]={0,50};
	int sum[2];
	
	// 1~50까지 합을 처리하는 Thread와 51~100까지 합을 처리하는 Thread 두 개 crate
	for(int i=0; i<2; i++){
		if(pthread_create(&tid[i], NULL,Tsum,(void *)&num[i] )<0){
			perror("ptherad_create");
			exit(1);
		}
	}
	
	// 각각의 쓰레드 종료를 기다리고 pthread_exit()를 통해 return 값을 받는다.
	for(int i=0; i<2; i++){
		if(pthread_join(tid[i],NULL)<0){
			perror("pthread_join");
			exit(1);
		}
	}
	printf("Result : %d  %d\n",sum1,sum2);
	printf("Sum : %d\n",sum1+sum2);
	return 0;
}
