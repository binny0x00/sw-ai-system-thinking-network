# Echo 실습

이 디렉터리는 CSAPP 11장의 `echo client/server` 흐름을 직접 확인하기 위한 최소 실습 코드다.

## 파일

- `echoserver.c`: 반복형 TCP echo 서버
- `echoclient.c`: 표준입력 한 줄을 서버에 보내고 그대로 돌려받는 클라이언트
- `Makefile`: 상위 디렉터리의 `../csapp.c`, `../csapp.h`를 재사용해 빌드

## 빌드

```bash
cd /Users/choeyeongbin/webproxy_lab_docker/webproxy-lab/echo
make
```

## 실행

서버:

```bash
./echoserver 8000
```

클라이언트:

```bash
./echoclient 127.0.0.1 8000
```

클라이언트 실행 후 터미널에 문자열을 입력하면 서버가 그대로 돌려준다.

## 이 실습에서 확인할 것

1. 서버는 `Open_listenfd -> Accept -> echo -> Close` 흐름으로 동작한다.
2. 클라이언트는 `Open_clientfd`로 서버에 연결한다.
3. 실제 송수신은 `Rio_readlineb`, `Rio_writen`으로 처리한다.
4. 소켓도 `file descriptor`라서 파일처럼 읽고 쓸 수 있다.
