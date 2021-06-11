#include "stdafx.h"
#include "PosinCannon.h"
#include "M_Normal.h"

CPosinCannon::CPosinCannon() : m_iBulletCount(0), m_bAttack(false)
{
}


CPosinCannon::~CPosinCannon()
{
}
void CPosinCannon::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_tInfo.vPos = { 100.f,100.f,0.f };
	m_tInfo.vSize = { 40.f,40.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.6f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.6f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.6f, m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.6f, m_tInfo.vSize.y * 0.1f , 0.f };
	m_iAttLate = 1500;
	m_iExitLate = 6000;
}
void CPosinCannon::Release()
{
}
void CPosinCannon::Ai_Pattern()
{
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		m_bAttack = false;
		m_bWalk_Out = true;
	}

	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_bAttack)
	{
		if (m_dwAttTime + m_iAttLate < GetTickCount())
		{
			CObj* pObj;
			pObj = CreateBullet<CM_Normal>();
			static_cast<CMonster_Bullet*>(pObj)->Set_BulletType(2);
			pObj->Initialize();
			pObj->Set_Angle(m_fAngle);
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
			m_iBulletCount++;
			m_iAttLate = 1000;
			if (m_iBulletCount == 2)
				m_iAttLate = 3000;
			m_dwAttTime = GetTickCount();
		}
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

}
void CPosinCannon::Render(HDC _DC)
{
	RECT rc;
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x*0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x*0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y*0.5f));
	Rectangle(_DC, m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f - 100.f, m_tInfo.vPos.y - 10.f - 40.f, m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f + 50.f, m_tInfo.vPos.y - 10.f + 40.f);

	Ellipse(_DC, rc.left, rc.top, rc.right, rc.bottom);

	MoveToEx(_DC, (int)(m_vQ[0].x), (int)(m_vQ[0].y), nullptr);
	for (int i= 1; i<4;i++)
	{
		LineTo(_DC, (int)(m_vQ[i].x), (int)(m_vQ[i].y));
	}
	LineTo(_DC, (int)(m_vQ[0].x), (int)(m_vQ[0].y));
}
void CPosinCannon::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matRotParent, matTransl, matParents;

	//x나 y축 이동하면 포신 나오도록 할 수 있음

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
