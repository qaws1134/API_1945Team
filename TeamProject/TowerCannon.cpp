#include "stdafx.h"
#include "TowerCannon.h"
#include "M_Normal.h"

CTowerCannon::CTowerCannon()
{
}


CTowerCannon::~CTowerCannon()
{
}

void CTowerCannon::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 2000;
	m_iExitLate = 1000;

	m_tInfo.vSize = { 60.f,60.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.1f , 0.f };


	m_vPMonster[0] = { -m_tInfo.vSize.x * 0.6f,-m_tInfo.vSize.y * 0.6f , 0.f };
	m_vPMonster[1] = { -m_tInfo.vSize.x * 0.2f,-m_tInfo.vSize.y * 0.6f , 0.f };
	m_vPMonster[2] = { -m_tInfo.vSize.x * 0.2f, -m_tInfo.vSize.y * 0.2f , 0.f };
	m_vPMonster[3] = { -m_tInfo.vSize.x * 0.6f, -m_tInfo.vSize.y * 0.2f , 0.f };

	m_vPMonster[4] = {-m_tInfo.vSize.x * 0.6f,m_tInfo.vSize.y * 0.2f  , 0.f };
	m_vPMonster[5] = {-m_tInfo.vSize.x * 0.2f,m_tInfo.vSize.y * 0.2f , 0.f };
	m_vPMonster[6] = {-m_tInfo.vSize.x * 0.2f,m_tInfo.vSize.y * 0.6f, 0.f };
	m_vPMonster[7] = {-m_tInfo.vSize.x * 0.6f,m_tInfo.vSize.y * 0.6f , 0.f };


	m_fSpeed = 2.f;
}

void CTowerCannon::Release()
{
}

void CTowerCannon::Ai_Pattern()
{
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		m_bWalk_Out = true;
	}

	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_dwAttTime + m_iAttLate < GetTickCount())
	{
		CObj* pObj;
		pObj = CreateBullet<CM_Normal>();
		static_cast<CMonster_Bullet*>(pObj)->Set_BulletType(1);
		pObj->Initialize();
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
		m_dwAttTime = GetTickCount();
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	for (int i = 0; i < 8; i++)
		D3DXVec3TransformCoord(&m_vQMonster[i], &m_vPMonster[i], &matWorld);
}

void CTowerCannon::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matRotParent, matTransl, matParents;

	float fDia = sqrtf(m_vDir_Bullet.x * m_vDir_Bullet.x + m_vDir_Bullet.y* m_vDir_Bullet.y);

	float	fRad = acosf(m_vDir_Bullet.x / fDia);

	m_fAngle = fRad * 180.f / 3.14f;

	if (m_pPlayer)
	{
		if (m_tInfo.vPos.y < m_pPlayer->Get_Info().vPos.y)
			m_fAngle *= -1.f;
	}

	D3DXMatrixTranslation(&matTransl, 20.f, 0.f, 0.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matWorld = matTransl*matRot*matParents;
}

void CTowerCannon::Render(HDC _DC)
{
	RECT rc;
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x*0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x*0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y*0.5f));

	Rectangle(_DC, rc.left, rc.top, rc.right, rc.bottom);

	MoveToEx(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y, nullptr);
	for (int i = 1; i < 4; i++)
		LineTo(_DC, (int)m_vQMonster[i].x, (int)m_vQMonster[i].y);
	LineTo(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y);

	MoveToEx(_DC, (int)m_vQMonster[4].x, (int)m_vQMonster[4].y, nullptr);
	for (int i = 5; i < 8; i++)
		LineTo(_DC, (int)m_vQMonster[i].x, (int)m_vQMonster[i].y);
	LineTo(_DC, (int)m_vQMonster[4].x, (int)m_vQMonster[4].y);

	MoveToEx(_DC, (int)(m_vQ[0].x), (int)(m_vQ[0].y), nullptr);
	LineTo(_DC, (int)(m_vQ[1].x), (int)(m_vQ[1].y));

	MoveToEx(_DC, (int)(m_vQ[2].x), (int)(m_vQ[2].y), nullptr);
	LineTo(_DC, (int)(m_vQ[3].x), (int)(m_vQ[3].y));
}
