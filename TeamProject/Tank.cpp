#include "stdafx.h"
#include "Tank.h"
#include "ObjMgr.h"
#include "M_Normal.h"
#include "ObjMgr.h"
CTank::CTank()
{

}


CTank::~CTank()
{
	Release();
}

void CTank::Initialize()
{
	m_iHp = 3;
	//추가한 코드(위)

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 1500;
	m_iExitLate = 1300;

	m_tInfo.vPos = { 100.f,100.f, 0.f};
	m_tInfo.vSize = { 100.f,100.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.06f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.06f,-m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.06f, m_tInfo.vSize.y * 0.1f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.06f, m_tInfo.vSize.y * 0.1f , 0.f };


	m_fSpeed = 3.5f;
}

void CTank::Ai_Pattern()
{

	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		m_fSpeed = 2.3f;
		m_bWalk_Out = true;
	}

	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_dwAttTime + m_iAttLate < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::M_BULLET);
		m_dwAttTime = GetTickCount();
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CTank::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot,matRotParent, matTransl, matParents;

	float fDia = sqrtf(m_vDir_Bullet.x * m_vDir_Bullet.x+ m_vDir_Bullet.y* m_vDir_Bullet.y);

	float	fRad = acosf(m_vDir_Bullet.x / fDia);

	m_fAngle = fRad * 180.f / 3.14f;
	
	if (m_pPlayer)
	{
		if (m_tInfo.vPos.y < m_pPlayer->Get_Info().vPos.y)
			m_fAngle *= -1.f;
	}

	D3DXMatrixTranslation(&matTransl,20.f,0.f,0.f);
	D3DXMatrixRotationZ(&matRot , D3DXToRadian( -m_fAngle));
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matWorld = matTransl*matRot*matParents;


}

void CTank::Dir_Plane(bool _bWalk_Out)
{
	m_tInfo.vDir = { 0.f,1.f,0.f };

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
}

void CTank::Release()
{
}

void CTank::Render(HDC _DC)
{
	RECT rc;
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x*0.2f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x*0.2f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.3f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y*0.3f));

	Rectangle(_DC, rc.left, rc.top, rc.right, rc.bottom);

	Ellipse(_DC, rc.left+2, rc.top+12, rc.right-2, rc.bottom-12);

	MoveToEx(_DC, (int)(m_vQ[0].x), (int)(m_vQ[0].y),nullptr);
	LineTo(_DC, (int)(m_vQ[1].x), (int)(m_vQ[1].y));

	MoveToEx(_DC, (int)(m_vQ[2].x), (int)(m_vQ[2].y), nullptr);
	LineTo(_DC, (int)(m_vQ[3].x), (int)(m_vQ[3].y));

}