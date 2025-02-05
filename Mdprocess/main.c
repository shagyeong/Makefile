#include<stdio.h>
#include<unistd.h>
#include "mdprocess.h"

// $ ./mp chapter01.md README.md -3형태
int main(int argc, char* argv[]){
    FILE* rfp = fopen(argv[1], "r");
    FILE* wfp = fopen(argv[2], "w");
    int opt;
    int header;     //제목 수준(마크다운 '#', '##', '###', '####')
    char cbuf[256];
    int i;
    long offset;

    opt = getopt(argc, argv, "1234");
    switch(opt){
        case '1': header = 1; break;
        case '2': header = 2; break;
        case '3': header = 3; break;
        case '4': header = 4; break;
        default:  header = 4;
    }

    //첫 번째 줄 작성
    fread(cbuf, sizeof(char), 256, rfp);
    i = 0;
    while(i < 256 && cbuf[i] != '\n'){
        fputc(cbuf[i++], wfp);
    }
    fputc(cbuf[i], wfp);    //개행 문자까지 출력
    //오프셋 조정
    offset = i - 255;
    fseek(rfp, offset, SEEK_CUR);

    //두 번째 줄 이후 작성
    while(fread(cbuf, sizeof(char), 256, rfp) != 0){
        i = 0;
        while(i < 256){
            if(cbuf[i] == '#' && (cbuf[i + 1] == '#' || cbuf[i + 1] == ' ')){
                while(i < 256 && cbuf[i] != '\n'){
                    fputc(cbuf[i++], wfp);
                }
                fputc(cbuf[i], wfp);
            }
            else{
                i++;
            }
        }
        //오프셋 조정
        offset = i - 255;
        fseek(rfp, offset, SEEK_CUR);
    }

    //제목이 버퍼[255]로 끊긴 경우 처리 필요
    
    
    fclose(rfp);
    fclose(wfp);
}
