#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void zeroHandler(int sign);
void consider_float_values(int argc, char *argv[]);
void consider_int_values(int argc, char *argv[]);

int main (int argc, char *argv[])
{
    // Capturando o sinais
    signal(SIGFPE, zeroHandler);

    // Escolha entre entrada de reais ou inteiros
    consider_float_values(argc, argv);
    // consider_int_values(argc, argv);
    return 0;
}

void consider_float_values(int argc, char *argv[])
{
    float n0, n1;   
    sscanf(argv[1], "%f", &n0);
    sscanf(argv[2], "%f", &n1);
    
    // Operacoes básicas
    printf("add: %f\n", n0+n1);
    printf("sub: %f\n", n0-n1);
    printf("mul: %f\n", n0*n1);
    printf("div: %f\n", n0/n1);
}

void consider_int_values(int argc, char *argv[])
{
    int n0, n1;   
    sscanf(argv[1], "%d", &n0);
    sscanf(argv[2], "%d", &n1);
    
    // Operacoes básicas
    printf("add: %d\n", n0+n1);
    printf("sub: %d\n", n0-n1);
    printf("mul: %d\n", n0*n1);
    printf("div: %d\n", n0/n1);
}


void zeroHandler(int sign)
{
    printf("Sinal %d capturado!\tAlgum dos números de entrada é zero.\n", sign);
    exit(0);
}

