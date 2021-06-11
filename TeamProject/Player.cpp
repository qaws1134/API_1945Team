#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Player_Bullet.h"
#include "Super_Bullet.h"
#include "SuperFly.h"
CPlayer::CPlayer() 
	:m_fPosinAngle(0.f), m_eBullet_Type(BULLET_LEVEL::END), m_Bullet_State(1),
	m_bBullet_Launch(false), m_Bullet_LaunchN(0), m_pCharge_Shot(nullptr),
    m_Bomb(false), m_bCharge_Bomb(false),
	m_iBulletLevel(0), m_iBombN(0), m_eBeforeBullet_Type(BULLET_LEVEL::END),
	m_Charge_Gauge(0), m_iChargeShot(0), m_iScore(0), m_iSuperShot(0),
	m_iSuperShot_Gauge(0), m_bDead_Effect_Sequence(false), m_bDead_Effect_Move(false), Dead_Montion_Num(0),
	m_bDeadMove(false), m_bKeyRock(false), m_bBlink(false),
	m_iDelay(50)

{
	ZeroMemory(&Dead_Effect, sizeof(Dead_Effect));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_iTime = GetTickCount();

	Dead_EffectSize[0] = 0;
	Dead_EffectSize[1] = 100;
	Dead_EffectSize[2] = 120;
	Dead_EffectSize[3] = 130;
	Dead_EffectSize[4] = 140;


	m_iHp = 1;

	m_iBombN = 3;

	//m_iSuperShot_Gauge = 300;
	//m_iScore = 100;
	//m_iSuperShot = 2;
	///////////////확인용

	m_fAngle = 0.f;
	m_delay = 120;
	m_Time = GetTickCount();
	m_eRenderID = RENDERID::OBJECT;

	D3DXMatrixIdentity(&matWorld);

	m_tInfo.vPos = { 550.0f, 650.0f, 0.0f };
	m_tInfo.vSize = { 30.0f, 60.0f, 0.0f };
	m_tInfo.vDir = { 0.0f, 0.0f, 0.0f };
	m_tInfo.vDir = { 0.0f, 0.0f, 0.0f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.9f);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f);

	m_tRect.top = (LONG)(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f);
	m_fSpeed = 10.f;

	m_eBullet_Type = LEVEL1;
	m_eBeforeBullet_Type = m_eBullet_Type;

	Set_Player();

}

int CPlayer::Update()
{

	if (m_bDead)
		return OBJ_DEAD;
	Dead_Player();
	Bullet_Launch();
	Key_Check();
	Check_Hp(); // 죽은 지 확인하고 재시작
	Super_Shot_Check();
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);


	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);


	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));


	matWorld = matScale * matRotY * matTrans * matParentTrans;

	for (int i = 0; i < 30; ++i)
	{
		D3DXVec3TransformCoord(&m_pDraw_Player[i], &m_pPlayer[i], &matWorld);
	}

	Update_Rect();
	return OBJ_NOEVENT;


}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	Draw_Rect(_DC);
	MoveToEx(_DC, (int)m_pDraw_Player[0].x, (int)m_pDraw_Player[0].y, nullptr);
	if (!m_bBlink)
	{
		for (int i = 1; i < 29; ++i)
			LineTo(_DC, (int)m_pDraw_Player[i].x, (int)m_pDraw_Player[i].y);
	}
	if(m_bDead_Effect_Move)
	for(int i = 0; i < 5; i++)
		Ellipse(_DC, Dead_Effect[i].left, Dead_Effect[i].top, Dead_Effect[i].right, Dead_Effect[i].bottom);


}

void CPlayer::Release()
{
}

void CPlayer::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.2f);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.1f);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f);
}

void CPlayer::Add_Level()
{
	if (LEVEL6 >= m_iBulletLevel)
	{
		m_iBulletLevel++;
		m_eBullet_Type = (BULLET_LEVEL)m_iBulletLevel;
		m_eBeforeBullet_Type = m_eBullet_Type;
	}
}

void CPlayer::Add_Bomb()
{
	m_iBombN++;
}

int CPlayer::Get_BombN()
{
	return m_iBombN;
}

int CPlayer::Get_SuperShot_Gauge()
{
	return m_iSuperShot_Gauge;
}

int CPlayer::Get_Score()
{
	return m_iScore;
}

int CPlayer::Get_Super_Shot()
{
	return m_iSuperShot;
}

int CPlayer::Get_Charge_Shot()
{
	return m_iChargeShot;
}

int CPlayer::Get_Charge_Shot_Gauge()
{
	return m_Charge_Gauge;
}

void CPlayer::Super_Shot_Check()
{
	if (m_iSuperShot_Gauge > Bomb_Gauge_Max)
	{
		m_iSuperShot_Gauge = 0;
		m_iSuperShot++;
	}
}

