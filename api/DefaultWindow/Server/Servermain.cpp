#include "Common.h"
#include "NetworkManager.h"
#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512

CPlayer player1; //player1
CPlayer player2; //player2


int main(int argc, char* argv[])
{
	int retval;

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
		
		//���� ���� �ޱ�
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port),buf);
		
		memset(buf, 0, sizeof(buf));
		// Ŭ���̾�Ʈ�� ������ ��� (��� ����ؾ� �ϴ� �κ�)
		while (1) {
			if (!boolValue) {
				// ������ �ޱ�
				retval = recv(client_sock, buf, sizeof(bool), 0);
				if (retval == SOCKET_ERROR) {
					err_display("recv()");
					break;
				}
				else if (retval == 0)
					break;

				// buf�� ����� bool �� ��ȯ
				boolValue = buf[0] != '0'; // '0'�� �ƴϸ� true, '0'�̸� false
				// bool ���� ���ڿ��� ��ȯ�Ͽ� ���
				printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), boolValue ? "true" : "false");
				if (boolValue) {
					player1.Set_PlayerReady(true);			//������ �ΰ��� ����� �����ؼ� ���� �׸�
					player2.Set_PlayerReady(true);			//�̷� ��������
				}//���Ƿ� ����� ��
			}

			if (player1.Get_PlayerReady() && player2.Get_PlayerReady()) {
				CNetworkManager::Get_Instance()->Set_AllReady(true);
			}

			// ������ ������
			buf[0] = static_cast<char>(CNetworkManager::Get_Instance()->Get_AllReady());
			retval = send(client_sock, &buf[0], sizeof(bool), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				break;
			}

			//���Ƿ� Ŭ��1�� ����
			memset(buf, 0, sizeof(buf));
			
			// ������ �ޱ�
			retval = recv(client_sock, reinterpret_cast<char*>(&player1.m_splayerdata), sizeof(player1.m_splayerdata), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;
			player1.Set_PlayerData();
			printf("ü��: %d, ����: %d, ����: %d, ��� ü��: %d \n",player1.Get_Hp(), player1.Get_Coin(), player1.Get_Score(),player1.Get_OppHp());
		}

		// ���� �ݱ�
		closesocket(client_sock);
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));
	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}
