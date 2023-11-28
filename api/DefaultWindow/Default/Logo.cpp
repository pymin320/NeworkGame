#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	OBJMGR->Release();

	m_tMouseInfo.fCX = 30;
	m_tMouseInfo.fCY = 30;

	m_tLogo.left = 200;
	m_tLogo.right = 520;
	m_tLogo.top = 350;
	m_tLogo.bottom = 500;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Page_Title.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/logo.bmp", L"Logo2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logodark.bmp", L"Logo3");
	CSoundMgr::Get_Instance()->PlaySoundW(L"00_Logo_Sound.wav", SOUND_BGM, g_fSound);
}

void CLogo::Update(void)
{
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);

	m_tMouseRect.left = LONG(m_tMouse.x - m_tMouseInfo.fCX);
	m_tMouseRect.right = LONG(m_tMouse.x + m_tMouseInfo.fCX);
	m_tMouseRect.top = LONG(m_tMouse.y - m_tMouseInfo.fCY);
	m_tMouseRect.bottom = LONG(m_tMouse.y + m_tMouseInfo.fCY);


}

void CLogo::Late_Update(void)
{
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Logo2");
	HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"Logo3");


	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	RECT	RC{ 0,0,0,0 };

	if (IntersectRect(&RC, &m_tMouseRect, &m_tLogo))
	{
		GdiTransparentBlt(hDC,
			int(220),	// 2,3 인자 :  복사받을 위치 X, Y
			int(350),
			int(320),
			int(156),
			hMemDC3,
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			320,			// 복사할 비트맵의 가로, 세로 길이
			156,
			RGB(255, 0, 200));
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
			CSceneMgr::Get_Instance()->Scene_Change(SC_Robby);

			return;
		}
	}
	else
	{
		GdiTransparentBlt(hDC,
			int(220),	// 2,3 인자 :  복사받을 위치 X, Y
			int(350),
			int(320),
			int(156),
			hMemDC2,
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			320,			// 복사할 비트맵의 가로, 세로 길이
			156,
			RGB(255, 0, 200));
	}

}

void CLogo::Release(void)
{
}
