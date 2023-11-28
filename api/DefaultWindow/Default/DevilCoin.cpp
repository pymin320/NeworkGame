#include "stdafx.h"
#include "DevilCoin.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ScoreMgr.h"
#include "SoundMgr.h"


CDevilCoin::CDevilCoin()
{
}

CDevilCoin::CDevilCoin(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


CDevilCoin::~CDevilCoin()
{
	Release();
}

void CDevilCoin::Initialize(void)
{
	m_tInfo.fCX = 90;
	m_tInfo.fCY = 104;

	m_iCoinFrame = 0;
	m_iCount = 0;
	m_tFrame.iFrameStart = 0;
	m_bCoin = false;
	m_iHp = 1;
	m_fSpeed = 10.0f;

	m_fAngle = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilCoin.bmp", L"DevilCoin");
}

const int && CDevilCoin::Update(void)
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

	if (m_tFrame.iFrameStart == 3)
		m_tFrame.iFrameStart = 0;



	return OBJ_NOEVENT;
}

void CDevilCoin::Late_Update(void)
{
	Update_Rect();
}

void CDevilCoin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DevilCoin");

	if (!m_bCoin)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iFrameStart * 90,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));
	}


}

void CDevilCoin::Release(void)
{
}

void CDevilCoin::PlayerColiision(void)
{
	m_iHp = 0;
	if (!m_bCoin)
	{
		CScoreMgr::Get_Instance()->Plus_Coin(100);
		m_bCoin = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"tr0011_get_coin_lev.wav", SOUND_EFFECT, g_fSound);
	}
}

void CDevilCoin::Set_Hp(void)
{
}

void CDevilCoin::PetColiision(INFO _Pet)
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
				CScoreMgr::Get_Instance()->Plus_Coin(100);
				m_bCoin = true;
				CSoundMgr::Get_Instance()->PlaySoundW(L"tr0011_get_coin_lev.wav", SOUND_EFFECT, g_fSound);
			}
		}
	}
}
