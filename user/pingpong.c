#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int f2c[2];
    int c2f[2];
    pipe(f2c);
    pipe(c2f);
    int pid=fork();
    if(pid<0){
        printf("error\n");
        exit(1);
    }
    else if(pid==0){
        close(f2c[1]);
        close(c2f[0]);
        char ch;
        read(f2c[0],&ch,1);
        printf("%d: received ping\n",getpid());
        write(c2f[1],&ch,1);
        close(f2c[0]);
        close(c2f[1]);
    }
    else{
        char ch;
        close(f2c[0]);
        close(c2f[1]);
        write(f2c[1],"c",1);
        read(c2f[0],&ch,1);
        printf("%d: received pong\n",getpid());
        close(f2c[1]);
        close(c2f[0]);
    }
    exit(0);
}