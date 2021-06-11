#include "stdafx.h"
#include "MyUI.h"
#include "ObjMgr.h"
#include "Player.h"
CMyUI::CMyUI()
:m_iScore(0), m_iBombN(0), m_iSuperShotGauge(0), m_iSuperShotN(0)
{
}


CMyUI::~CMyUI()
{
	Release();
}

void CMyUI::Initialize()
{
	m_tInfo.vPos = { 700.f, 400.f, 0.f };
	m_tInfo.vSize = { 200 * 2.5f, 800.f * 2.5f, 0.f };
	m_eRenderID = RENDERID::OBJECT;
}

int CMyUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Set_PlayerData();
	return OBJ_NOEVENT;
}

void CMyUI::Late_Update()
{
}


void CMyUI::Render(HDC _DC)
{
	Draw_Line(_DC);
	Write_Word(_DC);
	Draw_State(_DC);
}

void CMyUI::Release()
{
}

void CMyUI::Set_PlayerData()
{
	if ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))
	{
		m_iBombN = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_BombN();
		m_iSuperShotGauge = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_SuperShot_Gauge();
		m_iScore = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_Score();
		m_iSuperShotN = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_Super_Shot();
		m_iChargeShotN = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_Charge_Shot();
		m_iChargeGauge = ((CPlayer*)(CObjMgr::Get_Instance()->Get_Player()))->Get_Charge_Shot_Gauge();
	}
}


void CMyUI::Draw_Line(HDC _DC)
{
	MoveToEx(_DC, 0, 200, nullptr);
	LineTo(_DC, 200, 200);

	MoveToEx(_DC, 0, 200, nullptr);
	LineTo(_DC, 200, 200);

	MoveToEx(_DC, 0, 200, nullptr);
	LineTo(_DC, 200, 200);

	MoveToEx(_DC, 0, 200, nullptr);
	LineTo(_DC, 200, 200);

	MoveToEx(_DC, 0, 400, nullptr);
	LineTo(_DC, 200, 300);

	MoveToEx(_DC, 200, 0, nullptr);
	LineTo(_DC, 200, 800);
}

void CMyUI::Write_Word(HDC _DC)
{
	TCHAR str[100];
	Create_Letter(_DC, L"양재블럭체", L"[ Score ]", 15, 20, 30);
	Create_Letter(_DC, L"양재블럭체", L"Bomb!", 53, 215, 30);

	wsprintf(str, TEXT("%d"), m_iBombN);
	Create_Letter(_DC, L"안상수2006굵은", str, 90, 80, 30);
	Create_Letter(_DC, L"양재블럭체", L"Super Shot!", 10, 400, 30);

	wsprintf(str, TEXT("%d"), m_iScore);
	Create_Letter(_DC, L"안상수2006굵은", str, 90, 80, 30);
}

void CMyUI::Draw_State(HDC _DC)
{
	for (int i = 0; i < m_iBombN; i++)
	{
		Ellipse(_DC, 30 + 30 * i, 270, 50 + 30 * i, 300);
	}

	for (int i = 0; i < m_iChargeShotN; i++)
	{
		Ellipse(_DC, 30 + 30 * i, 450, 50 + 30 * i, 490);
	}

	int iGauge_Box = m_iChargeGauge / (Charge_Gauge_Max / 5);
	for (int i = 0; i < iGauge_Box; i++)
	{
		Rectangle(_DC, 50, 640 - 30 * i, 140, 665 - 30 * i);
	}
}


void CMyUI::Create_Letter(HDC _DC, const TCHAR * _pFont, const TCHAR * _pLetter, int _x, int _y, int _size)
{
	HFONT font, oldfont;
	font = CreateFont(_size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, _pFont);
	oldfont = (HFONT)SelectObject(_DC, font);
	TextOut(_DC, _x, _y, _pLetter, lstrlen(_pLetter));
	SelectObject(_DC, oldfont);
	DeleteObject(font);
}
