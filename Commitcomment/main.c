#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include "commitcomment.h"

// ./cc: 루트의 git.sh 업데이트/푸시
// ./cc NW OS SP: 인자로 지정한 디렉터리의 git.sh 업데이트/푸시
// ./cc -w NW: 옵션 인자로 지정한 디렉터리의 git.sh 업데이트

int main(int argc, char* argv[]){
    int i = 1;

    //옵션 처리
    int opt = getopt(argc, argv, "w:");
    extern char* optarg;
    extern int optind;
    switch(opt){
        case 'w':
            writecomment(opt, optarg);
            break;
        default:
            if(argc == 1){
                writecomment(opt, ".");
            }
            else{
                while(i < argc){
                    writecomment(opt, argv[i++]);
                }
            }
    }
}
