//--------------------------------------------------------------------  
// Valgrind reports data race  
// valgrind --tool=helgrind ./datarace  
//--------------------------------------------------------------------  
      
  
#include <pthread.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
      
  
//--------------------------------------------------------------------  
// Macro definition  
//--------------------------------------------------------------------  
#define NUM	10  
      
  
//--------------------------------------------------------------------  
// Global variables  
//--------------------------------------------------------------------  
int global_value = 0;  
//--------------------------------------------------------------------  
// Function prototype  
//--------------------------------------------------------------------  
void *t1_main(void *arg);  
void *t2_main(void *arg);  
//--------------------------------------------------------------------  
// Main function  
//--------------------------------------------------------------------  
int main(int argc, char **argv){  
    pthread_t t1, t2;  
    int code;  
    code = pthread_create(&t1, NULL, t1_main, NULL);  
    if (code != 0){    
        fprintf(stderr, "Create new thread t1 failed: %s\n", strerror(code));  
        exit(1);  
    }  
    else{  
        fprintf(stdout, "New thread t1 created.\n");  
    }   
    code = pthread_create(&t2, NULL, t2_main, NULL);  
    if (code != 0){    
        fprintf(stderr, "Create new thread t2 failed: %s\n", strerror(code));  
        exit(1);  
    }  
    else{    
        fprintf(stdout, "New thread t2 created.\n");  
    }  
    pthread_join(t1, NULL);  
    pthread_join(t2, NULL);  
    pthread_exit((void *) 0);  
}  
      
  
//--------------------------------------------------------------------  
// Thread #1   
//--------------------------------------------------------------------  
void *t1_main(void *arg){  
    int i;  
    for (i = 0; i < NUM; i++){  
        global_value++;		// data race, will be reported by valgrind  
        fprintf(stdout, "[Thread #t1]global_value = %d\n", global_value);  
        sleep(1);  
    }  
    pthread_exit((void *) 0);  
}  
      
  
//--------------------------------------------------------------------  
// Thread #2   
//--------------------------------------------------------------------  
void *t2_main(void *arg){  
    int i;  
    for (i = 0; i < NUM; i++){  
        global_value += 2;		// data race, will be reported by valgrind  
        fprintf(stdout, "[Thread #t2]global_value = %d\n", global_value);  
        sleep(1);  
    }  
    pthread_exit((void *) 0);  
}  
