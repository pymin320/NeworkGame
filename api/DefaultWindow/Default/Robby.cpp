#include "stdafx.h"
#include "Robby.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScoreMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "NetworkManager.h"

CRobby::CRobby()
{
}


CRobby::~CRobby()
{
	Release();
}


void CRobby::Initialize(void)
{
	m_tMouseInfo.fCX = 30;
	m_tMouseInfo.fCY = 30;

	m_tButton.left = 50;
	m_tButton.right = 350;
	m_tButton.top = 450;
	m_tButton.bottom = 530;


	m_tStartButton.left = 450;
	m_tStartButton.right = 750;
	m_tStartButton.top = 450;
	m_tStartButton.bottom = 530;

	m_tHP.left = 115;
	m_tHP.right = 275;
	m_tHP.top = 430;
	m_tHP.bottom = 462;
	m_iHp = 0;
	m_iHpCount = 0;

	m_tPurchaseDevil.left = 415;
	m_tPurchaseDevil.right = 510;
	m_tPurchaseDevil.top = 130;
	m_tPurchaseDevil.bottom = 160;

	m_tPurchaseZombie.left = 250;
	m_tPurchaseZombie.right = 340;
	m_tPurchaseZombie.top = 130;
	m_tPurchaseZombie.bottom = 160;

	m_tCrickDevil.left = 420;
	m_tCrickDevil.right = 503;
	m_tCrickDevil.top = 50;
	m_tCrickDevil.bottom = 100;

	m_tCrickZombie.left = 250;
	m_tCrickZombie.right = 340;
	m_tCrickZombie.top = 50;
	m_tCrickZombie.bottom = 100;

	m_tPurchaseNormal.left = 580;
	m_tPurchaseNormal.right = 762;
	m_tPurchaseNormal.top = 385;
	m_tPurchaseNormal.bottom = 403;

	m_tPurchaseRare.left = 580;
	m_tPurchaseRare.right = 762;
	m_tPurchaseRare.top = 430;
	m_tPurchaseRare.bottom = 448;

	

	m_bReady = false;
	m_bBuyZombie = false;
	m_bBuyDevil = false;
	m_bNormal = false;
	m_bRare = false;

	m_iCookieType = COFFEECOOKIE;

	m_iCoinFrame = 0;
	m_iCount = 0;
	m_tFrame.iFrameStart = 0;

	m_tRect.left = 550;
	m_tRect.right = 599;
	m_tRect.top = 80;
	m_tRect.bottom = 134;

	m_tScore.fX = 650;
	m_tScore.fY = 100;
	m_tScore.fCX = 32;
	m_tScore.fCY = 38;

	m_iJellyType = BASE;

	CScoreMgr::Get_Instance()->Reset_Score();
	CScoreMgr::Get_Instance()->Reset_Coin();
	CScoreMgr::Get_Instance()->Reset_Hp();


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bg_lobby.bmp", L"bg_lobby");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_ready.bmp", L"btn_ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_gamestart.bmp", L"btn_start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bg_lobbydark.bmp", L"bg_lobbydark");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilcookieIconcheck.bmp", L"DevilcookieIconcheck");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieCheck.bmp", L"ZombieCheck");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeCheck.bmp", L"CoffeeCheck");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_purchase.bmp", L"btn_purchase");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_purchase_heart.bmp", L"btn_purchase_heart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/gauge_lobby_heart_64.bmp", L"gauge_lobby_heart_64");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_upgrade_normal.bmp", L"btn_upgrade_normal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/btn_upgrade_advanced.bmp", L"btn_upgrade_advanced");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoffeeCookie.bmp", L"Coffee");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DevilCookie.bmp", L"DevilCookie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ZombieCookie.bmp", L"Zombie");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SilverCoin.bmp", L"SilverCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FONT_NUMBER.bmp", L"FONT_NUMBER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Jellies");

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySoundW(L"00_Main_Lobby.mp3", SOUND_BGM, g_fSound);
}

void CRobby::Update(void)
{
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);

	if (m_iCount == 0)
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}
	else if (m_iCount + 100 < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_iCount = GetTickCount();
	}

	if (m_tFrame.iFrameStart == 4)
		m_tFrame.iFrameStart = 0;



	if (GetAsyncKeyState('U'))
	{
		CScoreMgr::Get_Instance()->Plus_MaxCoin(1000);
	}
	m_iCoin = CScoreMgr::Get_Instance()->Get_MaxCoin();



}

