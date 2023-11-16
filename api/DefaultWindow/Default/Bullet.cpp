#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CBullet::CBullet()
{
}



CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fX = -10;
	m_tInfo.fY = -10;
	m_tInfo.fCX = 60;
	m_tInfo.fCY = 60;

	m_iHp = 1;
	m_fSpeed = 10.0f;
	m_bBullet = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Jellies");
}

const int && CBullet::Update(void)
{
	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		m_tInfo.fX = OBJMGR->Get_Player()->Get_Info().fX + m_fSpeed;
		m_tInfo.fY = OBJMGR->Get_Player()->Get_Info().fY;
	}

	if (GetAsyncKeyState('Q') && m_bBullet == false)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"shotgun_shot_01.wav", SOUND_PLAYER, g_fSound);
		m_bBullet = true;
	}

	if (m_bBullet == true)
	{
		m_fSpeed += -20;
		if (m_fSpeed < -600)
		{
			m_bBullet = false;
			m_fSpeed = 0;
		}
	}


	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	Update_Rect();
}

void CBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_tRect.left + iScrollX < 1000 && m_tRect.left + iScrollX > -100)
	{

		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Jellies");


		if (m_fSpeed < -160)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY + 10),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				1975,			// 비트맵 출력 시작 좌표, X,Y
				1800,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
	}
}

void CBullet::Release(void)
{
}

void CBullet::PlayerColiision(void)
{
}

void CBullet::Set_Hp(void)
{
}
