#include "stdafx.h"
#include "DevilJellies.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScoreMgr.h"
#include "SoundMgr.h"


DevilJellies::DevilJellies()
{
}

DevilJellies::DevilJellies(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


DevilJellies::~DevilJellies()
{
}

void DevilJellies::Initialize(void)
{
	m_tInfo.fCX = 114;
	m_tInfo.fCY = 73;

	m_iCount = 0;
	m_tFrame.iFrameStart = 0;
	m_iJellyX = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilJellies.bmp", L"DevilJellies");
}

const int && DevilJellies::Update(void)
{
	if (m_iCount == 0)
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 70 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 4)
		m_tFrame.iFrameStart = 0;



	m_tInfo.fX += 1;

	if (m_iHp == 0)
	{
		CScoreMgr::Get_Instance()->Plus_Score(6500);
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetJelly.mp3", SOUND_EFFECT, g_fSound);
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void DevilJellies::Late_Update(void)
{
	Update_Rect();
}

void DevilJellies::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	if (m_tRect.left + iScrollX < 1000)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DevilJellies");
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iFrameStart * 114,		// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}

}

void DevilJellies::Release(void)
{
}
