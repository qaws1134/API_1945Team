#include "stdafx.h"
#include "MainGame.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
CMainGame::CMainGame()
	: m_iFPS(0), m_dwFPSTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);
	//CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::LOGO);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{

	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Bmp(L"Back");
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp(L"Back");

	Rectangle(hBackBuffer, 0, 0, WINCX, WINCY);

	BitBlt(hBack, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBack);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);



	
	++m_iFPS;
	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		TCHAR		szFPS[16] = L"";
		swprintf_s(szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	CScrollMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
