#include "stdafx.h"
#include "Pet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CPet::CPet()
{
}


CPet::~CPet()
{
}

void CPet::Initialize(void)
{
	m_tFrame.iFrameStart = 0;
	m_iCount = 0;

	m_iDistance = 0;
	m_bMagnet = false;
	m_iMagnetCount = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet.bmp", L"Pet");

}

const int && CPet::Update(void)
{
	if (m_iCount == 0)
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 90 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 4)
		m_tFrame.iFrameStart = 0;

	if (m_iMagnetCount + 5000 <= GetTickCount())
	{
		m_bMagnet = false;
		m_iMagnetCount = 0;
		m_tInfo.fX -= 200;
	}

	return OBJ_NOEVENT;
}

void CPet::Late_Update(void)
{
	m_tMagnetRect.left = m_tRect.left - 150;
	m_tMagnetRect.right = m_tRect.right + 150;
	m_tMagnetRect.top = m_tRect.top - 150;
	m_tMagnetRect.bottom = m_tRect.bottom + 150;

	if (m_bMagnet)
	{
		if (m_iDistance <= 230)
		{
			m_iDistance += 10;
		}
		m_tInfo.fX += m_iDistance;
	}
	Update_Rect();
}

void CPet::Magnet()
{
	if (m_iMagnetCount == 0)
	{
		m_bMagnet = true;
		m_iMagnetCount = GetTickCount();
	}

}


void CPet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Get_Playertype() != WITCH)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Pet");
		if (static_cast<CPlayer*>(OBJMGR->Get_Obj_List(OBJ_PLAYER).front())->Get_Playertype() == BOOST)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX) - 100,	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top - 20),
				162,
				162,
				hMemDC,
				m_tFrame.iFrameStart * 162 + 20 + 468,			// 비트맵 출력 시작 좌표, X,Y
				0,
				162,		// 복사할 비트맵의 가로, 세로 길이
				162,
				RGB(255, 0, 200));
		}
		else if (m_bMagnet)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX) - 100,	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top - 20),
				162,
				162,
				hMemDC,
				m_tFrame.iFrameStart * 162,			// 비트맵 출력 시작 좌표, X,Y
				162,
				162,		// 복사할 비트맵의 가로, 세로 길이
				162,
				RGB(255, 0, 200));
		}
		else
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX) - 100,	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tRect.top - 20),
				162,
				162,
				hMemDC,
				m_tFrame.iFrameStart * 162 + 20,			// 비트맵 출력 시작 좌표, X,Y
				0,
				162,		// 복사할 비트맵의 가로, 세로 길이
				162,
				RGB(255, 0, 200));
		}
	}
}

void CPet::Release(void)
{
}
