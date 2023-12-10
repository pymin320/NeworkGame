#include "stdafx.h"
#include "Ui.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScoreMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Opp.h"
#include "NetworkManager.h"


CUi::CUi()
{
}


CUi::~CUi()
{
}

void CUi::Initialize(void)
{
	m_tInfo.fX = 260;
	m_tInfo.fY = 60;

	m_tInfo.fCX = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp();;
	m_tInfo.fCY = 50;

	m_tHP.fX = 400;
	m_tHP.fY = 60;
	m_bHp = false;

	m_tHP.fCX = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp();
	m_tHP.fCY = 50;
	
	m_fPlayerHp = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp();

	m_fOppOriginHp = CNetworkManager::Get_Instance()->Get_OppHp();

	m_tBonus.fX = 150;
	m_tBonus.fY = 20;

	m_tBonus.fCX = 277;
	m_tBonus.fCY = 31;


	m_tScore.fX = 400;
	m_tScore.fY = 100;

	m_tScore.fCX = 32;
	m_tScore.fCY = 38;

	m_tCoin.fX = 590;
	m_tCoin.fY = 100;

	m_tCoin.fCX = 32;
	m_tCoin.fCY = 38;

	m_fPlayerBar = 0;

	m_tJump.fX = 70;
	m_tJump.fY = 550;
	m_tJump.fCX = 118;
	m_tJump.fCY = 89;

	m_bHighScore = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Heart.bmp", L"Heart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Heart2.bmp", L"Heart2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Me.bmp", L"Me");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BonusTime.bmp", L"BonusTime");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FONT_NUMBER.bmp", L"Font");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Jellies.bmp", L"Jellies");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SilverCoin.bmp", L"Silver");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PlayBar.bmp", L"PlayBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UMINI.bmp", L"UMINI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/jump1.bmp", L"Jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Slide.bmp", L"Slide");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/1st.bmp", L"1st");

}

const int && CUi::Update(void)
{
	m_tHP.fCX = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp();

	//상대 hp
	m_tOppHP.fCX = CNetworkManager::Get_Instance()->Get_OppHp();


	m_iScore = CScoreMgr::Get_Instance()->Get_Score();
	m_iOppScore = CNetworkManager::Get_Instance()->Get_OppScore();

	if (CScoreMgr::Get_Instance()->Set_HighScore(m_iScore))
	{
		m_bHighScore = true;
	}

	if (m_iScore == 0)
	{
		m_bHighScore = false;
	}



	if(m_fPlayerHp > 0)
		m_fPlayerBar += 0.05f;

	if (m_fPlayerHp <= 0)
		m_fPlayerBar = 0;

	Get_Player();

	return OBJ_NOEVENT;
}

