#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define EVER ;;

void killHandler(int sinal);

int main (void)
{
    signal(SIGKILL, killHandler);
    printf("Vai parar...\n");
    pause();
    for(EVER);
}

void killHandler(int sinal)
{
    puts("Um sinal SIGKILL foi recebido.\n");
    for(EVER);
}
