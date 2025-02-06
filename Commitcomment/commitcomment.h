#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>

struct directory{
    char code[2];   //NW, SP, OS 형태의 과목 코드
};
typedef struct directory dir_t;

void getdate(char* tbuf);                //시간 서식 지정
void writecomment(int opt, const char* path);  //셸 파일 조작
