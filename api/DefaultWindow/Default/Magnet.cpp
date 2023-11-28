#include "stdafx.h"
#include "Magnet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMagnet::CMagnet()
{
}


CMagnet::~CMagnet()
{
}

void CMagnet::Initialize(void)
{
	m_tInfo.fX = 8500;
	m_tInfo.fY = 450;
	m_tInfo.fCX = 55;
	m_tInfo.fCY = 64;


	m_iHp = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Magnet.bmp", L"Magnet");
}

const int && CMagnet::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CMagnet::Late_Update(void)
{
	Update_Rect();
}

void CMagnet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Magnet");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		0,		// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 200));
}

void CMagnet::Release(void)
{
}
