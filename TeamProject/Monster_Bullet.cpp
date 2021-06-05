#include "stdafx.h"
#include "Monster_Bullet.h"


Monster_Bullet::Monster_Bullet()
{
}


Monster_Bullet::~Monster_Bullet()
{
}

void Monster_Bullet::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_fSpeed = 5.f;
}

int Monster_Bullet::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void Monster_Bullet::Late_Update()
{
	if (m_tRect.top < 0 || m_tRect.bottom > WINCY
		|| m_tRect.left < 0 || m_tRect.right > WINCX)
		m_bDead = true;
}

void Monster_Bullet::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Monster_Bullet::Release()
{
}
