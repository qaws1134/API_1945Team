#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster() : m_bTurn(false)
{
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
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}
