#include "stdafx.h"
#include "Heal.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CHeal::CHeal()
{
}


CHeal::~CHeal()
{
}

void CHeal::Initialize(void)
{
	m_tInfo.fX = 12200;
	m_tInfo.fY = 400;

	m_tInfo.fCX = 145;
	m_tInfo.fCY = 150;

	m_tFrame.iFrameStart = 0;
	m_iCount = 0;

	m_iHp = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Heal");


}

const int && CHeal::Update(void)
{
	if (m_iHp <= 0)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"tr0011_get_coin_lev.wav", SOUND_EFFECT, g_fSound);
		return OBJ_DEAD;
	}


	if (m_iCount == 0)
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 100 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 4)
		m_tFrame.iFrameStart = 0;

	return OBJ_NOEVENT;
}

void CHeal::Late_Update(void)
{
	Update_Rect();
}

void CHeal::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Heal");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		int(1485 + m_tFrame.iFrameStart * m_tInfo.fCX ),		// 비트맵 출력 시작 좌표, X,Y
		1300,
		(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));

}

void CHeal::Release(void)
{
}

