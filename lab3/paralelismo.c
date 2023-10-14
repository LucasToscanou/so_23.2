#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>

#define TAM_VETOR 1000000
#define NUM_THREADS 100

void *paralelismo(void *threadid) {
    int i = (int)threadid;
    int segmento1, segmento2, segmento_clock, *soma, *vetor, size = TAM_VETOR;

    clock_t *time;

    segmento1 = shmget(7000, sizeof(int) * size, IPC_CREAT | S_IRUSR | S_IWUSR);
    segmento2 = shmget(7001, sizeof(int) * NUM_THREADS, IPC_CREAT | S_IRUSR | S_IWUSR);
    segmento_clock = shmget(7002, sizeof(clock_t) * 2, IPC_CREAT | S_IRUSR | S_IWUSR);

    // Attach shared memory segments
    vetor = (int *)shmat(segmento1, 0, 0);
    soma = (int *)shmat(segmento2, 0, 0);
    time = (clock_t *)shmat(segmento_clock, 0, 0);

    soma[i] = 0;
    int forsize = size/NUM_THREADS;
    clock_t time_ver = clock();
    if (time_ver < time[0]) {
        time[0] = time_ver;
    }
    for (int j = 0; j < forsize; j++) {
        vetor[i * forsize + j] = vetor[forsize * i + j] * 2;
        soma[i] = soma[i] + vetor[i * forsize + j];
        // printf("soma %d = %d\n",i,soma[i]);
    }
    time_ver = clock();
    if (time_ver > time[1]) {
        time[1] = clock();
    }
    
    return NULL;
}

int main() {
    double time_spent = 0.0;
    int segmento1, segmento2, segmento_clock, *vetor, *soma, size = TAM_VETOR, soma_total = 0;
    clock_t *time;

    segmento1 = shmget(7000, sizeof(int) * size, IPC_CREAT | S_IRUSR | S_IWUSR);
    segmento2 = shmget(7001, sizeof(int) * NUM_THREADS, IPC_CREAT | S_IRUSR | S_IWUSR);
    segmento_clock = shmget(7002, sizeof(clock_t) * 2, IPC_CREAT | S_IRUSR | S_IWUSR);

    // Attach shared memory segments
    vetor = (int *)shmat(segmento1, 0, 0);
    soma = (int *)shmat(segmento2, 0, 0);
    time = (clock_t *)shmat(segmento_clock, 0, 0);

    pthread_t threads[NUM_THREADS];
    int t;

    for(int i = 0; i < size; i++)
      vetor[i] = 5;

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, paralelismo, (void *)t);
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        soma_total = soma_total + soma[i];
    }

    time_spent += (double)(time[1] - time[0]) / CLOCKS_PER_SEC;

    printf("Time spent: %f seconds\n", time_spent);
    printf("soma_total = %d\n", soma_total);

    shmctl (segmento1, IPC_RMID, 0);
    shmctl (segmento2, IPC_RMID, 0);
    shmctl (segmento_clock, IPC_RMID, 0);
    return 0;
}








