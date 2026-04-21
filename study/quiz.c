// 1.
int fibonacci(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return (fibonacci(n - 1) + fibonacci(n - 2));
}

// 2. 휘발성

// 3. 0,1,2

// 4. DNS

// 5.
/*
* 웹 브라우져 https://www.google.com/search?q=정글 입력 후 주소창 엔터
-> DNS를 통해 https://www.google.com을 바이너리 ip 주소로 변환
-> ip 주소에서 네트워크 어뎁터 또는 호스트에 대한 정보를 얻어 객체 형태로 커널의 TCP/IP에 실어 보냄
-> 서버와 연결되어 서버가 통신할 소켓 정보를 보냄
-> 해당 소켓으로 http 프로토콜 get 요청으로 엔드포인트 search에 "정글" 쿼리를 실어 보냄
-> 서버가 이에 대한 결과로 화면에 표출할 파일을 보냄
-> 브라우져에 받은 파일을 렌더링 함
*/