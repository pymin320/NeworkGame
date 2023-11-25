#include "stdafx.h"
#include "Small.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CSmall::CSmall()
{
}


CSmall::~CSmall()
{
}

void CSmall::Initialize(void)
{
	m_tInfo.fX = 6400;
	m_tInfo.fY = 100;

	m_tInfo.fCX = 60;
	m_tInfo.fCY = 80;


	m_iHp = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Small");
}

const int && CSmall::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CSmall::Late_Update(void)
{
	Update_Rect();
}

void CSmall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Small");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		int(1120),		
		1320,
		(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));
}

void CSmall::Release(void)
{
}
