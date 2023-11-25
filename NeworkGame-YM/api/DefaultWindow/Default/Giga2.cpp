#include "stdafx.h"
#include "Giga2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CGiga2::CGiga2()
{
}


CGiga2::~CGiga2()
{
}

void CGiga2::Initialize(void)
{
	m_tInfo.fX = 27000;
	m_tInfo.fY = 450;

	m_tInfo.fCX = 80;
	m_tInfo.fCY = 87;

	m_iHp = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Giga.bmp", L"Giga");
}

const int && CGiga2::Update(void)
{
	if (m_iHp <= 0)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"tr0011_get_coin_lev.wav", SOUND_EFFECT, g_fSound);
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CGiga2::Late_Update(void)
{
	Update_Rect();
}

void CGiga2::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Giga");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		0,		// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));
}

void CGiga2::Release(void)
{
}
