# 7장 시스템 수준 입출력
## 7.1 유닉스 입출력
### 7.1.3 개요
#### 파일시스템
* 좁은 의미의 파일 : 파일 시스템이 관리하는(디스크 내부에 있는) 파일
* 파일시스템 : (디스크 내부에 있는) 파일에 대한 정보(블록 위치 등)를 관리한다
* 계층구조로 나누어 관리한다
* *뷰*는 파일시스템 외부 특수 파일까지 확인 가능(그림 7.1.8 참고)
* 참고
    * 리커버리 시스템 : 파일시스템 설계의 핵심
    * 오픈 소스 파일시스템 프로젝트에 기여해보기
#### 파일
* **파일** : 데이터의 스트림(바이트의 시퀀스)
* 유닉스 입출력 인터페이스 : **파일**
* 유닉스 입출력 장치 : **파일**
* 커널(이미지) : **파일**
* **CPU, 메모리를 제외한 모든 장치가 파일로 표현된다**
* 참고 : dev/sda2, tty2 - 파티션시 번호가 붙음
#### 입출력 인터페이스
* 파일 열기/닫기 : open(2), close(2)
* 파일 읽기/쓰기 : read(2), write(2)
* lseek(2) : **오프셋**(파일 포인터) 지정
* 간단한 인터페이스
    * sequential한 read/write를 가정하고 '어디에서'읽을지 지정 불가
    * 단, 개발 경향이 변화에 따라 지정 가능한 시스템 호출 등장 : pread(2), pwrite(2)
### 7.1.5 파일 타입
#### 강의에서 다루는 파일 타입
* 레귤러 파일 : 임의의(arbitrary) 데이터 저장
* 디렉터리 : 관계된 파일 그룹에 대한 인덱스
* 소켓 : 다른 기기와 통신에 사용
#### 강의에서 다루지 않는 파일 타입
* *파이프*
* *심벌릭 링크*
* *캐릭터 디바이스*
* *블럭 디바이스*
### 7.1.6 레귤러 파일
#### 레귤러 파일
* **레귤러 파일** : 임의의(arbitrary) 데이터를 저장하는 파일
* 바이트 인코딩 : 이진 파일
* ASCII 인코딩 : 텍스트 파일
* 커널은 둘을 구별할 수 없어 인코딩 방식이 잘못되면 파일이 깨짐
#### 텍스트파일
* 텍스트파일 : 텍스트라인의 시퀀스
    * 각 텍스트라인은 개행 문자 '\n'에 의해 종료된다(terminated)
* 구식 타자기의 동작
    * LF(line feed) : 다음(아래) 줄로 옮김
    * carriage return : 종이를 가장 오른쪽으로 옮김(home으로 커서를 옮기는 것에 대응)
* 시스템별 EOL(end of line) 지시자
    * Linux/Mac OS :'\n' - LF
    * Windows/인터넷 프로토콜 : '\r\n' -CR LF
### 7.1.7 디렉터리
#### 디렉터리
* **디렉터리**  : *링크*의 배열로 이루어짐
    * 각 링크는 파일의 *파일명*과 매핑
* 각 디렉터리는 적어도 두 개의 엔트리를 포함
    * '.' : 스스로에 대한 링크(현재 위치)
    * '..' : 부모 디렉터리에 대한 링크
#### 주요 디렉터리 명령어
```
mkdir
ls
rmdir
```
```
$ ls -al
합계 48
drwxrwxr-x  9 shagyeong shagyeong 4096 11월  5 09:36 .
drwxr-x--- 29 shagyeong shagyeong 4096 11월  5 15:39 ..
...
-rw-rw-r--  1 shagyeong shagyeong   65 11월  5 08:53 git.sh
-rw-rw-r--  1 shagyeong shagyeong   48 10월 11 12:30 objdump.sh
-rw-rw-r--  1 shagyeong shagyeong 1512 11월  1 10:29 readme.md
```
* 'd' : 디렉터리
* '-' : 레귤러 파일
### 7.1.8 디렉터리 계층 구조
#### 개요
* 루트 디렉터리 : '/'(슬래시)
* cwd : 현재 작업 디렉터리 - 커널이 각 프로세스에 대해 유지
* cd(1) : change directory - 디렉터리 이동 명령어
#### 디렉터리 계층 구조
* 그림 7.1.8 참고
    ```
    /
        bin/
            bash
        dev/
            tty1
        etc/
            group
            passwd
        home/
            shagyeong/
                hello.c
            bryant/
        usr/
            include/
                stdio.h
                sys/
                    unistd.h
            bin/
                vim
    ```
