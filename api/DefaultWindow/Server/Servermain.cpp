#include "Common.h"
#include "NetworkManager.h"
#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512

CPlayer player1; //player1
CPlayer player2; //player2

<<<<<<< Updated upstream
=======
HANDLE hEvent1, hEvent2;
CRITICAL_SECTION cs;

CPlayer* player1 = new CPlayer();
CPlayer* player2 = new CPlayer();

int check1, check2;
bool playerturn = true;

DWORD WINAPI ProcessClient1(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];

	bool boolValue = false;
	bool boolReady = false;

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
			printf("쿠키타입: %d, 최대체력: %d\n", player1->Get_CookieType(), player1->Get_MaxHp());
			if (boolValue) {
				EnterCriticalSection(&cs);
				player1->Set_PlayerReady(true);
				playerturn = false;
				LeaveCriticalSection(&cs);
			}
		}

		EnterCriticalSection(&cs);
		if (!playerturn) {
			LeaveCriticalSection(&cs);
			continue;
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {
			if (!boolReady) {
				CNetworkManager::Get_Instance()->Set_AllReady(true);
				player1->Send_ReadyData(client_sock, *player2);
				boolReady = true;
			}
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
			++check1;
			if (player1->Get_Hp() >= 0) {
				//printf("[클라1 - %d] 체력: %d, 코인: %d, 점수: %d, 상태: %d, 위치X값: %f, 위치Y값: %f\n",
					//check1, player1->Get_Hp(), player1->Get_Coin(), player1->Get_Score(), player1->Get_State(), player1->Get_Posx(), player1->Get_Posy());
			}
			//상대 데이터 전송
			retval = send(client_sock, reinterpret_cast<char*>(&player2->m_splayerdata), sizeof(player2->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
				break;
			}
			else if (retval == 0)
				break;
			EnterCriticalSection(&cs);
			playerturn = false;
			LeaveCriticalSection(&cs);
		}
		LeaveCriticalSection(&cs);
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
	bool boolReady = false;

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
			printf("쿠키타입: %d, 최대체력: %d\n", player2->Get_CookieType(), player2->Get_MaxHp());
			if (boolValue) {
				EnterCriticalSection(&cs);
				player2->Set_PlayerReady(true);
				playerturn = true; 
				LeaveCriticalSection(&cs); 
			}
		}

		EnterCriticalSection(&cs);
		if (playerturn) {
			LeaveCriticalSection(&cs);
			continue; 
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {

			if (!boolReady) {
				CNetworkManager::Get_Instance()->Set_AllReady(true);
				player2->Send_ReadyData(client_sock, *player1);
				boolReady = true;
			}
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
			++check2;
			if (player2->Get_Hp() >= 0) {
				//printf("[클라2 - %d] 체력: %d, 코인: %d, 점수: %d, 상태: %d, 위치X값: %f, 위치Y값: %f\n",
					//check2, player2->Get_Hp(), player2->Get_Coin(), player2->Get_Score(), player2->Get_State(), player2->Get_Posx(), player2->Get_Posy());
			}
			//상대 데이터 전송
			retval = send(client_sock, reinterpret_cast<char*>(&player1->m_splayerdata), sizeof(player1->m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
				break;
			}
			else if (retval == 0)
				break;
			EnterCriticalSection(&cs); // 임계 영역 진입
			playerturn = true; // 플레이어 1의 차례로 변경
			LeaveCriticalSection(&cs); // 임계 영역 빠져나옴
		}
		LeaveCriticalSection(&cs); // 임계 영역 빠져나옴
	}
	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));

	return 0;
}
>>>>>>> Stashed changes

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
	bool boolValue = false;
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
		
		//게임 시작 받기
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port),buf);
		
		memset(buf, 0, sizeof(buf));
		// 클라이언트와 데이터 통신 (계속 통신해야 하는 부분)
		while (1) {
			if (!boolValue) {
				// 데이터 받기
				retval = recv(client_sock, buf, sizeof(bool), 0);
				if (retval == SOCKET_ERROR) {
					err_display("recv()");
					break;
				}
				else if (retval == 0)
					break;

				// buf에 저장된 bool 값 변환
				boolValue = buf[0] != '0'; // '0'이 아니면 true, '0'이면 false
				// bool 값을 문자열로 변환하여 출력
				printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
				if (boolValue) {
					player1.Set_PlayerReady(true);			//쓰레드 두개로 만들시 구분해서 넣을 항목
					player2.Set_PlayerReady(true);			//미래 수정사항
				}//임의로 만들어 둠
			}

			if (player1.Get_PlayerReady() && player2.Get_PlayerReady()) {
				CNetworkManager::Get_Instance()->Set_AllReady(true);
			}

			// 데이터 보내기
			buf[0] = static_cast<char>(CNetworkManager::Get_Instance()->Get_AllReady());
			retval = send(client_sock, &buf[0], sizeof(bool), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				break;
			}

			//임의로 클라1에 저장
			memset(buf, 0, sizeof(buf));
			
			// 데이터 받기
			retval = recv(client_sock, reinterpret_cast<char*>(&player1.m_splayerdata), sizeof(player1.m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;
			player1.Set_PlayerData();
			printf("체력: %d, 코인: %d, 점수: %d, 상대 체력: %d \n",player1.Get_Hp(), player1.Get_Coin(), player1.Get_Score(),player1.Get_OppHp());
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
