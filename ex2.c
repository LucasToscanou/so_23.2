
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define EVER ;;

void killHandler(int sinal);

int main (void)
{
    void (*p)(int);// ponteiro para função que recebe int como parâmetro
    p = signal(SIGKILL, killHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    for(EVER);
    }

void killHandler(int sinal)
{
    puts("Um sinal SIGKILL foi recebido.\n");
}