### 7.1.9 경로(pathname)
#### 경로
* **경로** : 계층 구조에서 파일 구조를 구분(denote)한다
#### 절대/상대경로
* **절대경로**(absolute pathname) : 슬래시'/'(루트)로 시작하는 경로
    * 예시 : /home/shagyeong/hello.c
* **상대경로**(relative pathname) : cwd에 대한 상대적인 경로(슬래시로 시작하지 않음)
    * 예시 : ./hello.c
### 7.1.10 파일 열기
#### 파일 열기
* **파일 열기** : 커널에게 파일에 접근할 준비를 하도록 요청
#### open(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int open(const char* pathname, int flags);
int open(const char* pahtname, int flags, mode_t mode);
```
```C
int fd;
if((fd = open("/etc/hosts", O_RDONLY)) < 0){
    perror("open");
    exit(1);
}
```
* 성공시 파일 디스크립터 리턴
* 실패시 -1 리턴
#### 파일 디스크립터
* **파일 디스크립터** : int형 식별자(identifying integer)
* 리눅스 셸에 의해 생성되는 각 프로세스는 아래 3개의 터미널 관련 파일 디스크립터와 삶을 시작
    * **0(stdin)** : 표준 입력
    * **1(stdout)** : 표준 출력
    * **2(stderr)** : 표준 에러
### 7.1.11 파일 닫기
#### 파일 닫기
* **파일 닫기** : 커널에게 파일 접근이 끝났음을 알림
#### close(2)
```C
#include<uinistd.h>
int close(int fd);
```
```C
int fd; int ret;
if((ret = close(fd)) < 0){
    perror("close");
    exit(1);
}
```
#### 이미 닫은 파일을 다시 닫기
* 스레드 프로그램에서 '재앙' 초래
* **다른 스레드에서 닫은 파일에 대한 fd로 파일을 열고 다시 닫는 경우**
* 온화해보이지만(seemingly benign) 반드시 리턴 코드를 확인할 것
    * bnign : '버닌'(bəˈnīn)으로 발음함
### 7.1.12 파일 읽기
#### 파일 읽기
* **파일 읽기** : 현재 **파일 포지션(오프셋)에서 메모리로** 바이트를 복제 후 포지션 업데이트
#### read(2)
```C
#include<unistd.h>
ssize_t read(int fd, void* buf, size_t count);
```
```C
char buf[512];
int fd;
int nbytes;
//fd에 대한 파일을 512바이트씩 읽음
if((nbytes = read(fd, buf, sizeof(buf))) < 0){
    perror("read");
    exit(1);
}
```
* 성공시 : fd에 대해 buf로 읽은 바이트 수 리턴(number of bytes read from file fd into buf)
    * ssize_t는 부호 있는 정수형
    * **short count 가능**(읽은 바이트 수가 버퍼 크기보다 작은 경우)
* 실패시 : 음수값 리턴
### 7.1.13 파일 쓰기
#### 파일 쓰기
* **파일 쓰기** : **메모리에서 파일 포지션으로** 바이트를 복제 후 포지션 업데이트
#### write(2)
```C
#include<unistd.h>
ssize_t write(int fd, const void* buf, size_t count);
```
```C
char buf[512];
int fd;
int nbytes;
//fd에 대한 파일에 512바이트씩 write
if((nbytes = write(fd, buf,sizeof(buf))) < 0){
    perror("write");
    exit(1);
}
```
* 성공시 : fd에 대해 buf로 작성한 바이트 수 리턴(number of bytes wrriten from buf to file fd)
    * **short count 가능**(작성한 바이트 수가 버퍼 크기보다 작은 경우)
* 실패시 : 음수값 리턴
### 7.1.14 예제 : 표준 입력을 표준 출력으로 복사
```C
#include<stdlib.h>
#include<unistd.h>

