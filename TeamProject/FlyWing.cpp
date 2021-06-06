#include "stdafx.h"
#include "FlyWing.h"
#include "ObjMgr.h"
#include "M_Normal.h"

CFlyWing::CFlyWing()
{
}

CFlyWing::~CFlyWing()
{
}

void CFlyWing::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iExitLate = 1000;
	m_tInfo.vPos = { 100.f,100.f, 0.f };
	m_tInfo.vSize = { 100.f,100.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f,m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[1] = { 0.f,-m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[3] = { 0.f,+m_tInfo.vSize.y * 0.3f , 0.f };


	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_fSpeed = 1.f;
}

void CFlyWing::Ai_Pattern()
{
	Set_Target(m_pPlayer);

	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_dwAttTime + m_iAttLate < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::BULLET);
		m_dwAttTime = GetTickCount();
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CFlyWing::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matRotParent, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.vDir = m_vDir_Bullet - m_tInfo.vPos;	
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);


	matWorld = matTransl*matParents;

}

void CFlyWing::Dir_Plane(bool _bWalk_Out)
{
	m_tInfo.vDir = { 0.f,1.f,0.f };

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
}
