#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "CAbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "BackGround.h"
#include "UiMgr.h"
#include "Heal.h"
#include "Boost.h"
#include "Pet.h"
#include "Giga.h"
#include "Giga2.h"
#include "BmpMgr.h"
#include "Magnet.h"
#include "ScoreMgr.h"
#include "SceneMgr.h"
#include "DevilCoin.h"
#include "Small.h"
#include "SoundMgr.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Opp.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<COpp>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_METEOR, CAbstractFactory<CMeteor>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_HEAL, CAbstractFactory<CHeal>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_BOOST, CAbstractFactory<CBoost>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_GIGA, CAbstractFactory<CGiga>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_GIGA2, CAbstractFactory<CGiga2>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_SMALL, CAbstractFactory<CSmall>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CPet>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM_MAGNET, CAbstractFactory<CMagnet>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_DEVILCOIN, CAbstractFactory<CDevilCoin>::Create());
	CObjMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();

	CScrollMgr::Get_Instance()->Reset_Scroll();

	static_cast<CPlayer*>(OBJMGR->Get_Player())->Get_PlayerHp(CScoreMgr::Get_Instance()->Get_Hp());
	static_cast<CPlayer*>(OBJMGR->Get_Player())->Get_PlayerPosx();
	static_cast<CPlayer*>(OBJMGR->Get_Player())->Get_PlayerPosy();

	CUiMgr::Get_Instance()->Initialize();

	m_tMouseInfo.fCX = 20;
	m_tMouseInfo.fCY = 20;

	m_tStartRect.left = 150;
	m_tStartRect.right = 350;
	m_tStartRect.top = 250;
	m_tStartRect.bottom = 350;

	m_tExitRect.left = 450;
	m_tExitRect.right = 650;
	m_tExitRect.top = 250;
	m_tExitRect.bottom = 350;

	m_tPauseRect.left = 720;
	m_tPauseRect.right = 724;
	m_tPauseRect.top = 10;
	m_tPauseRect.bottom = 64;
	iNum = 0;
	m_iCount = 0;
	iNum2 = 0;
	m_iCount2 = 0;

	m_bPause = true;

	RECT RC{ 0,0,0,0 };

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	CSoundMgr::Get_Instance()->PlaySoundW(L"01_The_Witch's_House.mp3", SOUND_BGM, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_continue.bmp", L"btn_continue");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_stop.bmp", L"btn_stop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_puase_no.bmp", L"btn_puase_no");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/cutscene.bmp", L"cutscene");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shotgun.bmp", L"Shotgun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/realend.bmp", L"realend");
}

void CStage::Update(void)
{
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);
	m_tMouseRect.left = LONG(m_tMouse.x - m_tMouseInfo.fCX);
	m_tMouseRect.right = LONG(m_tMouse.x + m_tMouseInfo.fCX);
	m_tMouseRect.top = LONG(m_tMouse.y - m_tMouseInfo.fCY);
	m_tMouseRect.bottom = LONG(m_tMouse.y + m_tMouseInfo.fCY);

	if (GetAsyncKeyState(VK_LBUTTON) && IntersectRect(&RC, &m_tPauseRect, &m_tMouseRect))
		m_bPause = false;

	else if(GetAsyncKeyState('P'))
		m_bPause = false;

	if(GetAsyncKeyState(VK_LBUTTON) && IntersectRect(&RC, &m_tStartRect, &m_tMouseRect) && m_bPause == false)
		m_bPause = true;


	if (GetAsyncKeyState('O') && IntersectRect(&RC, &m_tExitRect, &m_tMouseRect) && m_bPause == false)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SCORE);
	}

	else if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Set_Endgame())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SCORE);
	}

	if (m_bPause)
	{
		CObjMgr::Get_Instance()->Update();
		CUiMgr::Get_Instance()->Update();
		if (!CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).empty())
		{
			static_cast<CUi*>(CUiMgr::Get_Instance()->Get_Ui_List().front())->Get_Hp(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp());
			static_cast<CPet*>(OBJMGR->Get_Obj_List(OBJ_PET).front())->Set_Info(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Get_Info());
		}
	}
}