void CUi::Late_Update(void)
{
	if (!m_bHp)
	{
		m_tInfo.fCX = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj_List(OBJ_PLAYER).front())->Set_Hp();
		m_fOppOriginHp = CNetworkManager::Get_Instance()->Get_OppHp();
		m_bHp = true;
	}

	//m_fOppOriginHp = CNetworkManager::Get_Instance()->Get_OppHp();

	Update_Rect();

	m_iCoin = CScoreMgr::Get_Instance()->Get_Coin();
	m_iOppCoin = CNetworkManager::Get_Instance()->Get_OppCoin();

	m_tHPrect.left = LONG(m_tHP.fX - (m_tHP.fCX * 0.5f));
	m_tHPrect.top = LONG(m_tHP.fY - (m_tHP.fCY * 0.5f));
	m_tHPrect.right = LONG(m_tHP.fX + (m_tHP.fCX * 0.5f));
	m_tHPrect.bottom = LONG(m_tHP.fY + (m_tHP.fCY * 0.5f));

	m_tBonusRect.left = LONG(m_tBonus.fX - (m_tBonus.fCX * 0.5f));
	m_tBonusRect.top = LONG(m_tBonus.fY - (m_tBonus.fCY * 0.5f));
	m_tBonusRect.right = LONG(m_tBonus.fX + (m_tBonus.fCX * 0.5f));
	m_tBonusRect.bottom = LONG(m_tBonus.fY + (m_tBonus.fCY * 0.5f));

	m_tScoreRect.left = LONG(m_tScore.fX - (m_tScore.fCX * 0.5f));
	m_tScoreRect.top = LONG(m_tScore.fY - (m_tScore.fCY * 0.5f)) - 40.f;
	m_tScoreRect.right = LONG(m_tScore.fX + (m_tScore.fCX * 0.5f));
	m_tScoreRect.bottom = LONG(m_tScore.fY + (m_tScore.fCY * 0.5f));

	m_tCoinRect.left = LONG(m_tCoin.fX - (m_tCoin.fCX * 0.5f));
	m_tCoinRect.top = LONG(m_tCoin.fY - (m_tCoin.fCY * 0.5f)) - 40.f;
	m_tCoinRect.right = LONG(m_tCoin.fX + (m_tCoin.fCX * 0.5f));
	m_tCoinRect.bottom = LONG(m_tCoin.fY + (m_tCoin.fCY * 0.5f));

	// 상대 코인, 점수 포지션
	m_tOppScoreRect.left = LONG(m_tScore.fX - (m_tScore.fCX * 0.5f));
	m_tOppScoreRect.top = LONG(m_tScore.fY - (m_tScore.fCY * 0.5f)) + 10.f;
	m_tOppScoreRect.right = LONG(m_tScore.fX + (m_tScore.fCX * 0.5f));
	m_tOppScoreRect.bottom = LONG(m_tScore.fY + (m_tScore.fCY * 0.5f));

	m_tOppCoinRect.left = LONG(m_tCoin.fX - (m_tCoin.fCX * 0.5f));
	m_tOppCoinRect.top = LONG(m_tCoin.fY - (m_tCoin.fCY * 0.5f)) + 10.f;
	m_tOppCoinRect.right = LONG(m_tCoin.fX + (m_tCoin.fCX * 0.5f));
	m_tOppCoinRect.bottom = LONG(m_tCoin.fY + (m_tCoin.fCY * 0.5f));


	m_tJumpRect.left = LONG(m_tJump.fX - (m_tJump.fCX * 0.5f));
	m_tJumpRect.top = LONG(m_tJump.fY - (m_tJump.fCY * 0.5f));
	m_tJumpRect.right = LONG(m_tJump.fX + (m_tJump.fCX * 0.5f));
	m_tJumpRect.bottom = LONG(m_tJump.fY + (m_tJump.fCY * 0.5f));

}

