#include "stdafx.h"
#include "Jelly.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ScoreMgr.h"
#include "SoundMgr.h"

CJelly::CJelly()
{
}

CJelly::CJelly(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;

}


CJelly::~CJelly()
{
}

void CJelly::Initialize(void)
{
	m_iJellyType = CScoreMgr::Get_Instance()->Get_JellyType();

	if (m_iJellyType == BASE)
		m_iJellyScore = 30;

	else if (m_iJellyType == NORMAL)
		m_iJellyScore = 110;

	else if (m_iJellyType == RARE)
		m_iJellyScore = 300;


	m_tInfo.fCX = 40;
	m_tInfo.fCY = 60;

	if (m_iJellyType == RARE)
	{
		m_tInfo.fCX = 60;
	}

	m_iHp = 1;
	m_fAngle = 0;
	m_fSpeed = 10.0f;

	m_bScore = false;

	m_JellyCount = 0;

	m_bJellyDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Jellies");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect.bmp", L"effect");
}

const int && CJelly::Update(void)
{
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

void CJelly::Late_Update(void)
{
	Update_Rect();
}

void CJelly::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_tRect.left + iScrollX < 1000 && m_tRect.left + iScrollX > -100)
	{

		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Jellies");
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"effect");
		if (m_iHp == 0)
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
		else {

			if (m_iJellyType == BASE)
			{
				GdiTransparentBlt(hDC,
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
					int(m_tInfo.fCX),
					int(m_tInfo.fCY),
					hMemDC,
					0,			// 비트맵 출력 시작 좌표, X,Y
					1691,
					(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tInfo.fCY,
					RGB(255, 0, 200));
			}

			else if (m_iJellyType == NORMAL)
			{
				GdiTransparentBlt(hDC,
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
					int(m_tInfo.fCX),
					int(m_tInfo.fCY),
					hMemDC,
					200,			// 비트맵 출력 시작 좌표, X,Y
					1691,
					(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tInfo.fCY,
					RGB(255, 0, 200));
			}
			else if (m_iJellyType == RARE)
			{
				GdiTransparentBlt(hDC,
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
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
}

void CJelly::Release(void)
{
}

void CJelly::PlayerColiision(void)
{
	m_iHp = 0;
	if (!m_bScore)
	{
		CScoreMgr::Get_Instance()->Plus_Score(m_iJellyScore);
		m_bScore = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetJelly.mp3", SOUND_EFFECT, g_fSound);
	}
}

void CJelly::Set_Hp(void)
{
}

void CJelly::PetColiision(INFO _Pet)
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
			if (!m_bScore)
			{
					CScoreMgr::Get_Instance()->Plus_Score(m_iJellyScore);
					m_bScore = true;
					CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_GetJelly.mp3", SOUND_EFFECT, g_fSound);
			}
		}
	}

}