void CRobby::Late_Update(void)
{

	m_tMouseRect.left = LONG(m_tMouse.x - m_tMouseInfo.fCX);
	m_tMouseRect.right = LONG(m_tMouse.x + m_tMouseInfo.fCX);
	m_tMouseRect.top = LONG(m_tMouse.y - m_tMouseInfo.fCY);
	m_tMouseRect.bottom = LONG(m_tMouse.y + m_tMouseInfo.fCY);

	m_tScoreRect.left = LONG(m_tScore.fX - (m_tScore.fCX * 0.5f));
	m_tScoreRect.top = LONG(m_tScore.fY - (m_tScore.fCY * 0.5f));
	m_tScoreRect.right = LONG(m_tScore.fX + (m_tScore.fCX * 0.5f));
	m_tScoreRect.bottom = LONG(m_tScore.fY + (m_tScore.fCY * 0.5f));

	RECT RC{ 0,0,0,0 };

	if (IntersectRect(&RC, &m_tMouseRect, &m_tHP))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (m_iHpCount == 0)
			{
				++m_iHp;
				m_iHpCount = GetTickCount();
				CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
			}
			else if (m_iHpCount + 500 <= GetTickCount() && m_iHp < 5)
			{
				++m_iHp;
				m_iHpCount = GetTickCount();
				CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
			}
		}
	}

	CScoreMgr::Get_Instance()->Set_Hp(m_iHp);

	if (GetAsyncKeyState('P'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
		return;
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tPurchaseDevil) && m_bBuyDevil == false && m_iCoin > 15000)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bBuyDevil = true;
			CScoreMgr::Get_Instance()->Plus_MaxCoin(-15000);
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
		}
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tPurchaseZombie) && m_bBuyZombie == false && m_iCoin > 5000)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bBuyZombie = true;
			CScoreMgr::Get_Instance()->Plus_MaxCoin(-5000);
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
		}
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tCrickDevil) && m_bBuyDevil == true)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_iCookieType = DEVILCOOKIE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
		}
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tCrickZombie) && m_bBuyZombie == true)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_iCookieType = ZOMBIECOOKIE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
		}
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tPurchaseRare) && m_iCoin > 10000 && m_bRare == false)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
			CScoreMgr::Get_Instance()->Set_JellyType(RARE);
			CScoreMgr::Get_Instance()->Plus_MaxCoin(-10000);
			m_iJellyType = RARE;
			m_bRare = true;
		}
	}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tPurchaseNormal) && m_iCoin > 1000 && m_bNormal == false)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"SoundEff_UIButton.mp3", SOUND_EFFECT, g_fSound);
			CScoreMgr::Get_Instance()->Set_JellyType(NORMAL);
			CScoreMgr::Get_Instance()->Plus_MaxCoin(-1000);
			m_bNormal = true;
			m_iJellyType = NORMAL;
		}
	}
	CScoreMgr::Get_Instance()->Set_CookieType(m_iCookieType);
}

