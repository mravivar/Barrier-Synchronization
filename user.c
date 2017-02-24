/*
User program for barrier synchronization.
Below are the syscall numbers:
1. barrier_init - syscall 351
2. barrier_wait - syscall 352
3. barrier_destroy - syscall 353
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;

int fd1;
int ret;
unsigned long int sleep_time = 0;

// set1
int n1=5; // number of threads in childprocess1 part1
int count1=0;
int it1 = 0;
int iteration_cnt1 = 100;
int countandbarrierid1=0;

// set2
int n2=20; // number of threads in childprocess1 part2
int count2=0;
int it2 = 0;
int iteration_cnt2 = 100;
int countandbarrierid2=0;

// set3
int n3=5; // number of threads in childprocess2 part1
int count3=0;
int it3 = 0;
int iteration_cnt3 = 100;
int countandbarrierid3 = 0;

// set4
int n4=20; // number of threads in childprocess2 part2
int count4=0;
int it4 = 0;
int iteration_cnt4 = 100;
int countandbarrierid4=0;

void function_1(void)
{
    while (it1 < iteration_cnt1) {
        pthread_mutex_lock(&lock1);
        pthread_t t_id = pthread_self();
        printf("thread id: %ld; inside function_1; iteration %d\n", t_id, it1);
        
        count1++;
        if (count1 == n1) {
            it1++;
            count1 = 0;
        } 
        pthread_mutex_unlock(&lock1);
        
   ret = syscall(352, countandbarrierid1); // barrier wait
     if(ret < 0){
        printf("write function failed..\n");
    }
    usleep(sleep_time);
    }
}

void function_2(void)
{   
   while (it2 < iteration_cnt2) {
        pthread_mutex_lock(&lock2);
        pthread_t t_id = pthread_self();
        printf("thread id: %ld; inside function_2; iteration %d\n", t_id, it2);
        
        count2++;
        if (count2 == n2) {
            it2++;
            count2 = 0;
        } 
        pthread_mutex_unlock(&lock2);
        
        ret = syscall(352, countandbarrierid2); // barrier wait
     if(ret < 0){
        printf("write function failed..\n");
    }
    usleep(sleep_time);    
    }
} 

void function_3(void)
{
    while (it3 < iteration_cnt3) {
        pthread_mutex_lock(&lock3);
        pthread_t t_id = pthread_self();
        printf("thread id: %ld; inside function_3; iteration %d\n", t_id, it3);
        
        count3++;
        if (count3 == n3) {
            it3++;
            count3 = 0;
        } 
        pthread_mutex_unlock(&lock3);
        
    ret = syscall(352, countandbarrierid3); // barrier wait
     if(ret < 0){
        printf("write function failed..\n");
    }
   usleep(sleep_time);
      
    }
}

void function_4(void)
{   
   while (it4 < iteration_cnt4) {
        pthread_mutex_lock(&lock4);
        pthread_t t_id = pthread_self();
        printf("thread id: %ld; inside function_4; iteration %d\n", t_id, it4);
        
        count4++;
        if (count4 == n4) {
            it4++;
            count4 = 0;
        } 
        pthread_mutex_unlock(&lock4);
        
    ret = syscall(352, countandbarrierid4); // barrier wait
     if(ret < 0){
        printf("write function failed..\n");
    }
   usleep(sleep_time);
      
    }
} 

void  ChildProcess_1(void)
{
    pthread_mutex_init(&lock1, NULL);
    int *arg=NULL;
    printf("child 1 ....\n");

    // create 5 threads and control them using barrier1
    void *func1 = function_1;
    pthread_t thread_id_set1[n1];

    countandbarrierid1 = n1;
    printf("1.1 count: %d\n",countandbarrierid1);

    // barrier init
    ret = syscall(351, n1, &countandbarrierid1);
    if(ret < 0) {
        printf(" 1.1 Read function failed\n");
    }
    printf("1.1 barrierid: %d\n",countandbarrierid1);

    // create 5 threads and control them using barrier1
    int i;
    for(i=0; i<n1;i++) {
        pthread_create(&thread_id_set1[i], NULL, func1, arg);
        printf("1.1 thread created: %d\n",i);
    }

    // wait till 5 threads complete its execution
    for(i=0; i<n1; i++) {
        pthread_join(thread_id_set1[i],NULL);
        printf("1.1 thread joined: %d\n",i);
    }

    printf("1.1 thread destroy..");
    pthread_mutex_destroy(&lock1);
    
    // barrier destroy
    ret = syscall(353, countandbarrierid1);
    if(ret < 0) {
        printf(" 1.1 Read function failed\n");
    }

    pthread_mutex_init(&lock2, NULL);
    void *func2 = function_2;
    pthread_t thread_id_set2[n2];

    countandbarrierid2 = n2;
    printf("1.2.count: %d\n",countandbarrierid2);
    
    // barrier init
    ret = syscall(351, n2, &countandbarrierid2);
    if(ret < 0) {
        printf("1.2. Read function failed\n");
    }
    printf("1.barrierid: %d\n",countandbarrierid2);

    // create 20 threads and control them using barrier2
    for(i=0; i<n2;i++) {
        pthread_create(&thread_id_set2[i], NULL, func2, arg);
        printf("1.2. thread created: %d\n",i);

    }

    for(i=0; i<n2; i++) {
        pthread_join(thread_id_set2[i],NULL);
        printf("1.2. thread joined: %d\n",i);
    }

    printf("1.2. thread destroy..");
    pthread_mutex_destroy(&lock2);
    // barrier2 destroy
    ret = syscall(353, countandbarrierid2);
    if(ret < 0) {
        printf(" 1.2. Read function failed\n");
    }
    exit(0); // to stop child process
}

void  ChildProcess_2(void)
{
    pthread_mutex_init(&lock3, NULL);
    int *arg=NULL;
    printf("child 2 ....\n");
   
    void *func3 = function_3;
    pthread_t thread_id_set3[n3];
    countandbarrierid3 = n3;
    printf("2.1 count: %d\n",countandbarrierid3);
    
    // barrier init
    ret = syscall(351, n3, &countandbarrierid3);
    if(ret < 0) {
        printf(" 2.1. Read function failed\n");
    }
    printf("2.1. barrierid: %d\n",countandbarrierid3);

    // create 5 threads and control them using barrier
    int i;
    for(i=0; i<n3;i++) {
        pthread_create(&thread_id_set3[i], NULL, func3, arg);
        printf("2.1. thread created: %d\n",i);

    }

    for(i=0; i<n3; i++) {
        pthread_join(thread_id_set3[i],NULL);
        printf("2.1. thread joined: %d\n",i);
    }

    printf("2.1. thread destroy..");
    pthread_mutex_destroy(&lock3);
    ret = syscall(353, countandbarrierid3); //barrier destroy
    if(ret < 0) {
        printf(" 2.1. Read function failed\n");
    }

    
    pthread_mutex_init(&lock4, NULL);
    void *func4 = function_4;
    pthread_t thread_id_set4[n4];

    countandbarrierid4 = n4;
    printf("2.2. count: %d\n",countandbarrierid4);
    //barrier init
    ret = syscall(351, n4, &countandbarrierid4); 
    if(ret < 0) {
        printf("2.2. Read function failed\n");
    }
    printf("2.2. barrierid: %d\n",countandbarrierid4);

    // create 20 threads and control them using barrier
    for(i=0; i<n4;i++) {
        pthread_create(&thread_id_set4[i], NULL, func4, arg);
        printf("2.2. thread created: %d\n",i);

    }

    for(i=0; i<n4; i++) {
        pthread_join(thread_id_set4[i],NULL);
        printf("2.2. thread joined: %d\n",i);
    }

    printf("2.2. thread destroy..");
    pthread_mutex_destroy(&lock4);
    // barrier destroy
    ret = syscall(353, countandbarrierid4);
    if(ret < 0) {
        printf(" 2.2.Read function failed\n");
    }

exit(0);
}


int  main(void)
{
     pid_t   pid1, pid2, pid;
     int     status;

     printf("Enter sleep time in micro seconds..");
     scanf("%lu", &sleep_time);
     
    fd1 = open("/dev/barrier_sync", O_RDWR);
    if(fd1<0){
        printf("Fail to open device 1\n");
    }

     printf("*** Parent is about to fork process 1 ***\n");

     // fork child process 1
     if ((pid1 = fork()) < 0) {
          printf("Failed to fork process 1\n");
          exit(1);
     }
     else if (pid1 == 0) 
          ChildProcess_1();
    
    // fork child process 2
     printf("*** Parent is about to fork process 2 ***\n");
     if ((pid2 = fork()) < 0) {
          printf("Failed to fork process 2\n");
          exit(1);
     }
     else if (pid2 == 0) 
          ChildProcess_2();
   
     printf("*** Parent enters waiting status .....\n");
     
     // wait for the completion of one the processes
     pid = wait(&status);
     printf("*** Parent detects process %d was done ***\n", pid);
     
     // wait for the completion of one of the processes
     pid = wait(&status);
     printf("*** Parent detects process %d is done ***\n", pid);
     
     close(fd1);
     printf("*** Parent exits ***\n");
     
     exit(0);
}
