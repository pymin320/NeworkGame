#include "stdafx.h"
#include "Air.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"



CAir::CAir()
{
}

CAir::CAir(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


CAir::~CAir()
{
}

void CAir::Initialize(void)
{
	m_tInfo.fCX = 162;
	m_tInfo.fCY = 30;

	m_fJumpPower = 20;
	m_fJumpTime = 0;
	m_iAirspeed = -3;
	m_bSound = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/air.bmp", L"air");
}

const int && CAir::Update(void)
{
	if (m_iHp == 0)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 7.5f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_tInfo.fX += 30;
		m_fJumpTime += 0.3f;
		if (!m_bSound)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_MONSTER, g_fSound);
			m_bSound = true;
		}

		if (m_tInfo.fY < -300 || m_tInfo.fX < -200)
		{
			return OBJ_DEAD;
		}
	}
}

void CAir::Late_Update(void)
{
	Update_Rect();

	m_fTop = LONG(m_tInfo.fY - (94.f * 0.5f));
}

void CAir::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_tRect.left + iScrollX < 1200)
		m_tInfo.fX = LONG(m_iAirspeed + m_tInfo.fX);
	if (m_tRect.left + iScrollX < 1200)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"air");
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_fTop + iScrollY),
			int(m_tInfo.fCX),
			int(94),
			hMemDC,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)94,
			RGB(255, 0, 200));
	}
}

void CAir::Release(void)
{
}
