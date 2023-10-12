#include <stdio.h>
#include <unistd.h>
#define EVER ;;

int main(int argc, char *argv[]){
    printf("Loop eterno do pid = %d.\n", getpid());
    for(EVER){
        sleep(0.5);
        printf("loop %d", getpid());
    };
}