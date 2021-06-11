#include "stdafx.h"
#include "Monster_Bullet.h"


CMonster_Bullet::CMonster_Bullet()
{
}


CMonster_Bullet::~CMonster_Bullet()
{
}

void CMonster_Bullet::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_fSpeed = 5.f;
}

int CMonster_Bullet::Update()
{
	//////////////////////////////꼭 수정할 것
	m_bDead = true;
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CMonster_Bullet::Late_Update()
{
	if (m_tRect.top < 0 || m_tRect.bottom > WINCY
		|| m_tRect.left < 0 || m_tRect.right > WINCX)
		m_bDead = true;
}

void CMonster_Bullet::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster_Bullet::Release()
{
}
