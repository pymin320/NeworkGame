#include "stdafx.h"
#include "Pumkin.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CPumkin::CPumkin()
{
}

CPumkin::CPumkin(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


CPumkin::~CPumkin()
{
}

void CPumkin::Initialize(void)
{
	m_tInfo.fCX = 146;
	m_tInfo.fCY = 109;

	m_fJumpPower = 15;
	m_fJumpTime = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pumkin1.bmp", L"Pumkin1");
}

const int && CPumkin::Update(void)
{
	if (m_iHp == 0)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 7.5f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_tInfo.fX += 30;
		m_fJumpTime += 0.1f;
	}

	return OBJ_NOEVENT;
}

void CPumkin::Late_Update(void)
{
	Update_Rect();
}

void CPumkin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_tRect.left + iScrollX < 1200)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Pumkin1");
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

void CPumkin::Release(void)
{
}
