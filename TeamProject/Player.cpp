#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Player_Bullet.h"
#include "Super_Bullet.h"
#include "SuperFly.h"
CPlayer::CPlayer() :m_fPosinAngle(0.f), m_eBullet_Type(BULLET_LEVEL::END), m_Bullet_State(1), m_bBullet_Launch(false), m_Bullet_LaunchN(0), m_Charge_Shot(nullptr), m_bCharge_Shot(false), m_Bomb(false), m_bCharge_Bomb(false)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

	m_delay = 120;
	m_Time = GetTickCount();
	m_eRenderID = RENDERID::OBJECT;

	D3DXMatrixIdentity(&matWorld);

	m_tInfo.vPos = { 200.0f, 200.0f, 0.0f };
	m_tInfo.vSize = { 50.0f, 150.0f, 0.0f };
	m_tInfo.vDir = { 0.0f, 0.0f, 0.0f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };

	m_fSpeed = 10.f;


}

int CPlayer::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	Key_Check();
	Bullet_Launch();
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	//D3DXMatrixScaling(&matParentScale, 2.f, 2.f, 1.f); 
	//matParentWorld = matParentScale* matParentTrans; 

	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	//D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
	//D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));
	// 행렬의 곱셈의 순서는 그냥 외워. 
	// 스 * 자 *이 * 공 * 부 
	// 케일  전  동	전	 모
	matWorld = matScale * matRotY * /* matRotZ */* matTrans/* * matRelRotZ*/ * matParentTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

		//m_vP[i].y -= 1;
	}

	return OBJ_NOEVENT;


}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);

	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_DC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	LineTo(_DC, m_tInfo.vPos.x, m_tInfo.vPos.y - m_tInfo.vSize.y);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Check()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('1'))
	{
			m_eBullet_Type = LEVEL1;
			m_bBullet_Launch = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('2'))
	{
			m_eBullet_Type = LEVEL2;
			m_bBullet_Launch = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('3'))
	{
			m_eBullet_Type = LEVEL3;
			m_bBullet_Launch = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('4'))
	{
			m_eBullet_Type = LEVEL4;
			m_bBullet_Launch = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('5'))
	{
			m_eBullet_Type = LEVEL5;
			m_bBullet_Launch = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('6'))
	{
			m_eBullet_Type = LEVEL6;
			m_bBullet_Launch = true;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (!m_Charge_Shot)
		{
			m_eBullet_Type = CHARGE;
			m_bBullet_Launch = true;
		}
		else
		{
			((Basic_Bullet*)m_Charge_Shot)->Set_Pos(m_tInfo.vPos.x, m_tInfo.vPos.y + 5);
		}
		m_bCharge_Shot = true;
	}
	else if (m_bCharge_Shot)
	{
		if (m_Charge_Shot)
		{
			((Basic_Bullet*)m_Charge_Shot)->Set_Move(true);
		}
		m_Charge_Shot = false;
		m_Charge_Shot = nullptr;
	}

	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SHIFT))
	//{
	//	if (!m_bCharge_Bomb)
	//	{
	//		m_eBullet_Type = BOMB;
	//		m_bBullet_Launch = true;
	//	}
	//	m_bCharge_Bomb = true;
	//}
	//else if (m_bCharge_Bomb)
	//{
	//	if (m_Bomb)
	//	{
	//		((Basic_Bullet*)m_Bomb)->Set_Move(true);
	//	}
	//	m_bCharge_Bomb = false;
	//	m_Bomb = nullptr;
	//}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CSuperFly>::Create(m_tInfo.vPos.x, WINCY), OBJID::BULLET);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vDir.x = -1.f;
		m_fAngle -= 4;

		if (m_fAngle < Min_Player_Angle)
			m_fAngle = Min_Player_Angle;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.vDir.y = -1.f;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.vDir.y = 1.f;
		}

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vDir.x = 1.f;
		m_fAngle += 4;
		if (m_fAngle > Max_Player_Angle)
			m_fAngle = Max_Player_Angle;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.vDir.y = -1.f;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.vDir.y = 1.f;
		}

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vDir.y = -1.f;

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vDir.y = 1.f;

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
	}
	else
	{
		m_fAngle = 0.0;
	}
	m_tInfo.vDir = { 0.0, 0.0, 0.0 };


}

void CPlayer::State_Change()
{
}

void CPlayer::Bullet_Launch()
{
	if (m_bBullet_Launch)
	{
		if (m_Time + m_delay < GetTickCount())
		{
			switch (m_eBullet_Type)
			{
			case CPlayer::LEVEL1:
				Basic_Attack();
				break;
			case CPlayer::LEVEL2:
				Level2_Attack();
				break;
			case CPlayer::LEVEL3:
				Level3_Attack();
				break;
			case CPlayer::LEVEL4:
				Level4_Attack();
				break;
			case CPlayer::LEVEL5:
				Level5_Attack();
				break;
			case CPlayer::LEVEL6:
				Level6_Attack();
				break;
			case CPlayer::CHARGE:
				Charge_Shot();
				break;
			case CPlayer::BOMB:
				Bomb();
				break;
			case CPlayer::END:
				break;
			default:
				break;
			}
			m_Bullet_LaunchN++;

			if (m_Bullet_LaunchN >= Bullet_LaunchN || m_eBullet_Type == CHARGE || m_eBullet_Type == BOMB)
			{
				m_Bullet_LaunchN = 0;
				m_bBullet_Launch = false;
			}
			m_Time = GetTickCount();
		}
	}
}

void CPlayer::Basic_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;

	default:
		break;
	}

	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}

void CPlayer::Level2_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 17.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 17.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	}

	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}

void CPlayer::Level3_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	default:
		break;
	}
	
	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}

void CPlayer::Level4_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	default:
		break;
	}

	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}

void CPlayer::Level5_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	default:
		break;
	}

	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}



void CPlayer::Level6_Attack()
{
	switch (m_Bullet_State)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 30.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y, 145.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	default:
		break;
	}

	m_Bullet_State++;
	if (m_Bullet_State > 3)
	{
		m_Bullet_State = 1;
	}
}

void CPlayer::Charge_Shot()
{
	CObj* pObj = Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y + 5, -145.0, 20, 110, Player_Bullet::CHARGE);
	m_Charge_Shot = pObj;
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLET);

}

void CPlayer::Bomb()
{
	CObj* pObj = Create_PlayerBullet<Super_Bullet>(m_tInfo.vPos.x, WINCY, -145.0, 200, 110, Player_Bullet::BOMB);
	m_Bomb = pObj;
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLET);
}