int main(void){
	char c;
	while(read(STDIN_FILENO, &c, 1) != 0){
		write(STDOUT_FILENO, &c, 1);
	}
	exit(0);
}
```
```
$ ./test
hello
hello
^C
```
* 0번 fd를 read한 버퍼를 1번 fd에 write
### 7.1.15 short count
#### short count
* **short count** : 읽거나 쓴 바이트 수가 버퍼 크기보다 작은 경우
#### 발생 시기
* read(2)에서 EOF를 마주친 경우
* 터미널에서 텍스트 라인을 읽는 경우
* 네트워크 소켓을 읽기/쓰기 하는 경우
#### 절대 발생하지 않는 경우
* 디스크 파일 읽기(EOF 제외)
* 디스크 파일 쓰기
* 항상 short count를 허용하는 것이 좋음

## 7.2 RIO (robust I/O) package
### 7.2.17 개요
#### RIO 패키지
* RIO 패키지 : short count가 자주 발생하는 네트워크 프로그램에서 효율적이고 강력한(robust) 입출력을 제공하는 wrapper 집합
#### 제공 함수
* 버퍼링되지 않은 입력, 이진 데이터 출력 : rio_readn, rio_writen
* 버퍼링된 텍스트 라인 입력, 이진 데이터 출력 : rio_readlineb, rio_readnb
* 버퍼링된 RIO 루틴
    * 스레드로부터 안전
    * 동일한 fd에서 임의로 끼워 넣을 수 있다(can be interleaved arbitrarily on the same descriptor)

## 7.3 Metadata, sharing, and redirection
### 7.3.25 메타데이터
#### 개요
* **메타데이터** : 데이터에 관한 데이터 - 파일 데이터
* 파일에 대한(per-file) 메타데이터는 **커널이 관리**
* 메타데이터에 대한 사용자 접근 : stat(2), fstat(2)
#### 구조체 stat
```C
/* Metadata returned by the stat and fstat functions */
struct stat {
    dev_t st_dev;             //device
    ino_t st_ino;             //inode
    mode_t st_mode;           //mode(-rwxrwxrwx형태의 파일 타입과 protection)
    nlink_t st_nlink;         //하드 링크 수
    uid_t st_uid;             //소유자 user id
    gid_t st_gid;             //소유자 group id
    dev_t st_rdev;            //device type(inode device인 경우)
    off_t st_size;            //byte 단위의 total size
    unsigned long st_blksize; //파일시스템 입출력을 위한 블럭 사이즈
    unsigned long st_blocks;  //할당된 블럭 수
    time_t st_atime;          //마지막 접근 시각
    time_t st_mtime;          //마지막 수정 시각
    time_t st_ctime;          //마지막 변경 시각
};
```
#### stat(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int stat(const char* pathname, struct stat* statbuf);
```
### 7.3.26 예제 : 메타데이터 접근
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char** argv){
	struct stat statbuf;
	char* type; char* readok;
	stat(argv[1], &statbuf);

	/*파일 타입 접근*/
	if(S_ISREG(statbuf.st_mode)){type = "regular";}
	else if(S_ISDIR(statbuf.st_mode)){type = "directory";}
	else{type = "other";}

	/*파일 모드 접근*/
	if((statbuf.st_mode & S_IRUSR)){readok = "yes";}
	else{readok = "no";}

	/*메타데이터 출력*/
	printf("type : %s, read : %s\n", type, readok);
	exit(0);
}
```
```
$ ./test test.sh
type : regular, read : yes
$ ./test ..
type : directory, read : yes
```
### 7.3.27 커널 관점 입출력 표현
#### 개요
* 그림 7.3.27 참고
* 디스크립터 테이블 : 프로세스마다 **개별로 존재**
* open file 테이블 : **모든 프로세스가 공유**
* v-node 테이블 : **모든 프로세스가 공유**
#### open
* 그림 7.3.27 참고
* 두 개의 fd가 두 개의 파일을 참조
* 1번 fd(표준 출력)은 터미널을 가리킴
* 4번 fd 디스크 파일 open을 가리킴
#### 파일 셰어링
* 그림 7.3.28 참고
* 두 개의 fd가 같은 디스크 파일을 공유
* **개별 open file 테이블**
* **같은 v-node 테이블을 가리킴**
#### 포크
* 그림 7.3.29, 그림 7.3.30 참고
* **자식 프로세스의 디스크립터 테이블에서 부모 프로세스의 open file 테이블을 가리킴**
### 7.3.31 입출력 리디렉션
#### 개요
* 어떻게 셸이 입출력 리디렉션을 구현하는가?
    * '>'
    ```
    $ ls > foo.txt
    ```
* dup2(2)로 구현
#### dup2(2)
```C
#include<unistd.h>
int dup2(int oldfd, int newfd);
```
* (프로세스별) 디스크립터 테이블 엔트리 oldfd에 newfd를 복제
#### 예제 : 표준 출력을 디스크 파일로 리디렉션
* 표준 출력 fd에 디스크 파일에 fd를 복제
* 표준 출력 fd에 대한 write가 디스크 파일에 write된 것을 확인
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdio.h>

    int main(int argc, char* argv[]){
    	int fd_stdout = STDOUT_FILENO;
    	int fd_disk = open(argv[1], O_WRONLY);

    	dup2(fd_disk, fd_stdout);
    	write(fd_stdout, "hello\0", 6);
    
    	close(fd_stdout);
    	close(fd_disk);
    }
    ```
    ```
    $ ./test test.txt
    $ cat test.txt
    hello
    ```

