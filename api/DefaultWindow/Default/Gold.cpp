#include "stdafx.h"
#include "Gold.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScoreMgr.h"
#include "SoundMgr.h"

CGold::CGold()
{
}

CGold::CGold(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


CGold::~CGold()
{
}

void CGold::Initialize(void)
{
	m_tInfo.fCX = 58;
	m_tInfo.fCY = 67;

	m_iCoinFrame = 0;
	m_iCount = 0;
	m_tFrame.iFrameStart = 0;
	m_bCoin = false;
	m_fAngle = 0;
	m_iHp = 1;
	m_fSpeed = 10.0f;


	m_JellyCount = 0;

	m_bJellyDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Gold.bmp", L"Gold");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect.bmp", L"effect");
}

const int && CGold::Update(void)
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



	if (m_iHp == 0 && m_bJellyDead == false)
	{
		m_JellyCount = GetTickCount();
		m_bJellyDead = true;
	}
	else if (m_bJellyDead == true && m_JellyCount + 1100 < GetTickCount())
	{
		return OBJ_DEAD;
	}


	return OBJ_NOEVENT;
}

void CGold::Late_Update(void)
{
	Update_Rect();
}

void CGold::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_iHp == 0)
	{
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"effect");
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(49),
			int(54 - 20),
			hMemDC2,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)49,		// 복사할 비트맵의 가로, 세로 길이
			(int)54 - 20,
			RGB(255, 0, 200));
	}
	else if (m_tRect.left + iScrollX < 1000)
	{

		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Gold");
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iFrameStart * 58,		// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}
}

void CGold::Release(void)
{
}

void CGold::PlayerColiision(void)
{
	m_iHp = 0;
	if (!m_bCoin)
	{
		CScoreMgr::Get_Instance()->Plus_Coin(5);
		m_bCoin = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetGoldJelly.mp3", SOUND_EFFECT, g_fSound);
	}
}

void CGold::Set_Hp(void)
{
}

void CGold::PetColiision(INFO _Pet)
{
	if (m_iHp > 0)
	{
		float		fWidth = _Pet.fX - m_tInfo.fX;
		float		fHeight = _Pet.fY - m_tInfo.fY;

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float		fRadian = acosf(fWidth / fDiagonal);

		m_fAngle = (fRadian * 180.f) / PI;

		if (_Pet.fY > m_tInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += m_fSpeed * cosf((m_fAngle)* PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle)* PI / 180.f);

		if (_Pet.fX + 100 >= m_tInfo.fX && _Pet.fX - 100 <= m_tInfo.fX && _Pet.fY + 100 >= m_tInfo.fY && _Pet.fY - 100 <= m_tInfo.fY)
		{
			m_iHp = 0;
			if (!m_bCoin)
			{
				CScoreMgr::Get_Instance()->Plus_Coin(5);
				m_bCoin = true;
				CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetGoldJelly.mp3", SOUND_EFFECT, g_fSound);
			}
		}
	}
}