void CStage::Late_Update(void)
{
	if (m_bPause)
	{
		CObjMgr::Get_Instance()->Late_Update();
		CUiMgr::Get_Instance()->Late_Update();
	}
}

void CStage::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
	CUiMgr::Get_Instance()->Render(hDC);
	if (!m_bPause)
	{
		Pause(hDC);
	}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"btn_puase_no");
	GdiTransparentBlt(hDC,
		int(720),	// 2,3 인자 :  복사받을 위치 X, Y
		10,
		54,
		54,
		hMemDC,
		0,		// 비트맵 출력 시작 좌표, X,Y
		0,
		54,		// 복사할 비트맵의 가로, 세로 길이
		54,
		RGB(0, 255, 255));

	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		if (GetAsyncKeyState(VK_LBUTTON) && m_iCount == 0)
		{
			iNum += 800;
			m_iCount = GetTickCount();
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && m_iCount + 1000 < GetTickCount())
		{
			iNum += 800;
			m_iCount = GetTickCount();
		}
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"cutscene");
		GdiTransparentBlt(hDC,
			int(0),
			int(0),
			int(800),
			int(600),
			hMemDC,
			0 + iNum,
			0,
			(int)800,
			(int)600,
			RGB(0, 255, 255));
		if (iNum >= 4000)
		{
			HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Shotgun");
			GdiTransparentBlt(hDC,
				int(200),
				int(200),
				int(414),
				int(124),
				hMemDC2,
				iNum - 4000,
				0,
				(int)414,
				(int)124,
				RGB(255, 0, 200));

		}
	}

	if (static_cast<CPlayer*>(OBJMGR->Get_Player())->End())
	{
		HDC		hMemDC9 = CBmpMgr::Get_Instance()->Find_Image(L"realend");
		CSoundMgr::Get_Instance()->StopAll();


		if (GetAsyncKeyState(VK_LBUTTON) && m_iCount2 == 0)
		{
			iNum2 += 820;
			m_iCount2 = GetTickCount();
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && m_iCount2 + 1000 < GetTickCount())
		{
			iNum2 += 820;
			m_iCount2 = GetTickCount();
		}

		GdiTransparentBlt(hDC,
			int(0),
			int(0),
			int(820),
			int(592),
			hMemDC9,
			0 + iNum2,
			0,
			(int)820,
			(int)592,
			RGB(0, 255, 255));
	}
}

void CStage::Release(void)
{
}

void CStage::Pause(HDC hDC)
{
	if (IntersectRect(&RC, &m_tExitRect, &m_tMouseRect))
	{
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"btn_stop");
		GdiTransparentBlt(hDC,
			int(420),	// 2,3 인자 :  복사받을 위치 X, Y
			int(WINCY / 2),
			int(218),
			int(73),
			hMemDC2,
			218,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)218,		// 복사할 비트맵의 가로, 세로 길이
			(int)73,
			RGB(0, 255, 255));
	}

	else
	{
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"btn_stop");
		GdiTransparentBlt(hDC,
			int(420),	// 2,3 인자 :  복사받을 위치 X, Y
			int(WINCY / 2),
			int(218),
			int(73),
			hMemDC2,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)218,		// 복사할 비트맵의 가로, 세로 길이
			(int)73,
			RGB(0, 255, 255));
	}

	if (IntersectRect(&RC, &m_tStartRect, &m_tMouseRect))
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"btn_continue");
		GdiTransparentBlt(hDC,
			int(180),	// 2,3 인자 :  복사받을 위치 X, Y
			int(WINCY / 2),
			int(218),
			int(73),
			hMemDC,
			218,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)218,		// 복사할 비트맵의 가로, 세로 길이
			(int)73,
			RGB(0, 255, 255));
	}
	else
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"btn_continue");
		GdiTransparentBlt(hDC,
			int(180),	// 2,3 인자 :  복사받을 위치 X, Y
			int(WINCY / 2),
			int(218),
			int(73),
			hMemDC,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)218,		// 복사할 비트맵의 가로, 세로 길이
			(int)73,
			RGB(0, 255, 255));

	}


}


