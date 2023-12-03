#include "Common.h"
#include "NetworkManager.h"
#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512

using namespace std;

CPlayer* player1 = new CPlayer();
CPlayer* player2 = new CPlayer();

// Ŭ���̾�Ʈ�κ��� �����͸� �޴� �Լ�
int ReceiveData(SOCKET sock, char* buf, int bufsize)
{
	int retval = recv(sock, buf, bufsize, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}
	return retval;
}

// Ŭ���̾�Ʈ���� �����͸� ������ �Լ�
int SendData(SOCKET sock, const char* data, int dataSize)
{
	int retval = send(sock, data, dataSize, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	return retval;
}

DWORD WINAPI ProcessClient1(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];

	bool boolValue = false;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	//���� ���� �ޱ�
	retval = ReceiveData(client_sock, buf, BUFSIZE);
	if (retval == 0 || retval == SOCKET_ERROR) {
		closesocket(client_sock);
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));
		return 0;
	}

	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port),buf);
	
	memset(buf, 0, sizeof(buf));

	while (1) {
		if (!boolValue) {
			// ������ �ޱ�
			retval = ReceiveData(client_sock, buf, sizeof(bool));
			if (retval == 0 || retval == SOCKET_ERROR) {
				break;
			}

			// buf�� ����� bool �� ��ȯ
			boolValue = buf[0] != '0'; // '0'�� �ƴϸ� true, '0'�̸� false
			// bool ���� ���ڿ��� ��ȯ�Ͽ� ���
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
			if (boolValue)
				player1->Set_PlayerReady(true);
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {
			CNetworkManager::Get_Instance()->Set_AllReady(true);
			// ������ ������
			buf[0] = static_cast<char>(CNetworkManager::Get_Instance()->Get_AllReady());
			retval = SendData(client_sock, &buf[0], sizeof(bool));
			if (retval == SOCKET_ERROR) {
				break;
			}

			//���Ƿ� Ŭ��1�� ����
			memset(buf, 0, sizeof(buf));

			// ������ �ޱ�
			retval = ReceiveData(client_sock, reinterpret_cast<char*>(&player1->m_splayerdata), sizeof(player1->m_splayerdata));
			if (retval == 0 || retval == SOCKET_ERROR) {
				break;
			}

			player1->Set_PlayerData();
			if (player1->Get_Hp() >= 0)
				printf("[Ŭ��1] ü��: %d, ����: %d, ����: %d, Posx: %d, Posy: %d\n", 
					player1->Get_Hp(), player1->Get_Coin(), player1->Get_Score(), player1->Get_Posx(), player1->Get_Posy());

			//��� ������ ����
			retval = SendData(client_sock, reinterpret_cast<char*>(&player2->m_splayerdata), sizeof(player2->m_splayerdata));
			if (retval == SOCKET_ERROR) {
				break;
			}
		}
	}
	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
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

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}

	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

	memset(buf, 0, sizeof(buf));
	while (1) {
		if (!boolValue) {
			// ������ �ޱ�
			retval = ReceiveData(client_sock, buf, sizeof(bool));
			if (retval == 0 || retval == SOCKET_ERROR) {
				break;
			}

			// buf�� ����� bool �� ��ȯ
			boolValue = buf[0] != '0'; // '0'�� �ƴϸ� true, '0'�̸� false
			// bool ���� ���ڿ��� ��ȯ�Ͽ� ���
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
			if (boolValue)
				player2->Set_PlayerReady(true);
		}

		if (player1->Get_PlayerReady() && player2->Get_PlayerReady()) {
			CNetworkManager::Get_Instance()->Set_AllReady(true);

			// ������ ������
			buf[0] = static_cast<char>(CNetworkManager::Get_Instance()->Get_AllReady());
			retval = SendData(client_sock, &buf[0], sizeof(bool));
			if (retval == SOCKET_ERROR) {
				break;
			}

			//���Ƿ� Ŭ��1�� ����
			memset(buf, 0, sizeof(buf));

			// ������ �ޱ�
			retval = ReceiveData(client_sock, reinterpret_cast<char*>(&player2->m_splayerdata), sizeof(player2->m_splayerdata));
			if (retval == 0 || retval == SOCKET_ERROR) {
				break;
			}

			player2->Set_PlayerData();
			if (player2->Get_Hp() >= 0)
				printf("[Ŭ��2] ü��: %d, ����: %d, ����: %d, Posx: %d, Posy: %d\n", 
					player2->Get_Hp(), player2->Get_Coin(), player2->Get_Score(), player2->Get_Posx(), player2->Get_Posy());

			//��� ������ ����
			retval = SendData(client_sock, reinterpret_cast<char*>(&player1->m_splayerdata), sizeof(player1->m_splayerdata));
			if (retval == SOCKET_ERROR) {
				break;
			}
		}
	}
	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char* argv[])
{
	int retval;
	int ClientNum{};

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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

	// ������ ��ſ� ����� ����
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
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

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
	// ���� �ݱ�
	closesocket(listen_sock);

	delete player1;
	delete player2;
	// ���� ����
	WSACleanup();
	return 0;

}