#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Player_Bullet.h"
CPlayer::CPlayer() :m_fPosinAngle(0.f)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;

	D3DXMatrixIdentity(&matWorld);

	m_tInfo.fX = 200.f;
	m_tInfo.fY = 200.f;
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_fSpeed = 5.f;


}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Check();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_DC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(_DC, m_tInfo.fX, m_tInfo.fY - m_tInfo.iCY);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Check()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<Player_Bullet>(0.0), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<Player_Bullet>(-145.0), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<Player_Bullet>(0.0), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<Player_Bullet>(145.0), OBJID::BULLET);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}



}

void CPlayer::State_Change()
{
}
