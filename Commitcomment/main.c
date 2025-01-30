#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include "commitcomment.h"

int main(int argc, char* argv[]){
    //커밋 메시지 작성 파일
    int mfd; int mflags;
    mflags = O_CREAT| O_TRUNC | O_WRONLY;
    mmode = S_IRWXU | S_IRGRP | S_IROTH;
    mfd = open("./commit", mflags, mmode);

    //옵션 인자
    int opt;
    extern char* optarg;
    extern int optind;
    
    //커밋 메시지 작성
    write(mfd, "git add *\n", 10);
    write(mfd, "git commit -m \"Update: ", 23);
    char tbuf[10]; getdate(tbuf);
    write(mfd, tbuf, 10);
    write(mfd, "\"\n", 2);
    
    //옵션 처리
    while((opt = getopt(argc, argv, "p")) != -1){
        switch(opt){
            case 'p':
                write(STDOUT_FILENO, "-p: push\n", 9);
                write(mfd, "git push origin main\n", 21);
        }
    }

    //커밋/푸시
    system("cat ./commit && sh ./commit");
    close(mfd);
}
