#include "stdafx.h"
#include "MainGame.h"
#include "CAbstractFactory.h"
#include "JellyFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "BackGround.h"
#include "Scenemgr.h"
#include "SoundMgr.h"
#include "..\..\Common.h"

float g_fSound = 1.f;

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
	m_fTime = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Oven.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map2.bmp", L"Ground");
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	HDC hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_hDC, 0, 0, 1200, WINCY, hMemDC, 0, 0, SRCCOPY);
	BitBlt(hMemDC, 0, 0, 1200, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hMemDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}

int main()
{
	// 게임 초기화
	CMainGame mainGame;
	mainGame.Initialize();

	// 윈속 초기화
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize winsock" << std::endl;
		return -1;
	}

	// 소켓 생성
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "Failed to create socket" << std::endl;
		WSACleanup();
		return -1;
	}

	// 서버 주소 설정
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;

	if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
		std::cerr << "Invalid address" << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}

	serverAddress.sin_port = htons(9000);  // 테스트 서버의 포트 번호

	// 서버에 연결
	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "Failed to connect to server" << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}

	std::cout << "Connected to server" << std::endl;

	// 서버로 메시지 전송
	const char* message = "Game Has Started!";
	send(clientSocket, message, strlen(message), 0);

	// 서버로부터 응답 수신
	char buffer[1024];
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesReceived > 0) {
		buffer[bytesReceived] = '\0';
		std::cout << "Received from server: " << buffer << std::endl;
	}
	else {
		std::cerr << "Failed to receive response from server" << std::endl;
	}

	// 소켓 닫기
	closesocket(clientSocket);

	// 윈속 종료
	WSACleanup();

	return 0;
}