#include "../csapp.h"

static void echo(int connfd);

/*
 * 명령어 예시) ./echoserver 8000
 * argc : 전달된 인자 개수, argv: 문자열 포인터 배열
 * argc = 2
 * argv[0] = "./echoserver"
 * argv[1] = "8000"
 *
 * argv[0][0]의 타입 : char
 * argv[0]의 타입 : char *
 * argv의 타입 : char **
 */
int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    // 인자가 2개 안들어오면 에러 메세지 표출
    if (argc != 2)
    {
        /*
         * fprint()는 printf()와 달리 스트림(데이터 주고 받는 통로) 지정 가능
         * stderr : 표준 에러 - 모니터
         * 올바른 실행 형식 안내하기 위한 메시지
         */
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    /*
     * 듣기 식별자 open()
     */
    listenfd = Open_listenfd(argv[1]);

    /*
     * 서버는 이미 listenfd를 열어둔 상태다.
     * while (1)로 무한 루프를 돌면서 새 클라이언트를 기다린다.
     * Accept()가 클라이언트 접속이 올 때까지 블록된다.
     * 접속이 오면 그 클라이언트와 통신할 전용 소켓 connfd를 받는다.
     * Getnameinfo()로 접속한 클라이언트의 호스트/포트 정보를 문자열로 바꾼다.
     * 로그를 출력한다.
     * echo(connfd)로 실제 요청/응답 처리를 한다.
     * 처리가 끝나면 Close(connfd)로 그 클라이언트 연결을 닫는다.
     * 다시 루프 처음으로 돌아가 다음 클라이언트를 기다린다. */
    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen,
                    client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("accepted connection from (%s, %s)\n",
               client_hostname, client_port);
        echo(connfd);
        Close(connfd);
    }
}

static void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %zu bytes\n", n);
        Rio_writen(connfd, buf, n);
    }
}
