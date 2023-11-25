#include "stdafx.h"
#include "Meteor.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"


CMeteor::CMeteor()
{
}


CMeteor::~CMeteor()
{
}

void CMeteor::Initialize(void)
{
	m_tInfo.fX = -10;
	m_tInfo.fY = -10;
	m_tInfo.fCX = 130;
	m_tInfo.fCY = 124;

	m_iHp = 1;
	m_fSpeed = 10.0f;
	m_bBullet = false;
	m_iCount = 0;
	m_tFrame.iFrameStart = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pa.bmp", L"Pa");//9개
}

const int && CMeteor::Update(void)
{
	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		m_tInfo.fX = OBJMGR->Get_Player()->Get_Info().fX + m_fSpeed;
		m_tInfo.fY = OBJMGR->Get_Player()->Get_Info().fY;
	}

	if (GetAsyncKeyState('W') && m_bBullet == false)
	{
		m_bBullet = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"1653348834ntg.mp3", SOUND_PLAYER, g_fSound);
	}

	if (m_bBullet == true)
	{
		m_fSpeed += -20;
		if (m_fSpeed < -1200)
		{
			m_bBullet = false;
			m_fSpeed = 0;
		}
	}



	if (m_iCount == 0 && GetAsyncKeyState('W'))
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 70 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 9)
		m_tFrame.iFrameStart = 9;

	return OBJ_NOEVENT;
}

void CMeteor::Late_Update(void)
{
	Update_Rect();
}

void CMeteor::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_tRect.left + iScrollX < 1000 && m_tRect.left + iScrollX > -100)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Pa");

		if (m_fSpeed < -160)
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
}

void CMeteor::Release(void)
{
}

void CMeteor::PlayerColiision(void)
{
}

void CMeteor::Set_Hp(void)
{
}