void CPlayer::Set_BombN(int n)
{
	m_iBombN += n;
}

void CPlayer::Set_SuperShot_Gauge(int n)
{
	m_iSuperShot += n;
}


void CPlayer::Set_Score(int n)
{
	m_iScore += n;
}




void CPlayer::Key_Check()
{
	if (!m_bKeyRock)
	{



		//////////////////////////////////////////////
		if (CKeyMgr::Get_Instance()->Key_Down('C'))
		{
			CObj* pObj = new CSuperFly;
			pObj->Set_Pos(m_tInfo.vPos.x, WINCY);
			pObj->Initialize();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLET);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{

			m_bBullet_Launch = true;
			if (Charge_Gauge_Max <= m_Charge_Gauge)
			{
				m_iChargeShot += 1;
				m_Charge_Gauge = 0;
			}
			else if (Charge_Gauge_Max > m_Charge_Gauge && m_iChargeShot < 5)
				m_Charge_Gauge += 5;
			if (m_eBullet_Type == CHARGE)
			{
				m_eBullet_Type = m_eBeforeBullet_Type;
			}
		}


		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{

				if (!m_pCharge_Shot)
				{
					m_eBullet_Type = CHARGE;
					m_bBullet_Launch = true;
				}
				else
				{
					((Basic_Bullet*)m_pCharge_Shot)->Set_Pos(m_tInfo.vPos.x - 3, m_tInfo.vPos.y + 5);
				}
				m_bChargeShot = true;
			
		}
		else if (m_bChargeShot)
		{
			if (m_pCharge_Shot)
			{
				((Basic_Bullet*)m_pCharge_Shot)->Set_Move(true);
			}
			m_bChargeShot = false;
			m_pCharge_Shot = nullptr;
		}


		if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT) && m_iBombN > 0)
		{
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CSuperFly>::Create(m_tInfo.vPos.x, WINCY), OBJID::BULLET);
			m_iBombN--;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.vDir.x = -1.f;
			m_fAngle -= 4.f;

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

			if (m_tInfo.vPos.x < 220)
				m_tInfo.vPos.x = 220;
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

			if (m_tInfo.vPos.x > 800)
				m_tInfo.vPos.x = 800;
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
				if (m_iChargeShot > 0)
				{
					Charge_Shot();
					m_iChargeShot -= 1;
				}
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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 6.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 6.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 14.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 14.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 18.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 18.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 17.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 17.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 16.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 16.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 10, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 24.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 9.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 9.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 24.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 10.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 10.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 10.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 10.f, -145.0, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 70, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 0.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 40.f + 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 40.f + 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 40.f + 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y - 40.f + 30.f, -145.0, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 90, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);


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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y+ 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 7, 110, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
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
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 2:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		break;
	case 3:
		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, -10.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f - 40.f, -145.0, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

		CObjMgr::Get_Instance()->Add_Object(Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - m_tInfo.vSize.y + 30.f, 135.0f, 8, 130, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
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
	CObj* pObj = Create_PlayerBullet<Basic_Bullet>(m_tInfo.vPos.x , m_tInfo.vPos.y + 5, -145.0, 20, 110, Player_Bullet::CHARGE);
	m_pCharge_Shot = pObj;
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLET);

}

void CPlayer::Bomb()
{
	CObj* pObj = Create_PlayerBullet<Super_Bullet>(m_tInfo.vPos.x, WINCY, -145.0, 100, 50, Player_Bullet::BOMB);
	m_Bomb = pObj;
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BULLET);
}



void CPlayer::Replay()
{
	m_tInfo.vPos.y -= m_fSpeed * 0.2f;

	if (m_iTime + m_iDelay < (int)(GetTickCount()))
	{
		if (m_bBlink)
			m_bBlink = false;
		else
			m_bBlink = true;
		m_iTime = GetTickCount();
	}

	if (m_tInfo.vPos.y < 500)
	{
		m_bKeyRock = false;
		m_bDeadMove = false;
		m_bBlink = false;
	}
}

void CPlayer::Check_Hp()
{
	if (m_iHp < 0)
	{
		m_bDead_Effect_Move = true;
	}
	if (m_bDeadMove)
	{
		m_bKeyRock = true;
		Replay();
	}
}

void CPlayer::Draw_Rect(HDC _DC)
{
	HBRUSH	Brush, oBrush;
	HPEN	Pen, oPen = nullptr;
	Brush = CreateSolidBrush(RGB(255, 255, 255));
	oBrush = (HBRUSH)SelectObject(_DC, Brush);

	Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	oPen = (HPEN)SelectObject(_DC, Pen);

	Rectangle(_DC, int(m_tInfo.vPos.x - 12), int(m_tInfo.vPos.y - 15), int(m_tInfo.vPos.x + 5), int(m_tInfo.vPos.y + 38));


	SelectObject(_DC, oPen);
	DeleteObject(Pen);

	SelectObject(_DC, oBrush);
	DeleteObject(Brush);

}

