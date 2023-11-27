#include "Common.h"

#define SERVERPORT 9000
#define BUFSIZE    512

void ProcessGameData(SOCKET client_sock, const char* data)
{
	// 여기에 클라이언트의 게임 데이터를 처리하는 로직을 추가
	// 받은 데이터를 파싱하여 필요한 정보를 추출하고 적절한 응답을 생성

	// 예시: 받은 데이터가 "체력:100, 점수:500, 쿠키타입:1" 형식이라면
	int hp, score, cookieType;
	if (sscanf_s(data, "체력:%d, 점수:%d, 쿠키타입:%d", &hp, &score, &cookieType) == 3) {
		// 데이터 처리 로직 추가
		// 예: 서버 콘솔에 출력
		printf("[클라이언트 데이터] 체력:%d, 점수:%d, 쿠키타입:%d\n", hp, score, cookieType);

		// 클라이언트에게 응답 보내기
		char response[BUFSIZE];
		sprintf_s(response, BUFSIZE, "서버에서 받은 데이터 처리 완료. 체력:%d, 점수:%d, 쿠키타입:%d", hp, score, cookieType);
		int retval = send(client_sock, response, (int)strlen(response), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}
	}
}

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 클라이언트와 데이터 통신
		while (1) {
			// 데이터 받기
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 받은 데이터 출력
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

			ProcessGameData(client_sock, buf);

			// 데이터 보내기
			retval = send(client_sock, buf, retval, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				break;
			}
		}

		// 소켓 닫기
		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));
	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}