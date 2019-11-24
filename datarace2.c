#include<pthread.h>
#include<stdio.h>

int k=0;

void thread1(void){
    int i;
    for(i=0;i<10;i++){
        k++;
        printf("thread2 %d\n",k);
        sleep(1);
        printf("1\n");
    }
}

int main(void){
    pthread_t id1;
    int i;
    pthread_create(&id1,NULL,(void *) thread1,NULL);
    pthread_join(id1,NULL);
    for(i=0;i<10;i++){
        k++;
        printf("thread1 %d\n",k);
        sleep(1);
        printf("0\n");
    }
    return 0;
}
