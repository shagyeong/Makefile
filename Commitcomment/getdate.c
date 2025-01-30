#include "commitcomment.h"

char __itoa(int i);

void getdate(char* tbuf){
    struct tm* tmbuf;
    time_t timep;
    time(&timep);
    tmbuf = gmtime(&timep);
    int year = tmbuf->tm_year + 1900;
    int month = tmbuf->tm_mon + 1;
    int day = tmbuf->tm_mday;

    tbuf[0] = __itoa(year / 1000);      year -= (year / 1000) * 1000;
    tbuf[1] = __itoa(year / 100);       year -= (year / 100) * 100;
    tbuf[2] = __itoa(year / 10);        year -= (year / 10) * 10;
    tbuf[3] = __itoa(year);
    tbuf[4] = '-';
    tbuf[5] = __itoa(month / 10);       month -= (month / 10) * 10;
    tbuf[6] = __itoa(month);
    tbuf[7] = '-';
    tbuf[8] = __itoa(day / 10);          day -= (day / 10) * 10;
    tbuf[9] = __itoa(day);
}

char __itoa(int i){
    char c;
    switch(i){
        case 0: c = '0'; break;
        case 1: c = '1'; break;
        case 2: c = '2'; break;
        case 3: c = '3'; break;
        case 4: c = '4'; break;
        case 5: c = '5'; break;
        case 6: c = '6'; break;
        case 7: c = '7'; break;
        case 8: c = '8'; break;
        case 9: c = '9'; break;
    }
    return c;
}
