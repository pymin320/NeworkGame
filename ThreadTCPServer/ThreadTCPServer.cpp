#include "..\..\Common.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <vector>

#define SERVERPORT 9000
#define BUFSIZE    1024

#define MAXTHREADNUM 8

using std::cout;
using std::endl;
using std::string;
namespace fs = std::filesystem;

// ���൵ ǥ�ÿ�
uintmax_t FileSizeSum[MAXTHREADNUM]{  };
uintmax_t FileSize[MAXTHREADNUM]{  };
std::vector<bool> bUsingThread (MAXTHREADNUM, false);

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

bool RecvMessageFixedVariable(const SOCKET& client_sock, int& len, char* buf)
{
	int retval;
	// ������ �ޱ�(���� ����)
	retval = recv(client_sock, (char*)&len, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	// ������ �ޱ�(���� ����)
	retval = recv(client_sock, buf, len, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	return true;
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID* arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg[0];
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE];

	//������ �߰�
	int len; // �������� ������

	// ���� ������
	FILE* File;
	string FileName;

	// �� �����尡 ���� �ɶ� ��ȣ
	int ThisThreadNumber = (int)arg[1];
	FileSize[ThisThreadNumber] = 1;
	FileSizeSum[ThisThreadNumber] = 0;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr *)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	// ���� �̸� �ҷ�����
	if (RecvMessageFixedVariable(client_sock, len, buf))
	{
		FileName = buf;
		FileName[len] = '\0';

		File = fopen(FileName.c_str(), "wb");
		printf("\n[TCP ����] ���� �̸�: %s\n", FileName.data());

		memset(buf, 0, BUFSIZE);
	}
	else
	{
		exit(1);
	}

	// ���� ũ�� �ҷ�����
	if (RecvMessageFixedVariable(client_sock, len, buf))
	{
		FileSize[ThisThreadNumber] = strtoull(buf, NULL, 10);
		memset(buf, 0, BUFSIZE);
	}
	else
	{
		exit(1);
	}

	// Ŭ���̾�Ʈ�� ������ ���
	while (RecvMessageFixedVariable(client_sock, len, buf))
	{
		fwrite(buf, len, 1, File);
		FileSizeSum[ThisThreadNumber] += len;
		// gotoxy(0, 5 + ThisThreadNumber * 3);
		// cout << "�޴� �� " << int(((double)FileSizeSum[ThisThreadNumber] / FileSize) * 100) << "%..." << endl;
		memset(buf, 0, BUFSIZE);
	}

	// ���� �ݱ�
	fclose(File);

	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));

	bUsingThread[ThisThreadNumber] = false;

	return 0;
}

DWORD WINAPI ShowProgress()
{
	while (1)
	{
		int PrintNum = 0;
		gotoxy(0, 0);
		for (int i = 0; i < MAXTHREADNUM; i++)
		{
			printf("[%d]�� ������ %d%% ���� �Ϸ�.\n", i, int(((double)FileSizeSum[i] / FileSize[i]) * 100));
		}
		Sleep(50);
	}
}

int main(int argc, char *argv[])
{
	std::fill_n(FileSize, MAXTHREADNUM, 1);
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
	retval = bind(listen_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;

	system("cls");
	// ���� ��Ȳǥ ������ ����
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ShowProgress,
		NULL, 0, NULL);

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// ��밡���� ������ ��ȣ
		int ThreadNum = 0;

		// �� �� �ִ� �迭 ���� Ž��
		for (int i = 0; i < MAXTHREADNUM; i++)
		{
			if (!bUsingThread[i])
			{
				ThreadNum = i;
				bUsingThread[i] = true;
				break;
			}
		}
		LPVOID ThreadArg[2]{ (LPVOID)client_sock, (LPVOID)ThreadNum };

		// ������ ����
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessClient,
			ThreadArg, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}
