#include <stdio.h>
#include <pthread.h>
#define THREAD_NUM 16

int k=0;

void *thread_func1(void *arg){
    for(int i=0;i<10;i++){
        sleep(1);    
        printf("Thread1 k = %d\n", k++);
    }
    return (void*)0;
}

void *thread_func2(void *arg){
    for(int i=0;i<10;i++)
        printf("Thread2 k = %d\n", k++);
    return (void*)0;
}

void *thread_func3(void *arg){
    for(int i=0;i<10;i++)
        printf("Thread3 k = %d\n", k++);
    return (void*)0;
}

int main(int argc, const char *argv[]) {
    pthread_t a1,a2,a3;
    int i=0;
        pthread_create(&a1, NULL, thread_func1, (void*)(&i));
        pthread_create(&a2, NULL, thread_func2, (void*)(&i));
	pthread_create(&a3, NULL, thread_func3, (void*)(&i));
	pthread_join(a1, NULL);
	pthread_join(a2, NULL);
        pthread_join(a3, NULL);
    return 0;
}
