/*************************************************************************
    > File Name: no_mutex.c
    > Author: yjw
    > Mail: 617938460@qq.com
    > Created Time: 2018年11月19日 16时22分
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sharedi = 0;

void increse_num1(void);
void increse_num2(void);
void increse_num3(void);

int main(){
    int ret;
    pthread_t thrd1, thrd2, thrd3;

    ret = pthread_create(&thrd1, NULL, (void *)increse_num1, NULL);
    ret = pthread_create(&thrd2, NULL, (void *)increse_num2, NULL);
    ret = pthread_create(&thrd3, NULL, (void *)increse_num3, NULL);

    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);

    printf("sharedi = %d\n", sharedi);

    return 0;

}

void increse_num1(void) {
    long i,tmp;
    int sharedi = 0;
    for(i=0; i<=10; i++) {
	sleep(1);        
	sharedi++;
	printf("1\n");
    }
}

void increse_num2(void) {
    long i,tmp;
    int sharedi = 0;
    for(i=0; i<=10; i++) {
	sleep(1);  
	sharedi++;      
    }
}

void increse_num3(void) {
    long i,tmp;
    int a,c=0;
    int sharedi = 0;
    for(i=0; i<=10; i++) {
	sleep(1);        
	a = sharedi;
	printf("3\n");
    }
}
