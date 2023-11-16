#include "stdafx.h"
#include "Frog.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CFrog::CFrog()
{
}

CFrog::CFrog(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


CFrog::~CFrog()
{
}

void CFrog::Initialize(void)
{
	m_tInfo.fCX = 170;
	m_tInfo.fCY = 475;

	m_fJumpPower = 15;
	m_fJumpTime = 0;

	m_bSound = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/epN01_tm02_sdA.bmp", L"epN01_tm02_sdA");
}

const int && CFrog::Update(void)
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
	}

	return OBJ_NOEVENT;
}

void CFrog::Late_Update(void)
{
	Update_Rect();
}

void CFrog::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"epN01_tm02_sdA");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		170,		
		0,
		(int)m_tInfo.fCX,	
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));


}

void CFrog::Release(void)
{
}