void CUi::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	if (!static_cast<CPlayer*>(OBJMGR->Get_Player())->Cutscene())
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Heart");
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"BonusTime");
		HDC		hMemDC3 = CBmpMgr::Get_Instance()->Find_Image(L"Font");
		HDC		hMemDC4 = CBmpMgr::Get_Instance()->Find_Image(L"Jellies");
		HDC		hMemDC5 = CBmpMgr::Get_Instance()->Find_Image(L"Silver");
		HDC		hMemDC6 = CBmpMgr::Get_Instance()->Find_Image(L"PlayBar");
		HDC		hMemDC7 = CBmpMgr::Get_Instance()->Find_Image(L"UMINI");
		HDC		hMemDC8 = CBmpMgr::Get_Instance()->Find_Image(L"Jump");
		HDC		hMemDC9 = CBmpMgr::Get_Instance()->Find_Image(L"Slide");
		HDC		hMemDC10 = CBmpMgr::Get_Instance()->Find_Image(L"1st");
		HDC		hMemDC11 = CBmpMgr::Get_Instance()->Find_Image(L"Heart2");
		HDC		hMemDC12 = CBmpMgr::Get_Instance()->Find_Image(L"Me");

		//HPbar
		GdiTransparentBlt(hDC,
			int(70),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));

		GdiTransparentBlt(hDC,
			int(70),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tHPrect.top),
			int(m_tHP.fCX),
			int(m_tHP.fCY),
			hMemDC,
			0,			// 비트맵 출력 시작 좌표, X,Y
			50,
			(int)m_tHP.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tHP.fCY,
			RGB(255, 0, 200));

		//OppHp
		GdiTransparentBlt(hDC,
			int(70),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + 45),
			int(m_fOppOriginHp),
			int(m_tInfo.fCY),
			hMemDC11,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_fOppOriginHp,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));

		GdiTransparentBlt(hDC,
			int(70),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tHPrect.top + 45),
			int(m_tOppHP.fCX),
			int(m_tHP.fCY),
			hMemDC11,
			0,			// 비트맵 출력 시작 좌표, X,Y
			50,
			(int)m_tOppHP.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tHP.fCY,
			RGB(255, 0, 200));

		//me
		GdiTransparentBlt(hDC,
			int(10),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + 10),
			int(63),
			int(31),
			hMemDC12,
			0,			// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)63,		// 복사할 비트맵의 가로, 세로 길이
			(int)31,
			RGB(255, 0, 200));

		// 보너스 타임
		GdiTransparentBlt(hDC,
			int(m_tBonusRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tBonusRect.top),
			int(m_tBonus.fCX),
			int(m_tBonus.fCY),
			hMemDC2,
			0,			// 비트맵 출력 시작 좌표, X,Y
			31,
			(int)m_tBonus.fCX,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tBonus.fCY,
			RGB(255, 0, 200));

		if (m_iScore <= 9)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * m_iScore),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iScore >= 10 && 100 > m_iScore)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iScore / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}
		else if (m_iScore >= 100 && 1000 > m_iScore)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iScore / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * ((m_iScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * ((m_iScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iScore >= 1000 && 10000 > m_iScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iScore / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iScore >= 10000 && 100000 > m_iScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iScore / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 10000) / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iScore >= 100000 && 1000000 > m_iScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iScore / 100000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100000) / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 10000) / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 125),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}




		GdiTransparentBlt(hDC,
			340,	// 2,3 인자 :  복사받을 위치 X, Y
			35,
			40,
			int(m_tInfo.fCY),
			hMemDC4,
			0,			// 비트맵 출력 시작 좌표, X,Y
			1691,
			(int)40,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));





		// 코인
		if (m_iCoin <= 9)
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * m_iCoin),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
		else if (m_iCoin >= 10 && 100 > m_iCoin)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iCoin >= 100 && m_iCoin < 1000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iCoin >= 1000 && m_iCoin < 10000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin / 1000)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}



		GdiTransparentBlt(hDC,		//코인
			560,	// 2,3 인자 :  복사받을 위치 X, Y
			35,
			49,
			54,
			hMemDC5,
			0,		// 비트맵 출력 시작 좌표, X,Y
			0,
			49,		// 복사할 비트맵의 가로, 세로 길이
			54,
			RGB(255, 0, 200));



		// 상대 점수, 코인
		if (m_iOppScore <= 9)
		{
			GdiTransparentBlt(hDC,
				int(m_tOppScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * m_iOppScore),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iOppScore >= 10 && 100 > m_iOppScore)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iOppScore / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iOppScore % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}
		else if (m_iOppScore >= 100 && 1000 > m_iOppScore)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * (m_iOppScore / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * ((m_iOppScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppScoreRect.top),
					int(m_tScore.fCX),
					int(m_tScore.fCY),
					hMemDC3,
					int(m_tScore.fCX * ((m_iOppScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iOppScore >= 1000 && 10000 > m_iOppScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iOppScore / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iOppScore >= 10000 && 100000 > m_iOppScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iOppScore / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 10000) / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}

		else if (m_iOppScore >= 100000 && 1000000 > m_iOppScore)
		{
			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * (m_iOppScore / 100000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100000) / 10000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 10000) / 1000)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 1000) / 100)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) / 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));

			GdiTransparentBlt(hDC,
				int(m_tScoreRect.left + 125),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppScoreRect.top),
				int(m_tScore.fCX),
				int(m_tScore.fCY),
				hMemDC3,
				int(m_tScore.fCX * ((m_iOppScore % 100) % 10)),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tScore.fCY,
				RGB(255, 0, 200));
		}




		GdiTransparentBlt(hDC,
			340,	// 2,3 인자 :  복사받을 위치 X, Y
			85,
			40,
			int(m_tInfo.fCY),
			hMemDC4,
			0,			// 비트맵 출력 시작 좌표, X,Y
			1691,
			(int)40,		// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 200));





		// 코인
		if (m_iOppCoin <= 9)
		{
			GdiTransparentBlt(hDC,
				int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tOppCoinRect.top),
				int(m_tCoin.fCX),
				int(m_tCoin.fCY),
				hMemDC3,
				int(m_tCoin.fCX * m_iOppCoin),			// 비트맵 출력 시작 좌표, X,Y
				0,
				(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
				(int)m_tCoin.fCY,
				RGB(255, 0, 200));
		}
		else if (m_iOppCoin >= 10 && 100 > m_iOppCoin)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iOppCoin >= 100 && m_iOppCoin < 1000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}

		else if (m_iOppCoin >= 1000 && m_iOppCoin < 10000)
		{
			{
				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 25),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin / 1000)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tScore.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tScore.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 50),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 1000 / 100)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 75),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 100 / 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));

				GdiTransparentBlt(hDC,
					int(m_tCoinRect.left + 100),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tOppCoinRect.top),
					int(m_tCoin.fCX),
					int(m_tCoin.fCY),
					hMemDC3,
					int(m_tCoin.fCX * (m_iOppCoin % 10)),			// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tCoin.fCX,		// 복사할 비트맵의 가로, 세로 길이
					(int)m_tCoin.fCY,
					RGB(255, 0, 200));
			}
		}



		GdiTransparentBlt(hDC,		//코인
			560,	// 2,3 인자 :  복사받을 위치 X, Y
			85,
			49,
			54,
			hMemDC5,
			0,		// 비트맵 출력 시작 좌표, X,Y
			0,
			49,		// 복사할 비트맵의 가로, 세로 길이
			54,
			RGB(255, 0, 200));




		// 1st
		if (m_bHighScore)
		{
			GdiTransparentBlt(hDC,		//코인
				700,	// 2,3 인자 :  복사받을 위치 X, Y
				70,
				88,
				66,
				hMemDC10,
				0,		// 비트맵 출력 시작 좌표, X,Y
				0,
				88,		// 복사할 비트맵의 가로, 세로 길이
				66,
				RGB(255, 0, 200));
		}

		GdiTransparentBlt(hDC,
			50,	// 2,3 인자 :  복사받을 위치 X, Y
			75 + 50,
			282,
			42,
			hMemDC6,
			0,		// 비트맵 출력 시작 좌표, X,Y
			0,
			282,		// 복사할 비트맵의 가로, 세로 길이
			42,
			RGB(255, 0, 200));

		GdiTransparentBlt(hDC,
			int(50 + m_fPlayerBar),	// 2,3 인자 :  복사받을 위치 X, Y
			80 + 50,
			24,
			26,
			hMemDC7,
			0,		// 비트맵 출력 시작 좌표, X,Y
			0,
			24,		// 복사할 비트맵의 가로, 세로 길이
			26,
			RGB(255, 0, 200));

		if (m_iPlayer == JUMP)
		{
			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC8,
				118,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));

			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left + 660),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC9,
				0,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));
		}
		else if (m_iPlayer == SLIDE)
		{
			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left + 660),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC9,
				115,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));

			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC8,
				0,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));
		}
		else
		{
			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC8,
				0,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));

			GdiTransparentBlt(hDC,
				int(m_tJumpRect.left + 660),	// 2,3 인자 :  복사받을 위치 X, Y
				int(m_tJumpRect.top),
				int(m_tJump.fCX),
				int(m_tJump.fCY),
				hMemDC9,
				0,		// 비트맵 출력 시작 좌표, X,Y
				0,
				int(m_tJump.fCX),		// 복사할 비트맵의 가로, 세로 길이
				int(m_tJump.fCY),
				RGB(0, 255, 255));
		}
	}
}

void CUi::Release(void)
{
}

void CUi::Get_Player()
{
	m_iPlayer = static_cast<CPlayer*>(OBJMGR->Get_Player())->Set_State();
}
