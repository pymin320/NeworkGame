#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512

using namespace std;

CPlayer* player1 = new CPlayer();
CPlayer* player2 = new CPlayer();

DWORD WINAPI ProcessClient1(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];

	bool boolValue = false;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	//게임 시작 받기
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		//err_display("recv()");
	}

	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port),buf);
	
	memset(buf, 0, sizeof(buf));

	while (1) {
		if (!boolValue) {
			// 데이터 받기
			boolValue = player1->Recv_ReadyData(client_sock);

			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
			printf("쿠키타입: %d\n", player1->Get_CookieType());
			if (boolValue)
				player1->Set_PlayerReady(true);
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {
			CNetworkManager::Get_Instance()->Set_AllReady(true);
			
			player1->Send_ReadyData(client_sock, *player2);
			//임의로 클라1에 저장
			memset(buf, 0, sizeof(buf));

			// 데이터 받기
			retval = recv(client_sock, reinterpret_cast<char*>(&player1->m_splayerdata), sizeof(player1->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			player1->Set_PlayerData();
			if (player1->Get_Hp() >= 0 && player1->Get_Collide() == true)
				printf("[클라1] 체력: %d, 코인: %d, 점수: %d, 상태: %d\n 위치X값: %f, 위치Y값: %f, 충돌여부: %d\n",
					player1->Get_Hp(), player1->Get_Coin(), player1->Get_Score(), 
					player1->Get_State(), player1->Get_Posx(), player1->Get_Posy(),
					player1->Get_Collide());

			//상대 데이터 전송
			retval = send(client_sock, reinterpret_cast<char*>(&player2->m_splayerdata), sizeof(player2->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
				break;
			}
			else if (retval == 0)
				break;
		}
	}
	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));

	return 0;
}

DWORD WINAPI ProcessClient2(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];
	bool boolValue = false;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		//err_display("recv()");
	}

	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

	memset(buf, 0, sizeof(buf));
	while (1) {
		if (!boolValue) {
			// 데이터 받기
			boolValue = player2->Recv_ReadyData(client_sock);
			
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
			printf("쿠키타입: %d\n", player2->Get_CookieType());
			if (boolValue)
				player2->Set_PlayerReady(true);
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {
			CNetworkManager::Get_Instance()->Set_AllReady(true);

			player2->Send_ReadyData(client_sock, *player1);

			//임의로 클라1에 저장
			memset(buf, 0, sizeof(buf));

			// 데이터 받기
			retval = recv(client_sock, reinterpret_cast<char*>(&player2->m_splayerdata), sizeof(player2->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			player2->Set_PlayerData();
			if (player2->Get_Hp() >= 0 && player2->Get_Collide() == true)
				printf("[클라2] 체력: %d, 코인: %d, 점수: %d, 상태: %d, 위치X값: %f, 위치Y값: %f\n",
					player2->Get_Hp(), player2->Get_Coin(), player2->Get_Score(), 
					player2->Get_State(), player2->Get_Posx(), player2->Get_Posy(),
					player2->Get_Collide());

			//상대 데이터 전송
			retval = send(client_sock, reinterpret_cast<char*>(&player1->m_splayerdata), sizeof(player1->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
				break;
			}
			else if (retval == 0)
				break;
		}
	}
	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char* argv[])
{
	int retval;
	int ClientNum{};

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	//if (listen_sock == INVALID_SOCKET); //err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) //err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	//if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;

	int addrlen;
	char buf[BUFSIZE + 1];
	bool boolValue = false;
	HANDLE ClientThread1;
	HANDLE ClientThread2;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			//err_display("accept()");
			//break;
		}

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// Thread 생성
		++ClientNum;
		if (1 == ClientNum) {
			//player1 = new CPlayer();
			player1->Set_ClientNum(ClientNum);
			ClientThread1 = CreateThread(NULL, 0, ProcessClient1,
				(LPVOID)client_sock, 0, NULL);
			if (ClientThread1 == NULL) { closesocket(client_sock); }
			else { CloseHandle(ClientThread1); }
		}
		else if (2 == ClientNum) {
			//player2 = 
			player2->Set_ClientNum(ClientNum);
			ClientThread2 = CreateThread(NULL, 0, ProcessClient2,
				(LPVOID)client_sock, 0, NULL);
			if (ClientThread2 == NULL) { closesocket(client_sock); }
			else { CloseHandle(ClientThread2); }
		}
	}
	// 소켓 닫기
	closesocket(listen_sock);

	delete player1;
	delete player2;
	// 윈속 종료
	WSACleanup();
	return 0;

}