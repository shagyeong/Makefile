#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
    int i = 0;
    char sbuf[256] = "hello ";
    char* cbuf = argv[1];
    write(STDOUT_FILENO, sbuf, 256);
    while(*cbuf != '\0'){
        write(STDOUT_FILENO, cbuf, 1);
        cbuf++;
    }
    *cbuf = '\n';
    write(STDOUT_FILENO, cbuf, 1);
}