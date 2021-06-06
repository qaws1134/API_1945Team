#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster() 
	: m_bWalk_Out(false), m_bItemDrop(false)
	,m_dwExitTime(GetTickCount()),m_iExitLate(0),m_dwAttTime(GetTickCount()),m_iAttLate(0)
{
	ZeroMemory(&m_vDir_Bullet, sizeof(m_vDir_Bullet));
}


CMonster::~CMonster()
{
	Release();
}


int CMonster::Update()
{

	if (m_bDead)
		return OBJ_DEAD;


	Ai_Pattern();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; i++)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);
}

void CMonster::Release()
{
}
