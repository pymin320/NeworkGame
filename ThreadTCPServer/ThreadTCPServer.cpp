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

// 진행도 표시용
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
	// 데이터 받기(고정 길이)
	retval = recv(client_sock, (char*)&len, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	// 데이터 받기(가변 길이)
	retval = recv(client_sock, buf, len, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	return true;
}

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID* arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg[0];
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE];

	//과제용 추가
	int len; // 고정길이 데이터

	// 파일 정보들
	FILE* File;
	string FileName;

	// 이 스레드가 생성 될때 번호
	int ThisThreadNumber = (int)arg[1];
	FileSize[ThisThreadNumber] = 1;
	FileSizeSum[ThisThreadNumber] = 0;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr *)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	// 파일 이름 불러오기
	if (RecvMessageFixedVariable(client_sock, len, buf))
	{
		FileName = buf;
		FileName[len] = '\0';

		File = fopen(FileName.c_str(), "wb");
		printf("\n[TCP 서버] 파일 이름: %s\n", FileName.data());

		memset(buf, 0, BUFSIZE);
	}
	else
	{
		exit(1);
	}

	// 파일 크기 불러오기
	if (RecvMessageFixedVariable(client_sock, len, buf))
	{
		FileSize[ThisThreadNumber] = strtoull(buf, NULL, 10);
		memset(buf, 0, BUFSIZE);
	}
	else
	{
		exit(1);
	}

	// 클라이언트와 데이터 통신
	while (RecvMessageFixedVariable(client_sock, len, buf))
	{
		fwrite(buf, len, 1, File);
		FileSizeSum[ThisThreadNumber] += len;
		// gotoxy(0, 5 + ThisThreadNumber * 3);
		// cout << "받는 중 " << int(((double)FileSizeSum[ThisThreadNumber] / FileSize) * 100) << "%..." << endl;
		memset(buf, 0, BUFSIZE);
	}

	// 파일 닫기
	fclose(File);

	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
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
			printf("[%d]번 스레드 %d%% 진행 완료.\n", i, int(((double)FileSizeSum[i] / FileSize[i]) * 100));
		}
		Sleep(50);
	}
}

int main(int argc, char *argv[])
{
	std::fill_n(FileSize, MAXTHREADNUM, 1);
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
	retval = bind(listen_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;

	system("cls");
	// 진행 상황표 스레드 생성
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

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 사용가능한 스레드 번호
		int ThreadNum = 0;

		// 쓸 수 있는 배열 공간 탐색
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

		// 스레드 생성
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessClient,
			ThreadArg, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
