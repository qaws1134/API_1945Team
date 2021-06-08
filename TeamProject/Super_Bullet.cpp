#include "stdafx.h"
#include "Super_Bullet.h"
#include "ObjMgr.h"
Super_Bullet::Super_Bullet() :m_eBulletType(BULLET_STATE::END),  m_Move(false), m_Still(0)
{
}


Super_Bullet::~Super_Bullet()
{

}

void Super_Bullet::Initialize()
{
	m_tInfo.vSize = { m_tInfo.vSize.x * 5, m_tInfo.vSize.y * 5, 0.f };
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.5f, m_tInfo.vSize.y  * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_fSpeed = 25;
	m_Still = 80;


	if (m_eBulletType == TARGET)
	{
		CObj* pObj = CObjMgr::Get_Instance()->Get_ShortTarget(m_tInfo, OBJID::MONSTER);
		if (pObj)
		{
			TestInfo.vPos = pObj->Get_Info().vPos;
			m_tInfo.vDir = TestInfo.vPos - m_tInfo.vPos;


			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

			D3DXVECTOR3 vLook{ 0.f, 1.f, 0.f };

			float fCos = D3DXVec3Dot(&vLook, &m_tInfo.vDir);
			m_fAngle = acosf(fCos);
		}
	}
}

int Super_Bullet::Update()
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eBulletType)
	{

	case Player_Bullet::BOMB:
		Bomb_Update();
		break;
	case Player_Bullet::TARGET:
		Target_Update();
		break;
	default:
		break;
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void Super_Bullet::Late_Update()
{
	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY)
		m_bDead = true;
}

void Super_Bullet::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Super_Bullet::Release()
{
}

void Super_Bullet::Bomb_Update()
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	matWorld = matScale * matTrans * matParentTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}
	if (m_tInfo.vPos.y < 450)
	{
		m_fSpeed = 2.5f;
	}

	if(m_Move)
		m_tInfo.vPos.y -= m_fSpeed;
}

void Super_Bullet::Target_Update()
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);

	matWorld = matScale * matTrans * matParentTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}
	m_tInfo.vPos.x += (int)(m_tInfo.vDir.x * m_fSpeed);
	m_tInfo.vPos.y += (int)(m_tInfo.vDir.y * m_fSpeed);

}



void Super_Bullet::Set_Size(float _xSize, float _ySize)
{
	m_tInfo.vSize.x = _xSize;
	m_tInfo.vSize.y = _ySize;
}

void Super_Bullet::Set_BulletType(BULLET_STATE _BULLET)
{
	m_eBulletType = _BULLET;
}



