#include "stdafx.h"
#include "Fork.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CFork::CFork()
{
}

CFork::CFork(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


CFork::~CFork()
{
}

void CFork::Initialize(void)
{
	m_tInfo.fCX = 134;
	m_tInfo.fCY = 482;
	m_fJumpPower = 15;
	m_fJumpTime = 0;
	m_bSound = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StickP.bmp", L"StickP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/epN01_tm02_sdA.bmp", L"epN01_tm02_sdA");
}

const int && CFork::Update(void)
{
	if (m_iHp == 0)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 15.5f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_tInfo.fX += 30;
		m_fJumpTime += 0.1f;
		if (!m_bSound)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_CrashWithPower.mp3", SOUND_MONSTER, g_fSound);
			m_bSound = true;
		}
	}

	return OBJ_NOEVENT;
}

void CFork::Late_Update(void)
{
	Update_Rect();
}

void CFork::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"StickP");

	if (iScrollX < -12200)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"epN01_tm02_sdA");
		m_tInfo.fCX = 170;
		m_tInfo.fCY = 475;
	}

	if (m_tRect.left + iScrollX < 1000)
	{
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
}

void CFork::Release(void)
{
}

void CFork::Dead(void)
{
	m_iHp = 0;
}