void CRobby::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"bg_lobby");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"btn_ready");
	HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"btn_start");
	HDC		hMemDC4 = CBmpMgr::Get_Instance()->Find_Image(L"bg_lobbydark");
	HDC		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"DevilcookieIconcheck");
	HDC		hMemDC6 = CBmpMgr::Get_Instance()->Find_Image(L"ZombieCheck");
	HDC		hMemDC7 = CBmpMgr::Get_Instance()->Find_Image(L"CoffeeCheck");
	HDC		hMemDC8 = CBmpMgr::Get_Instance()->Find_Image(L"btn_purchase");
	HDC		hMemDC9 = CBmpMgr::Get_Instance()->Find_Image(L"btn_purchase_heart");
	HDC		hMemDC10 = CBmpMgr::Get_Instance()->Find_Image(L"gauge_lobby_heart_64");
	HDC		hMemDC11 = CBmpMgr::Get_Instance()->Find_Image(L"btn_upgrade_normal");
	HDC		hMemDC12 = CBmpMgr::Get_Instance()->Find_Image(L"btn_upgrade_advanced");

	HDC		hMemDC13 = CBmpMgr::Get_Instance()->Find_Image(L"Coffee");
	HDC		hMemDC14 = CBmpMgr::Get_Instance()->Find_Image(L"Zombie");
	HDC		hMemDC15 = CBmpMgr::Get_Instance()->Find_Image(L"DevilCookie");
	HDC		hMemDC16 = CBmpMgr::Get_Instance()->Find_Image(L"SilverCoin");

	HDC		hMemDC17 = CBmpMgr::Get_Instance()->Find_Image(L"FONT_NUMBER");

	HDC		hMemDC18 = CBmpMgr::Get_Instance()->Find_Image(L"Jellies");

	if(m_bReady == false)
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	else
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC4, 0, 0, SRCCOPY);

	RECT	RC{ 0,0,0,0 };

	if (IntersectRect(&RC, &m_tMouseRect, &m_tButton) && m_bReady == false)
	{
		GdiTransparentBlt(hDC,
			int(50),	// 2,3 인자 :  복사받을 위치 X, Y
			int(450),
			int(292),
			int(79),
			hMemDC2,
			291,								// 비트맵 출력 시작 좌표, X,Y
			0,
			292,			// 복사할 비트맵의 가로, 세로 길이
			79,
			RGB(0, 255, 255));
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_bReady = true;
			return;
		}

	}
	else if(m_bReady == false)
		{
		GdiTransparentBlt(hDC,
			int(50),	// 2,3 인자 :  복사받을 위치 X, Y
			int(450),
			int(292),
			int(79),
			hMemDC2,
			0,
			0,
			292,			// 복사할 비트맵의 가로, 세로 길이
			79,
			RGB(0, 255, 255));
		}

	if (IntersectRect(&RC, &m_tMouseRect, &m_tStartButton) && m_bReady == false)
	{
		GdiTransparentBlt(hDC,
			int(450),	// 2,3 인자 :  복사받을 위치 X, Y
			int(450),
			int(292),
			int(79),
			hMemDC3,
			292,								// 비트맵 출력 시작 좌표, X,Y
			0,
			292,			// 복사할 비트맵의 가로, 세로 길이
			79,
			RGB(0, 255, 255));
		if (GetAsyncKeyState(VK_LBUTTON)){
			CNetworkManager::Get_Instance()->Set_OppReady(true);
			return;
		}
	}

	else if(m_bReady == false)
	{
		GdiTransparentBlt(hDC,
			int(450),	// 2,3 인자 :  복사받을 위치 X, Y
			int(450),
			int(292),
			int(79),
			hMemDC3,
			0,				// 비트맵 출력 시작 좌표, X,Y
			0,
			292,			// 복사할 비트맵의 가로, 세로 길이
			79,
			RGB(0, 255, 255));
	}


	if (m_bReady == true)
	{
		if (m_bBuyDevil == true && m_iCookieType == DEVILCOOKIE)
		{
			GdiTransparentBlt(hDC,	//악마맛
				int(420),
				int(50),
				int(83),
				int(77),
				hMemDC5,
				0,
				0,
				83,
				77,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,	//악마맛
				int(300),
				int(300),
				int(160),
				int(130),
				hMemDC15,
				3740,
				230,
				160,
				130,
				RGB(255, 0, 200));
		}
		else if (m_bBuyDevil == true && m_iCookieType != DEVILCOOKIE)
		{
			GdiTransparentBlt(hDC,
				int(420),
				int(50),
				int(83),
				int(77),
				hMemDC5,
				83,
				0,
				83,
				77,
				RGB(255, 0, 200));
		}
		else
		{
			GdiTransparentBlt(hDC,
				int(420),
				int(50),
				int(83),
				int(77),
				hMemDC5,
				166,
				0,
				83,
				77,
				RGB(255, 0, 200));
		}

		GdiTransparentBlt(hDC,
			int(415),
			int(130),
			int(90),
			int(30),
			hMemDC8,
			0,
			90,
			90,
			30,
			RGB(0, 255, 255));



		if (m_bBuyZombie == true && m_iCookieType == ZOMBIECOOKIE)
		{
			GdiTransparentBlt(hDC,	//좀비맛
				int(250),
				int(50),
				int(83),
				int(77),
				hMemDC6,
				0,
				0,
				83,
				77,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(320),
				int(320),
				int(170),
				int(170),
				hMemDC14,
				4100,
				190,
				170,
				170,
				RGB(255, 0, 200));

		}
		else if (m_bBuyZombie == true && m_iCookieType != ZOMBIECOOKIE)
		{
			GdiTransparentBlt(hDC,	//좀비맛
				int(250),
				int(50),
				int(83),
				int(77),
				hMemDC6,
				83,
				0,
				83,
				77,
				RGB(255, 0, 200));
		}

		else
		{
			GdiTransparentBlt(hDC,	//좀비맛
				int(250),
				int(50),
				int(83),
				int(77),
				hMemDC6,
				166,
				0,
				83,
				77,
				RGB(255, 0, 200));
		}

		GdiTransparentBlt(hDC,
			int(245),
			int(130),
			int(90),
			int(30),
			hMemDC8,
			0,
			30,
			90,
			30,
			RGB(0, 255, 255));

		if (m_iCookieType == COFFEECOOKIE)
		{
			GdiTransparentBlt(hDC,	// 기본쿠키
				int(80),	// 2,3 인자 :  복사받을 위치 X, Y
				int(50),
				int(83),
				int(77),
				hMemDC7,
				0,				// 비트맵 출력 시작 좌표, X,Y
				0,
				83,			// 복사할 비트맵의 가로, 세로 길이
				77,
				RGB(255, 0, 200));


			GdiTransparentBlt(hDC,
				int(330),
				int(280),
				int(140),
				int(215),
				hMemDC13,
				1560,
				1240,
				140,
				215,
				RGB(255, 0, 200));
		}

		else
		{
			GdiTransparentBlt(hDC,	// 기본쿠키
				int(80),	// 2,3 인자 :  복사받을 위치 X, Y
				int(50),
				int(83),
				int(77),
				hMemDC7,
				83,				// 비트맵 출력 시작 좌표, X,Y
				0,
				83,			// 복사할 비트맵의 가로, 세로 길이
				77,
				RGB(255, 0, 200));
		}

		// 젤리 타입
		if (m_iJellyType == BASE)
		{
			GdiTransparentBlt(hDC,	// 기본쿠키
				int(650),	// 2,3 인자 :  복사받을 위치 X, Y
				int(300),
				int(40),
				int(60),
				hMemDC18,
				0,				// 비트맵 출력 시작 좌표, X,Y
				1691,
				40,			// 복사할 비트맵의 가로, 세로 길이
				60,
				RGB(255, 0, 200));
		}
		else if (m_iJellyType == NORMAL)
		{
			GdiTransparentBlt(hDC,	// 기본쿠키
				int(650),	// 2,3 인자 :  복사받을 위치 X, Y
				int(300),
				int(40),
				int(60),
				hMemDC18,
				200,				// 비트맵 출력 시작 좌표, X,Y
				1691,
				40,			// 복사할 비트맵의 가로, 세로 길이
				60,
				RGB(255, 0, 200));
		}

		else if (m_iJellyType == RARE)
		{
			GdiTransparentBlt(hDC,	// 기본쿠키
				int(650),	// 2,3 인자 :  복사받을 위치 X, Y
				int(300),
				int(60),
				int(60),
				hMemDC18,
				1975,				// 비트맵 출력 시작 좌표, X,Y
				1800,
				60,			// 복사할 비트맵의 가로, 세로 길이
				60,
				RGB(255, 0, 200));
		}

		GdiTransparentBlt(hDC,										//체력 상점				
			int(55),		// 2,3 인자 :  복사받을 위치 X, Y
			int(430),
			int(59),
			int(43),
			hMemDC9,
			0,				// 비트맵 출력 시작 좌표, X,Y
			0,
			59,			// 복사할 비트맵의 가로, 세로 길이
			43,
			RGB(0, 255, 255));

		GdiTransparentBlt(hDC,										// 체력 빈거							
			int(115),
			int(430),
			int(160),
			int(32),
			hMemDC10,
			0,
			0,
			160,
			32,
			RGB(0, 255, 255));


		GdiTransparentBlt(hDC,									// 체력 찬거
			int(115),		// 2,3 인자 :  복사받을 위치 X, Y
			int(430),
			10 + m_iHp * 22,
			int(32),
			hMemDC10,
			0,				// 비트맵 출력 시작 좌표, X,Y
			32,
			10 + m_iHp * 23,			// 복사할 비트맵의 가로, 세로 길이
			32,
			RGB(0, 255, 255));

		GdiTransparentBlt(hDC,				// 노말 코인 업그레이드
			int(580),		// 2,3 인자 :  복사받을 위치 X, Y
			int(385),
			int(182),
			int(37),
			hMemDC11,
			0,				// 비트맵 출력 시작 좌표, X,Y
			0,
			182,			// 복사할 비트맵의 가로, 세로 길이
			37,
			RGB(0, 255, 255));

		GdiTransparentBlt(hDC,							//고급강화
			int(580),		// 2,3 인자 :  복사받을 위치 X, Y
			int(430),
			int(182),
			int(39),
			hMemDC12,
			0,				// 비트맵 출력 시작 좌표, X,Y
			0,
			182,			// 복사할 비트맵의 가로, 세로 길이
			39,
			RGB(0, 255, 255));

		GdiTransparentBlt(hDC,			//코인
			int(m_tRect.left),	
			int(m_tRect.top),
			int(49),
			int(54),
			hMemDC16,
			m_tFrame.iFrameStart * 49,	
			0,
			49,		// 복사할 비트맵의 가로, 세로 길이
			54,
			RGB(255, 0, 200));

		if (m_iCoin <= 9)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC17,
				int(m_tScore.fCX * m_iCoin),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}
		else if (m_iCoin >= 10 && m_iCoin < 100)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 25 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}
		else if (m_iCoin >= 100 && m_iCoin < 1000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 50 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 25 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 100 / 10 )),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}
		else if (m_iCoin >= 1000 && m_iCoin < 10000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 75 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 50 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 25 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iCoin >= 10000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 100 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin / 10000)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 75 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10000 / 1000)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 50 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left - 25 + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC17,
					int(m_tScore.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}


	}
}


void CRobby::Release(void)
{
}
