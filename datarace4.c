#include<pthread.h>
#include<stdio.h>

int k=0;

void thread1(void){
    int i;
    for(i=0;i<10;i++){
        if(k > 5){
            k++;
            printf("thread2 %d\n",k);
            printf("1\n");
        }
        sleep(1);
    }
}

void thread2(void){
    int i;
    for(i=0;i<10;i++){
        if(k < 5){
            k++;
            printf("thread3 %d\n",k);
            printf("1\n");
        }
	sleep(1);
    }
}

int main(void){
    pthread_t id1,id2;
    int i;
    pthread_create(&id1,NULL,(void *) thread1,NULL);
    pthread_create(&id2,NULL,(void *) thread2,NULL);
    pthread_join(id2,NULL);
    pthread_join(id1,NULL);
        for(i=0;i<10;i++){
            k++;
            printf("thread1 %d\n",k);
            printf("0\n");
	    sleep(1);
        }
    return 0;
}
