# CSAPP 11장 학습 허브

이 폴더는 `CSAPP 3e Chapter 11: Network Programming`과 `webproxy-lab` 과제를 함께 공부하기 위한 개인 학습 자료 모음이다.

이번 주 목표는 아래 3가지를 한 흐름으로 이해하는 것이다.

1. `11.1 ~ 11.4`를 통해 소켓 프로그래밍의 흐름과 용어를 이해한다.
2. `11.5 ~ 11.6`를 따라 `tiny` 웹 서버를 완성한다.
3. `proxy.c`로 확장해 프록시 서버, 동시성, 캐시를 준비한다.

## 먼저 읽을 순서

1. [csapp_11_1.md](csapp_11_1.md)
2. [csapp_11_2.md](csapp_11_2.md)
3. [csapp_11_3_4.md](csapp_11_3_4.md)
4. [c_for_network_programming.md](c_for_network_programming.md)
5. [tiny_implementation_guide.md](tiny_implementation_guide.md)
6. [proxy_lab_guide.md](proxy_lab_guide.md)

## 이번 과제에서 꼭 잡아야 하는 키워드

| 키워드 | 이번 과제에서 이해해야 하는 수준 |
| --- | --- |
| `BSD Socket` | `socket -> bind/listen/accept` 또는 `socket -> connect` 흐름을 설명할 수 있어야 한다. |
| `IP` | IP 주소가 "호스트를 식별하는 주소"라는 점과 `DNS -> IP 변환` 흐름을 이해하면 충분하다. |
| `TCP` | 연결형, 바이트 스트림, 순서 보장이라는 특성이 왜 HTTP 서버 구현에 필요한지 설명할 수 있어야 한다. |
| `UDP` | 비연결형이라는 특성만 알고, 이번 과제는 TCP 중심이라는 점을 구분하면 된다. |
| `HTTP` | 요청라인, 헤더, 본문, 상태코드, 정적/동적 컨텐츠 처리를 읽을 수 있어야 한다. |
| `file descriptor` | 소켓도 파일처럼 `fd`로 다룬다는 점이 중요하다. |
| `DNS` | `www.example.com`을 IP 주소로 바꾸는 과정이라는 점만 확실히 잡으면 된다. |
| `REST API` | 웹 자원을 URL로 다루고 HTTP 메서드로 조작하는 스타일이라는 개념 수준이면 충분하다. |
| `HTTP Method` | `GET`, `POST`, `DELETE`, `PUT/PATCH`의 목적 차이를 이해하되 Tiny는 우선 `GET` 중심이다. |
| `OSI 7계층` | 계층 이름을 외우기보다 `HTTP(응용) - TCP(전송) - IP(인터넷)`의 위치 관계를 이해하는 것이 더 중요하다. |
| `CDN` | 원본 서버 대신 가까운 캐시 서버가 컨텐츠를 제공한다는 개념만 이해하면 충분하다. |
| `Proxy` | 클라이언트와 서버 사이에서 요청/응답을 중계하고, 필요시 캐시/로그/필터링을 수행하는 서버다. |

## 추천 학습 루틴

### 1. 개념 30분

- 섹션 `11.1 ~ 11.4`를 읽으면서 아래 질문에 답해본다.
- 클라이언트와 서버는 각각 어느 시점에 시작되는가?
- 소켓은 왜 `fd`로 표현되는가?
- TCP 연결은 누가 열고 누가 받아들이는가?
- 브라우저 주소창의 도메인은 어떻게 서버 IP가 되는가?

### 2. 코드 40분

- [webproxy-lab/tiny/tiny.c](../webproxy-lab/tiny/tiny.c)를 열고 함수 단위로 읽는다.
- `main -> doit -> parse_uri -> serve_static/serve_dynamic` 호출 흐름을 종이에 그린다.
- 모르는 C 문법은 [c_for_network_programming.md](c_for_network_programming.md)와 함께 본다.

### 3. 실습 20분

- `tiny`를 실행한 뒤 브라우저와 `curl`로 테스트한다.
- `GET /home.html`
- `GET /cgi-bin/adder?1&2` 형태의 동적 요청
- 잘못된 경로 요청 후 `404` 확인

### 4. 회고 10분

- 오늘 새로 이해한 것 3개
- 아직 헷갈리는 함수 2개
- 내일 바로 구현할 TODO 1개

## 이번 주 체크리스트

- [ ] `11.1 ~ 11.4` 각 절의 핵심을 한 문장으로 설명할 수 있다.
- [ ] `socket`, `connect`, `bind`, `listen`, `accept`의 역할을 구분할 수 있다.
- [ ] `tiny.c`의 처리 흐름을 함수 단위로 설명할 수 있다.
- [ ] 정적 컨텐츠와 동적 컨텐츠 차이를 설명할 수 있다.
- [ ] `adder.c`가 CGI로 동작하는 이유를 설명할 수 있다.
- [ ] 숙제 `11.6C, 7, 9, 10, 11`을 풀었다.
- [ ] `proxy.c`에서 순차 처리 버전을 만들었다.
- [ ] 동시성 모델 후보를 하나 정했다. (`process`, `thread`, `I/O multiplexing`)
- [ ] 캐시 설계를 말로 설명할 수 있다. (`MAX_CACHE_SIZE`, `MAX_OBJECT_SIZE`)

## 바로 써볼 실습 도구

- [http_flow_lab.sh](http_flow_lab.sh): 로컬에서 Tiny 서버에 요청을 보내며 HTTP 흐름을 확인하는 스크립트

## 참고

- CSAPP 3e 목차 기준으로 Chapter 11은 `11.1 Client-Server`, `11.2 Networks`, `11.3 Global IP Internet`, `11.4 Sockets`, `11.5 Web Servers`, `11.6 Tiny Web Server` 순서로 구성되어 있다. 확인용 공개 목차: [csapp.cs.cmu.edu](https://csapp.cs.cmu.edu/3e/pieces/preface3e.pdf)
