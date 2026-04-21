#include "../csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port;
    char buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    /*
     * 키보드에서 한줄 읽음
     * 읽은 문자열을 buf에 저장
     * 사용자가 EOF를 입력하면 NULL이 되어 루프가 끝남
     *
     * echoserver에서는 한줄단위로 동작함
     */
    while (Fgets(buf, MAXLINE, stdin) != NULL)
    {
        // 서버에 전송 보냄
        Rio_writen(clientfd, buf, strlen(buf));
        // 서버가 보낸 응답 한 줄 읽음
        if (Rio_readlineb(&rio, buf, MAXLINE) == 0)
        {
            fprintf(stderr, "server closed connection\n");
            break;
        }
        // 서버 응답 화면에 출력
        Fputs(buf, stdout);
    }

    Close(clientfd);
    return 0;
}
