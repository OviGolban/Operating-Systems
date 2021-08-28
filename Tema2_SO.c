#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include<pthread.h>
#include<semaphore.h>

#define NR_THREADS 5
#define NR_THREADS_SECOND 42
#define NR_THREADS_THIRD 6

pthread_mutex_t lacat = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bariera;
sem_t semafor1;
sem_t semafor2;

int status1 = 1;

int count = 0;
void* threadFn(void *aux)
{   
    int id = *(int*) aux;
    pthread_mutex_lock(&lacat);
    if(id!=2){
    if(id!=4 && id!=1) {
    info(BEGIN,2,id);
    info(END,2,id);
    }
    if(id==4){
        info(BEGIN,2,4);
        info(BEGIN,2,1);
        info(END,2,1);
        info(END,2,4);
    }
    }
    pthread_mutex_unlock(&lacat);
    return NULL;
}

void* threadSecond(void *aux)
{   
    //int count=0;
    
    int id = *(int*) aux;
    
    //sem_wait(&semafor1);
    pthread_mutex_lock(&lacat);
    info(BEGIN,4,id);
    info(END,4,id);
    pthread_mutex_unlock(&lacat);
    //sem_post(&semafor1);
    return NULL;
}

void* threadSecondAux(void * aux)
{
    int id = *(int*) aux;

    pthread_mutex_lock(&lacat);
    info(BEGIN,4,6);
    info(BEGIN,4,7);
    info(BEGIN,4,8);
    info(BEGIN,4,9);
    info(BEGIN,4,10);
    info(BEGIN,4,id);
    info(END,4,id);
    info(END,4,10);
    info(END,4,9);
    info(END,4,8);
    info(END,4,7);
    info(END,4,6);
    pthread_mutex_unlock(&lacat);
    return NULL;
}

void* threadThird(void *aux){
    int id = *(int*) aux;
    pthread_mutex_lock(&lacat);
    if(id!=5 && id!=2){
    info(BEGIN,7,id);
    info(END,7,id);
    }
    pthread_mutex_unlock(&lacat);
    return NULL;

}

void* thread2(void* unused){
    pthread_mutex_lock(&lacat);
    info(BEGIN,2,2);
    info(END,2,2);
    pthread_mutex_unlock(&lacat);
    return NULL;
}

void* thread7(void *aux)
{   
    int id = *(int*) aux;
    pthread_mutex_lock(&lacat);
    info(BEGIN,7,id);
    info(END,7,id);
    pthread_mutex_unlock(&lacat);
    return NULL;
}

int main(){
    init();

    int p1, p2, p3, p5,p8,i,aux;
    pthread_t threads_ids[NR_THREADS];
    pthread_t threads_second[NR_THREADS_SECOND];
    pthread_t threads_third[NR_THREADS_THIRD];
    pthread_t auxiliar1;
    pthread_t auxiliar2;
    pthread_t auxiliar3;
    pthread_t auxiliar4;
   
    info(BEGIN, 1, 0);
    if(sem_init(&semafor1, 0 ,6) != 0) {
        perror("Could not init the semaphore");
        return -1;
    }
    if(sem_init(&semafor2, 0 ,1) != 0) {
        perror("Could not init the semaphore");
        return -1;
    }

    p1 = fork(); //creez p2
    if (p1 == 0)
    {
       info(BEGIN,2,0);

        for(i=0;i<NR_THREADS;i++){
             aux=i+1;
             pthread_create(&threads_ids[i],NULL,threadFn,&aux);
             pthread_join(threads_ids[i],NULL);
         }

       p2=fork(); //creez p4
       if(p2 == 0){
           info(BEGIN,4,0);

           for(i=0;i<5;i++){
                 aux=i+1;
                 pthread_create(&threads_second[i],NULL,threadSecond,&aux);
                 pthread_join(threads_second[i],NULL);
             }
             int un = 11;
             pthread_create(&auxiliar4,NULL,threadSecondAux,&un);
             pthread_join(auxiliar4, NULL);

            for(int i=11; i<NR_THREADS_SECOND;i++) {
                aux = i+1;
                pthread_create(&threads_second[i],NULL,threadSecond,&aux);
                pthread_join(threads_second[i],NULL);
            }
        
           p3=fork();//creez p5
           if(p3==0){
               info(BEGIN,5,0);
               p5=fork();//creez p7
               if(p5==0){
                   info(BEGIN,7,0);
                   for(i=0; i<NR_THREADS_THIRD;i++){
                       aux=i+1;
                       pthread_create(&threads_third[i],NULL,threadThird,&aux);
                       pthread_join(threads_third[i],NULL);
                   }
                   int cinci = 5;
                   int doi = 2;
                   pthread_create(&auxiliar1,NULL, thread7,&cinci);
                   pthread_join(auxiliar1, NULL);
                   pthread_create(&auxiliar2,NULL, thread2,NULL);
                   pthread_join(auxiliar2, NULL);
                   pthread_create(&auxiliar3,NULL, thread7,&doi);
                   pthread_join(auxiliar3, NULL);

                   waitpid(p2,&status1, 0);
                   p8=fork();//creez p8
                   if(p8==0){
                       info(BEGIN,8,0);
                       info(END,8,0);
                   }else{
                    waitpid(p8, &status1,0);
                    info(END,7,0);
                   }
               }else{
                   waitpid(p5, &status1,0);
                   info(END,5,0);
               }
           }else{
               waitpid(p3,&status1,0);
               info(END,4,0);
           }
           
       }else{
           waitpid(p2,&status1, 0);
           info(END,2,0);

           info(BEGIN,3,0);
       p3=fork();
       if(p3==0){
           info(BEGIN,6,0);
           info(END,6,0);

       }else{
           waitpid(p3,&status1, 0);
           info(END,3,0);
       }
       }

    }else{
        waitpid(p1,&status1, 0);
        info(END, 1, 0);
    }

    pthread_mutex_destroy(&lacat);
    sem_destroy(&semafor1);
    sem_destroy(&semafor2);
    return 0;
}
