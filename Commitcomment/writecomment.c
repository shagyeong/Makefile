#include "commitcomment.h"

void writecomment(int opt, const char* path){
    //커밋할 디렉터리로 이동
    chdir(path);

    //커밋 메시지 작성 파일
    int wfd;
    int wflags = O_CREAT| O_TRUNC | O_WRONLY;
    int wmode = S_IRWXU | S_IRGRP | S_IROTH;
    wfd = open("./git.sh", wflags, wmode);

    //커밋 메시지 작성
    write(wfd, "git add *\n", 10);
    write(wfd, "git commit -m \"Update: ", 23);
    char tbuf[10]; getdate(tbuf);
    write(wfd, tbuf, 10);
    if(*path != '.'){
        write(wfd, " ", 1); write(wfd, path, 2);
    }
    write(wfd, "\"\n", 2); 

    //옵션 처리
    if(opt == 'w'){
        write(STDOUT_FILENO, "write only\n", 11);
        close(wfd);
    }
    else{
        write(wfd, "git push origin main\n", 21);
        close(wfd);
        system("cat ./git.sh && sh ./git.sh");
    }

    //최상위 디렉터리로
    if(*path != '.'){
        chdir("..");
    }
}