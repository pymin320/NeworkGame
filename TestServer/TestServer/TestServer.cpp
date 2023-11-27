#include "Common.h"

#define SERVERPORT 9000
#define BUFSIZE    512

void ProcessGameData(SOCKET client_sock, const char* data)
{
	// ���⿡ Ŭ���̾�Ʈ�� ���� �����͸� ó���ϴ� ������ �߰�
	// ���� �����͸� �Ľ��Ͽ� �ʿ��� ������ �����ϰ� ������ ������ ����

	// ����: ���� �����Ͱ� "ü��:100, ����:500, ��ŰŸ��:1" �����̶��
	int hp, score, cookieType;
	if (sscanf_s(data, "ü��:%d, ����:%d, ��ŰŸ��:%d", &hp, &score, &cookieType) == 3) {
		// ������ ó�� ���� �߰�
		// ��: ���� �ֿܼ� ���
		printf("[Ŭ���̾�Ʈ ������] ü��:%d, ����:%d, ��ŰŸ��:%d\n", hp, score, cookieType);

		// Ŭ���̾�Ʈ���� ���� ������
		char response[BUFSIZE];
		sprintf_s(response, BUFSIZE, "�������� ���� ������ ó�� �Ϸ�. ü��:%d, ����:%d, ��ŰŸ��:%d", hp, score, cookieType);
		int retval = send(client_sock, response, (int)strlen(response), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}
	}
}

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

		// Ŭ���̾�Ʈ�� ������ ���
		while (1) {
			// ������ �ޱ�
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// ���� ������ ���
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

			ProcessGameData(client_sock, buf);

			// ������ ������
			retval = send(client_sock, buf, retval, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				break;
			}
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