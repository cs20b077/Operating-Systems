#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

int N;
int timetotal = 0;

#define THINKING 2
#define EATING 0

sem_t chopstick[100];
sem_t mutex;
int state_of_phil[100];

void* philosopher(void* arg)
{
    int np = *(int*)arg;
    int i = 1;
    int eat = 5;
    while(eat != 0)
    {
        if(state_of_phil[np] == THINKING)
        {
            printf("< %d > Philosopher %d is thinking\n",timetotal,np+1);
            int think_t = rand()%50 + 50;
            timetotal = timetotal + think_t;
            state_of_phil[np] = EATING;      
        }
    else if(state_of_phil[np] == EATING)
    {   
        sem_wait(&chopstick[np]);
        int value;
        int flag = 0;
        sem_getvalue(&chopstick[(np+1)%N],&value);
        if(value == 0) {
            flag = 1;
            sem_post(&chopstick[np]);
            state_of_phil[np] = THINKING;
            continue;
        }
        else sem_wait(&chopstick[(np+1)%N]);
            printf("< %d > Philosopher %d is eating - state_of_phil - %d\n",timetotal,np+1,i);
            i++;
            timetotal = timetotal + 100;
            state_of_phil[np] = THINKING;
            eat--;
        if(flag == 0)
        {
            sem_post(&chopstick[np]);
            sem_post(&chopstick[(np+1)%N]);
        }
    }
    }
}
int main(int argc,char* argv[])
{
    N = atoi(argv[1]);
    for(int i=0;i<N;i++)
    {
        state_of_phil[i] = THINKING;
        sem_init(&chopstick[i],0,1);
    }
    sem_init(&mutex,0,1);

    pthread_t phil[N];
    for(int i=0;i<N;i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&phil[i],NULL,philosopher,arg);
    }
    for(int i=0;i<N;i++)
    {
        pthread_join(phil[i],NULL);
    }
    return 0;
}