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
float g_fSound = 1.f;


CMainGame::CMainGame()
	:m_dwTime(GetTickCount())
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
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

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