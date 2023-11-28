#include "stdafx.h"
#include "Needle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CNeedle::CNeedle()
{
}

CNeedle::CNeedle(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


CNeedle::~CNeedle()
{
}

void CNeedle::Initialize(void)
{
	m_tInfo.fCX = 63;
	m_tInfo.fCY = 200;

	m_fJumpPower = 15;
	m_fJumpTime = 0;

	m_bSound = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Fork.bmp", L"Needle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Cat.bmp", L"Cat");
}

const int && CNeedle::Update(void)
{
	if (m_iHp == 0)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 7.5f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_tInfo.fX += 30;
		m_fJumpTime += 0.1f;
		if (!m_bSound)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_CrashWithPower.mp3", SOUND_MONSTER, g_fSound);
			m_bSound = true;
		}

		if (m_tInfo.fY < -300 || m_tInfo.fX < -200)
		{
			return OBJ_DEAD;
		}
	}

	return OBJ_NOEVENT;
}

void CNeedle::Late_Update(void)
{
	Update_Rect();
}

void CNeedle::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Needle");

	if (iScrollX < -12200)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cat");
		m_tInfo.fCX = 107;
	}

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		0,			// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));
}

void CNeedle::Release(void)
{
}
