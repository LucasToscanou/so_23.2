#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_VETOR 1000000

int main (int argc, char *argv[])
{

double time_spent =0.0;
clock_t begin = clock();

// Criando o vetor
int vetor[TAM_VETOR];
int soma = 0;
for(int i = 0; i < TAM_VETOR; i++)
  vetor[i] = 5;

// Somando todos os valores
for(int i = 0; i < TAM_VETOR; i++){
  vetor[i] = vetor[i]*2;
  soma = soma + vetor[i];
}

clock_t end = clock();
time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
printf("Time spent: %f seconds\n", time_spent);

printf("soma = %d\n", soma);
return 0;

}