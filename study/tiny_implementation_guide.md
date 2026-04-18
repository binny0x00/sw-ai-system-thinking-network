# Tiny 웹 서버 구현 가이드

이 문서는 `webproxy-lab/tiny/tiny.c`와 `webproxy-lab/tiny/cgi-bin/adder.c`를 완성하기 위한 구현 중심 가이드다.

## 목표

- 브라우저의 HTTP 요청을 읽는다.
- 정적 파일을 응답할 수 있다.
- CGI 프로그램을 실행해 동적 컨텐츠를 응답할 수 있다.
- 최소한 `GET` 요청과 기본 오류 응답을 처리할 수 있다.

## 코드 흐름 한 장 요약

```text
main
  -> Open_listenfd(port)
  -> Accept()
  -> doit(connfd)
       -> 요청라인 읽기
       -> method / uri / version 파싱
       -> 헤더 읽기
       -> parse_uri()
       -> stat()
       -> serve_static() or serve_dynamic()
```

## 함수별 역할

### `main`

- 서버 시작
- 포트 열기
- 반복적으로 새 연결 수락
- 각 연결마다 `doit(connfd)` 호출

### `doit`

- Tiny의 핵심 진입점
- HTTP 요청 한 건을 처리한다.
- 해야 할 일:
  - 요청라인 읽기
  - `GET`인지 검사
  - 요청 헤더 읽고 버리기
  - URI를 정적/동적으로 분류
  - 파일 존재 여부와 권한 검사
  - 적절한 응답 함수 호출

### `read_requesthdrs`

- 요청 헤더를 한 줄씩 읽는다.
- 빈 줄 `\r\n`이 나오면 헤더 끝이다.
- Tiny는 대부분 헤더를 활용하지 않고 읽어서 소비만 한다.

### `parse_uri`

- URI가 정적인지 동적인지 판별한다.
- 정적이면 파일 경로를 만든다.
- 동적이면 CGI 인자를 분리한다.

예상 결과:

- `/home.html` -> 정적
- `/cgi-bin/adder?1&2` -> 동적

### `serve_static`

- 상태줄과 헤더 전송
- 파일 타입 결정
- 파일 내용을 응답 본문으로 전송

### `get_filetype`

- 파일 확장자로 MIME 타입을 정한다.
- 예:
  - `.html` -> `text/html`
  - `.gif` -> `image/gif`
  - `.jpg` -> `image/jpeg`

### `serve_dynamic`

- CGI 프로그램 실행
- 자식 프로세스 생성
- 환경변수 `QUERY_STRING` 설정
- 자식의 표준출력을 클라이언트 소켓으로 연결

### `clienterror`

- `404`, `403`, `501` 같은 오류 응답을 보낸다.

## 구현하면서 확인할 체크포인트

### 1. 요청라인 파싱

이런 요청이 들어온다고 가정한다.

```http
GET /home.html HTTP/1.1
Host: localhost:8000

```

최소한 아래 세 값을 파싱해야 한다.

- `method = GET`
- `uri = /home.html`
- `version = HTTP/1.1`

### 2. GET만 허용

- Tiny 기본 구현은 `GET`만 지원한다.
- 다른 메서드가 오면 `501 Not Implemented`

### 3. 정적/동적 분기

- URI에 `cgi-bin`이 있으면 동적으로 보는 것이 Tiny의 단순 규칙이다.
- 아니면 정적 파일로 간주한다.

### 4. 권한 검사

- 정적:
  - 일반 파일인지
  - 읽기 가능한지
- 동적:
  - 일반 파일인지
  - 실행 가능한지

### 5. 동적 컨텐츠의 핵심

- Tiny가 직접 계산하는 것이 아니라 CGI 프로그램을 실행한다.
- `adder.c`는 쿼리 문자열을 읽어 계산 후 HTML 형식으로 출력한다.
- CGI 프로그램의 `stdout`이 곧 HTTP 응답 본문으로 간다.

## `adder.c`를 이해하는 포인트

### 입력

- 환경변수 `QUERY_STRING`
- 예: `first=1&second=2`

### 처리

- `&`, `=` 기준으로 문자열 분리
- 숫자 변환
- 합 계산

### 출력

- `Content-type`
- `Content-length`
- 빈 줄
- HTML 본문

즉, CGI는 "표준출력으로 HTTP body를 생성하는 프로그램"이라는 감각으로 보면 된다.

## 직접 테스트하는 순서

### 1. 빌드

```bash
make
cd /Users/choeyeongbin/webproxy_lab_docker/webproxy-lab/tiny && make
```

### 2. 서버 실행

```bash
cd /Users/choeyeongbin/webproxy_lab_docker/webproxy-lab/tiny
./tiny 8000
```

### 3. 정적 파일 테스트

```bash
curl -i http://127.0.0.1:8000/home.html
```

### 4. 동적 파일 테스트

```bash
curl -i "http://127.0.0.1:8000/cgi-bin/adder?1&2"
```

### 5. 오류 테스트

```bash
curl -i http://127.0.0.1:8000/no-such-file
```

## 구현이 막힐 때 보는 순서

1. `main`의 서버 루프가 맞는가
2. `doit`에서 요청라인을 제대로 읽는가
3. `read_requesthdrs`가 빈 줄까지 읽는가
4. `parse_uri`가 파일명과 인자를 잘 나누는가
5. `stat` 검사 조건이 맞는가
6. `serve_static` 또는 `serve_dynamic`에서 헤더를 먼저 보내는가

## 이번 과제에서 꼭 설명할 수 있어야 하는 질문

1. 왜 Tiny는 반복형(iterative) 서버인가?
2. 왜 요청 헤더를 다 쓰지 않는데도 읽어야 하는가?
3. 왜 정적 파일과 동적 컨텐츠의 처리 방식이 다른가?
4. 왜 `serve_dynamic`에서는 `fork`와 `execve`가 필요한가?
5. 왜 CGI 프로그램의 출력이 HTTP 응답처럼 보이는가?

## Tiny 완성 기준

- `tiny.c`의 핵심 함수가 모두 구현되어 있다.
- `adder.c`가 빌드되고 실행된다.
- 브라우저 또는 `curl`로 정적 페이지가 열린다.
- CGI 요청이 동작한다.
- 잘못된 요청에 대해 기본 에러 응답이 나온다.
