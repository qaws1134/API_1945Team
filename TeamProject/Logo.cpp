#include "stdafx.h"
#include "Logo.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "MyUI.h"
CLogo::CLogo():dwDelay(0), dwTime(GetTickCount()), m_bColor(false), m_fAngle(0.f), m_bDir(false), m_fSpeed(0.f)
{
	ZeroMemory(m_pAirPlane, sizeof(m_pAirPlane));
	ZeroMemory(m_pAirPlane_draw, sizeof(m_pAirPlane_draw));
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	Load_Rocket();
	CObj* pObj = new CMyButton;
	pObj->Set_Pos(500.f, 600.f);
	pObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::UI);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMyUI>::Create(), OBJID::STATE);
	m_tInfo.vPos.x = 250.f;
	m_tInfo.vPos.y = 600.f;


	dwDelay = 200;

	m_fAngle = 45.f;
	m_fSpeed = 2.f;
}

void CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();

	Move_Plane();
}

void CLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CLogo::Render(HDC _DC)
{
	Draw_Paint(_DC);
}

void CLogo::Release()
{

	CObjMgr::Get_Instance()->Delete_ObjID(OBJID::UI);
}

void CLogo::Create_Letter(HDC _DC, const TCHAR * _pFont, const TCHAR * _pLetter, int _x, int _y, int _size)
{
	HFONT font, oldfont;
	font = CreateFont(_size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, _pFont);
	oldfont = (HFONT)SelectObject(_DC, font);
	TextOut(_DC, _x, _y, _pLetter, lstrlen(_pLetter));
	SelectObject(_DC, oldfont);
	DeleteObject(font);
}

void CLogo::Draw_Paint(HDC _DC)
{
	//글씨
	Create_Letter(_DC, L"HY견고딕", L"STRIKERS", 360, 200, 55);
	Create_Letter(_DC, L"HY견고딕", L"1945", 320, 250, 150);

	// 선
	MoveToEx(_DC, 255, 250, nullptr);
	LineTo(_DC, 745, 250);

	// insert Button
	CObjMgr::Get_Instance()->Render(_DC);

	// 깜빡임
	if (dwTime + dwDelay < GetTickCount())
	{
		m_bColor = !m_bColor;
		dwTime = GetTickCount();
	}
	if (m_bColor)
		TextOut(_DC, 457, 590, L"[ Insert Coin ]", 15);

	Draw_Rocket(_DC);
}

void CLogo::Draw_Rocket(HDC _DC)
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matParentWorld = matParentTrans;
	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 0.5f + m_tInfo.vSize.x, 0.5f + m_tInfo.vSize.y, 1.f);
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	matWorld = matScale * matRotZ * matParentWorld;


	for (int i = 0; i < 62; ++i)
	{
		D3DXVec3TransformCoord(&m_pAirPlane_draw[i], &m_pAirPlane[i], &matWorld);
	}

	MoveToEx(_DC, (int)m_pAirPlane_draw[0].x, (int)m_pAirPlane_draw[0].y, nullptr);
	for (int i = 1; i < 62; i++)
		LineTo(_DC, (int)m_pAirPlane_draw[i].x, (int)m_pAirPlane_draw[i].y);
	LineTo(_DC, (int)m_pAirPlane_draw[0].x, (int)m_pAirPlane_draw[0].y);
}

void CLogo::Load_Rocket()
{
	HANDLE hFile = CreateFile(L"../Data/Line.txt", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}
	int n = 0;
	DWORD	dwByte = 0;
	
	float Data;
	while (true)
	{
		ReadFile(hFile, &Data, sizeof(Data) , &dwByte, NULL);
		if (0 == dwByte)
			break;
		m_pAirPlane[n].x = Data;
		ReadFile(hFile, &Data, sizeof(Data), &dwByte, NULL);
		if (0 == dwByte)
			break;
		m_pAirPlane[n].y = Data;
		n++;
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}

void CLogo::Move_Plane()
{
	if (m_bDir)
	{
		m_tInfo.vPos.x -= m_fSpeed;
		m_tInfo.vPos.y += m_fSpeed;
		if (m_fAngle > -135.f)
			m_fAngle -= 2;
	}
	else
	{
		m_tInfo.vPos.x += m_fSpeed;
		m_tInfo.vPos.y -= m_fSpeed;

		if (m_fAngle < 45.f)
			m_fAngle += 2;
	}
	if (m_tInfo.vPos.y < 300.f)
	{
		m_bDir = true;

	}

	m_tInfo.vSize.x += 0.003f;
	m_tInfo.vSize.y += 0.003f;


}

