#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

int buff[1001];
int position=0,np,pc,nc,cc;
sem_t mutex;
sem_t full;

void *producer(void *numb)
{
    int index=*(int*)numb;
    int productnum,i;
    for(i=0;i<pc;i++){
        productnum=rand()%1000;
        sem_wait(&mutex);
        buff[position]=productnum;
        position++;
        printf("Producer %d produced item %d\n",index,productnum);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *numb)
{
    int index=*(int*)numb;
    int productnum,i;
    for(i=0;i<cc;i++){
        sem_wait(&full);
        sem_wait(&mutex);
        position--;
        productnum=buff[position];
        printf("Consumer %d consumes item %d\n",index,productnum);
        sem_post(&mutex);
    }
}

int main(int argc, char* argv[]){
    np=atoi(argv[2]);
    pc=atoi(argv[4]);
    nc=atoi(argv[6]);
    cc=atoi(argv[8]);

    //creating semaphores
    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    
    pthread_t prod[np],cons[nc];
    
    int a[np],b[nc];
    for(int i=0;i<np;i++){
        a[i]=i+1;
    }
    for(int i=0;i<nc;i++){
        b[i]=i+1;
    }

    for(int i=0;i<np;i++) {
        pthread_create(&prod[i],NULL,(void *)producer,&a[i]);
    }
    for(int i=0;i<nc;i++) {
        pthread_create(&cons[i],NULL,(void *)consumer,&b[i]);
    }
    for(int i=0;i<np;i++) {
        pthread_join(prod[i], NULL);
    }
    for(int i=0;i<nc;i++) {
        pthread_join(cons[i], NULL);
    }
}