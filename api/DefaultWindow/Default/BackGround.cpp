#include "stdafx.h"
#include "BackGround.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
}

void CBackGround::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 550.f;
	m_tInfo.fCX = 1800;
	m_tInfo.fCY = 300;

	m_fScroll = 0;

	m_Tile.fCX = 124;
	m_Tile.fCY = 120;
	m_Tile.fX = 0;
	m_Tile.fY = 495;
	m_bSound = false;
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackFireK.bmp", L"Fire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Oven.bmp", L"Oven2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Forest.bmp", L"Forest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Exit.bmp", L"Exit");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile1.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile2.bmp", L"Tile2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Witch.bmp", L"Witch");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PlayWtich.bmp", L"PlayWtich");
}

const int&& CBackGround::Update(void)
{
	Late_Update();

	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		m_fScroll += 0.5f;
	}
	else
		m_fScroll -= 0.5;

	m_TileRect.left = LONG(m_Tile.fX - (m_Tile.fCX * 0.5f));
	m_TileRect.top = LONG(m_Tile.fY - (m_Tile.fCY * 0.5f));
	m_TileRect.right = LONG(m_Tile.fX + (m_Tile.fCX * 0.5f));
	m_TileRect.bottom = LONG(m_Tile.fY + (m_Tile.fCY * 0.5f));


	return OBJ_NOEVENT;
}

void CBackGround::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hMem = CBmpMgr::Get_Instance()->Find_Image(L"Oven2");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Tile");
	HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"Exit");
	HDC		hMemDC4 = CBmpMgr::Get_Instance()->Find_Image(L"Witch");

	if (iScrollX < -12200)
	{
		hMem = CBmpMgr::Get_Instance()->Find_Image(L"Forest");
		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Tile2");

		if (!m_bSound)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CSoundMgr::Get_Instance()->PlaySoundW(L"03_Moonlit_Night_Sea.mp3", SOUND_BGM, g_fSound);
			m_bSound = true;
		}
	}

	BitBlt(hDC, int(0 + m_fScroll), 0, 2500, 700, hMem, 0, 0, SRCCOPY);
	BitBlt(hDC, int(0 + m_fScroll + 1200), 0, 2500, 700, hMem, 0, 0, SRCCOPY);



	GdiTransparentBlt(hDC,
		int(37000 + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(0),
		int(1704),
		int(640),
		hMemDC3,
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)1704,				// 복사할 비트맵의 가로, 세로 길이
		(int)640,
		RGB(255, 0, 200));


	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Fire");

		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tInfo.fY),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			0,								// 비트맵 출력 시작 좌표, X,Y
			265,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));


		if (m_tRect.left + iScrollX < 2800)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 1800),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,			// 비트맵 출력 시작 좌표, X,Y
				265,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}

		if (m_tRect.left + iScrollX < 1000)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 3600),	// 2,3 인자 :  복사받을 위치 X, Y
														//int(m_tRect.top),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,			// 비트맵 출력 시작 좌표, X,Y
				265,
				(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}


		if (m_tRect.left + iScrollX < -800)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 5400),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,
				265,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}

		if (m_tRect.left + iScrollX < -2600)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 7200),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,
				265,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
		if (m_tRect.left + iScrollX < -4400)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 7200),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,
				265,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
		if (m_tRect.left + iScrollX < -6200)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 9000),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,
				265,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
		if (m_tRect.left + iScrollX < -8000)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left + iScrollX + 10800),
				int(m_tInfo.fY),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				hMemDC,
				0,
				265,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 200));
		}
	}

	for (int i = 0; i < 25; ++i)
	{
		if(m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
		GdiTransparentBlt(hDC,
			int(m_TileRect.left + iScrollX + 124 * i),
			int(m_Tile.fY + iScrollY),
			int(m_Tile.fCX),
			int(m_Tile.fCY),
			hMemDC2,
			0,
			0,
			(int)m_Tile.fCX,
			(int)m_Tile.fCY,
			RGB(255, 0, 200));
	}
	for (int i = 27; i < 65; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
		GdiTransparentBlt(hDC,
			int(m_TileRect.left + iScrollX + 124 * i),
			int(m_Tile.fY + iScrollY),
			int(m_Tile.fCX),
			int(m_Tile.fCY),
			hMemDC2,
			0,
			0,
			(int)m_Tile.fCX,
			(int)m_Tile.fCY,
			RGB(255, 0, 200));
	}
	for (int i = 68; i < 100; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
		GdiTransparentBlt(hDC,
			int(m_TileRect.left + iScrollX + 124 * i),
			int(m_Tile.fY + iScrollY),
			int(m_Tile.fCX),
			int(m_Tile.fCY),
			hMemDC2,
			0,
			0,
			(int)m_Tile.fCX,
			(int)m_Tile.fCY,
			RGB(255, 0, 200));
	}
	for (int i = 103; i < 130; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 133; i < 153; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}



	for (int i = 156; i < 160; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}
	for (int i = 162; i < 167; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}
	for (int i = 170; i < 175; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}	
	for (int i = 178; i < 183; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 186; i < 238; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 241; i < 250; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 253; i < 259; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 261; i < 267; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 269; i < 275; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}

	for (int i = 277; i < 340; ++i)
	{
		if (m_TileRect.left + iScrollX + 124 * i < 1000 && m_TileRect.left + iScrollX + 124 * i > -150)
			GdiTransparentBlt(hDC,
				int(m_TileRect.left + iScrollX + 124 * i),
				int(m_Tile.fY + iScrollY),
				int(m_Tile.fCX),
				int(m_Tile.fCY),
				hMemDC2,
				0,
				0,
				(int)m_Tile.fCX,
				(int)m_Tile.fCY,
				RGB(255, 0, 200));
	}


	if (!static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		GdiTransparentBlt(hDC,
			int(38500 + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(80),
			int(227),
			int(169),
			hMemDC4,
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)227,				// 복사할 비트맵의 가로, 세로 길이
			(int)169,
			RGB(255, 0, 200));
	}
	else
	{
		HDC hMemDC8 = CBmpMgr::Get_Instance()->Find_Image(L"PlayWtich");
		GdiTransparentBlt(hDC,
			int(37900 + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(0),
			int(596),
			int(237),
			hMemDC8,
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)596,				// 복사할 비트맵의 가로, 세로 길이
			(int)237,
			RGB(255, 0, 200));
	}


}

void CBackGround::Release(void)
{
}

void CBackGround::Late_Update(void)
{
}
