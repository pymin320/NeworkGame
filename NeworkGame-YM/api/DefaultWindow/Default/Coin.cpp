#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScoreMgr.h"
#include "SoundMgr.h"


CCoin::CCoin()
{
}

CCoin::CCoin(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


CCoin::~CCoin()
{
}

void CCoin::Initialize(void)
{
	m_tInfo.fCX = 49;
	m_tInfo.fCY = 54;




	m_iCoinFrame = 0;
	m_iCount = 0;
	m_tFrame.iFrameStart = 0;
	m_bCoin = false;
	m_fAngle = 0;
	m_iHp = 1;
	m_fSpeed = 10.0f;

	m_JellyCount = 0;

	m_bJellyDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SilverCoin.bmp", L"Silver");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect.bmp", L"effect");
}

const int && CCoin::Update(void)
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

void CCoin::Late_Update(void)
{

	Update_Rect();
}

void CCoin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	

	if (m_tRect.left + iScrollX < 1000 && m_tRect.left + iScrollX > 0)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Silver");
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"effect");
		if (m_iHp == 0 && m_tRect.left + iScrollX > 0)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY - 20),
				hMemDC2,
				0,			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY - 20,
				RGB(255, 0, 200));
		}
		else if (m_tRect.left + iScrollX < 1000 && m_tRect.left + iScrollX > 0)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top + iScrollY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				m_tFrame.iFrameStart * 49,		// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
	}

}

void CCoin::Release(void)
{
}

void CCoin::PlayerColiision(void)
{
	m_iHp = 0;
	if (!m_bCoin)
	{
		CScoreMgr::Get_Instance()->Plus_Coin(1);
		m_bCoin = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetCoinJelly.mp3", SOUND_EFFECT, g_fSound);
	}
}

void CCoin::Set_Hp(void)
{
}

void CCoin::PetColiision(INFO _Pet)
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

		if (_Pet.fX + 70 >= m_tInfo.fX && _Pet.fX - 70 <= m_tInfo.fX && _Pet.fY + 70 >= m_tInfo.fY && _Pet.fY - 70 <= m_tInfo.fY)
		{
			m_iHp = 0;
			if (!m_bCoin)
			{
				CScoreMgr::Get_Instance()->Plus_Coin(1);
				m_bCoin = true;
				CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetCoinJelly.mp3", SOUND_EFFECT, g_fSound);
			}
		}
	}

}