void CPlayer::Dead_Player()
{
	if (m_bDead_Effect_Move)
	{
		if (Dead_EffectSize <= 0)
			m_bDead_Effect_Sequence = false;
		if (Dead_EffectSize[4] > 210)
		{
			m_bDead_Effect_Sequence = true;
			m_bDead_Effect_Move = false;
			m_iHp = 1;
			m_bDeadMove = true;
			ZeroMemory(&Dead_Effect[0], sizeof(RECT));
			m_tInfo.vPos.x = 400.f;
			m_tInfo.vPos.y = 900.f;
		}



		for (int i = 0; i < 5; i++)
		{
			if (m_bDead_Effect_Sequence)
				Dead_EffectSize[i] -= 30;
			else
				Dead_EffectSize[i] += 30;

			Dead_Effect[i].left = (LONG)(m_tInfo.vPos.x - Dead_EffectSize[i] * 0.5);
			Dead_Effect[i].right = (LONG)(m_tInfo.vPos.x + Dead_EffectSize[i] * 0.5);
			Dead_Effect[i].top = (LONG)(m_tInfo.vPos.y - Dead_EffectSize[i] * 0.5);
			Dead_Effect[i].bottom = (LONG)(m_tInfo.vPos.y + Dead_EffectSize[i] * 0.5);
		}
	}
}




void CPlayer::Set_Player()
{
	int ixMove = 120;
	int iyMove = 550;
	m_pPlayer[0] =	{ 100.f - ixMove, 500.f - iyMove, 0.f };
	m_pPlayer[1] =	{ 98.f - ixMove, 505.f - iyMove, 0.f };
	m_pPlayer[2] =	{ 95.f - ixMove, 515.f - iyMove, 0.f };
	m_pPlayer[3] =	{ 95.f - ixMove, 522.f - iyMove, 0.f };
	m_pPlayer[4] =	{ 94.f - ixMove, 538.f - iyMove, 0.f };
	m_pPlayer[5] =	{ 20.f - ixMove, 578.f - iyMove, 0.f };
	m_pPlayer[6] =	{ 20.f - ixMove, 586.f - iyMove, 0.f };
	m_pPlayer[7] =	{ 94.f - ixMove, 586.f - iyMove, 0.f };
	m_pPlayer[8] =	{ 94.f - ixMove, 620.f - iyMove, 0.f };
	m_pPlayer[9] =	{ 74.f - ixMove, 628.f - iyMove, 0.f };
	m_pPlayer[10] = { 74.f - ixMove, 637.f - iyMove, 0.f };
	m_pPlayer[11] = { 113.f - ixMove, 628.f - iyMove, 0.f };
	m_pPlayer[12] = { 152.f - ixMove, 636.f - iyMove, 0.f };
	m_pPlayer[13] = { 152.f - ixMove, 628.f - iyMove, 0.f };
	m_pPlayer[14] = { 131.f - ixMove, 620.f - iyMove, 0.f };
	m_pPlayer[15] = { 131.f - ixMove, 586.f - iyMove, 0.f };
	m_pPlayer[16] = { 205.f - ixMove, 586.f - iyMove, 0.f };
	m_pPlayer[17] = { 205.f - ixMove, 578.f - iyMove, 0.f };
	m_pPlayer[18] = { 131.f - ixMove, 538.f - iyMove, 0.f };
	m_pPlayer[19] = { 129.f - ixMove, 528.f - iyMove, 0.f };
	m_pPlayer[20] = { 129.f - ixMove, 523.f - iyMove, 0.f };
	m_pPlayer[21] = { 127.f - ixMove, 510.f - iyMove, 0.f };
	m_pPlayer[22] = { 122.f - ixMove, 500.f - iyMove, 0.f };
	m_pPlayer[23] = { 116.f - ixMove, 495.f - iyMove, 0.f };
	m_pPlayer[24] = { 112.f - ixMove, 495.f - iyMove, 0.f };
	m_pPlayer[25] = { 111.f - ixMove, 495.f - iyMove, 0.f };
	m_pPlayer[26] = { 108.f - ixMove, 495.f - iyMove, 0.f };
	m_pPlayer[27] = { 106.f - ixMove, 495.f - iyMove, 0.f };
	m_pPlayer[28] = { 100.f - ixMove, 500.f - iyMove, 0.f };
}

bool CPlayer::Get_DeadMove()
{
	return m_bDeadMove;
}