## 7.4 Standard I/O
### 7.4.35 표준 입출력 함수
* C 표준 라이브러리 : 고수준 표준 입출력 함수 제공
    ```
    fopen(3), fclose(3)     //파일 열기/닫기
    fread(3), fwrite(3)     //바이트 읽기/쓰기
    fgets(3), fputs(3)      //텍스트 라인 읽기/쓰기
    fscanf(3), fprintf(3)   //포멧 기반 읽기/쓰기
    ```
### 7.4.36 표준 입출력 스트림
#### 스트림
* 표준 입출력 모델은 파일을 ***스트림***으로 open
    * fd, 버퍼에 대한 추상화
#### 표준 스트림
* C 프로그램은 3개의 open 스트림으로 삶을 시작
    * **stdin** : 표준 입력
    * **stdout** : 표준 출력
    * **stderr** : 표준 에러
    ```C
    #include<stdio.h>
    extern FILE* stdin;
    extern FILE* stdout;
    extern FILE* stderr;
    int main(void){
        fpirntf(stdout, "hello\n");
    }
    ```
### 7.4.37 버퍼링된 IO
#### 버퍼링 motivation
* 애플리케이션에서 캐릭터 단위로 읽기/쓰기를 수행하는 경우가 있음
* 입출력 시스템 호출로 구현시 비용 증가(커널 영역까지 진입해야 함)
#### 버퍼링된 read
* 비용이 큰 **시스템 호출 횟수를 줄이기 위해** 1회 read시 블럭 단위로 가져옴
    * 라이브러리 함수로 버퍼에 있는 내용에 접근
* read(2)로 바이트 블럭을 읽음
* 라이브러리 함수로 버퍼로부터 1바이트를 취함
* 버퍼가 빈 경우 리필
#### 표준 입출력 함수
* **표준 입출력 함수는 버퍼링된 입출력을 사용한다**
* 라이브러리 함수로 버퍼에 적은뒤 시스템 호출
* 그림 7.4.38 참고
* strace를 이용해 버퍼링 동작 확인 가능(그림 7.4.39)

## 7.5 Closing remarks
### 7.5.41 유닉스 입출력 vs 표준입출력 vs RIO
* 표준입출력, RIO : 저수준 유닉스 입출력을 이용한 '구현'이다
* 그림 7.5.41 : 입출력 계층 구조
### 7.5.42 유닉스 입출력 pros and cons
#### pros
* 가장 일반적이고 낮은 오버헤드의 입출력 형태
    * 다른 입출력 패키지는 유닉스 입출력을 이용한 '구현'임
* 메타데이터 접근 함수 제공
* async-signal-safe : 시그널 핸들러에서 안전하게 사용될 수 있다
#### cons
* short count를 다루기 까다로움
* 효율적인 텍스트 라인 읽기를 다루기 까다로움
* 두 문제는 표준입출력, RIO 패키지에서 이미 해결되었음
### 7.5.43 표준입출력 pros and cons
#### pros
* read(2), write(2) 호출 횟수를 줄임으로서 버퍼링의 효율을 높임
* short count 처리
#### cons
* 메타데이터 접근 함수 없음
* async-signal-safe하지 않아 시그널 핸들러에 적절하지 않음
* 네트워크 소켓 입출력에 적절하지 않음
### 7.5.44 입출력 함수 선정
#### general rule
* 가능한 한 가장 high-level 함수 사용
* 표준입출력 함수로 거의 모든 작업 수행 가능
* 함수에 대한 이해 필수
#### 표준입출력 사용 시기
* 디스크, 터미널 파일 작업시
* 커널 접근으로 인한 (시간적)비용 증가를 막기 위해 버퍼링된 입출력 사용 필요
#### 저수준입출력 사용
* 시그널 핸들러 내부에서 작업시 : 유닉스 입출력은 async-signal-safe
* 최적화시 드물게 사용
