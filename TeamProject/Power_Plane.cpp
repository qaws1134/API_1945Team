#include "stdafx.h"
#include "Power_Plane.h"
#include "ObjMgr.h"
#include "M_Normal.h"
#include "Power.h"
CPower_Plane::CPower_Plane() : m_bTurn(false)
{
}


CPower_Plane::~CPower_Plane()
{
	Release();
}

void CPower_Plane::Initialize()
{
	m_iHp = 1;
	//추가한 코드(위)

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iExitLate = 700;
	m_tInfo.vSize = { 100.f,100.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.1f, m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.1f,m_tInfo.vSize.y * 0.3f , 0.f };

	m_fSpeed = 3.f;
}

void CPower_Plane::Ai_Pattern()
{

	//턴타임
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		m_bWalk_Out = true;
	}
	//이동
	Dir_Plane(m_bTurn);
	WriteMatrix(m_fAngle);

	//턴 행동패턴
	if (m_bWalk_Out)
	{
		m_fAngle -= 6.f;
		if (-180.f > m_fAngle)
		{
			m_bWalk_Out = true;
			if (!m_bTurn)
			{
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::M_BULLET);
				m_bTurn = true;
			}
		}
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	//턴할때 총알 발사
}

void CPower_Plane::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRotX, matRotY, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	if (!m_bTurn)
	{
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
		matWorld = matRotX *matParents;
	}
	else
	{
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(180));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
		matWorld = matRotX*matRotY *matParents;
	}
}

void CPower_Plane::Dir_Plane(bool m_bTurn)
{
	//스폰 시
	if (!m_bTurn)
		//아래 방향
		m_tInfo.vDir = { 0.f,1.f,0.f };
	else
		//오른쪽 대각선 위방향
		m_tInfo.vDir = { 1.f,-1.f,0.f };

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
}

void CPower_Plane::Release()
{
	if (m_bItemDrop)
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPower>::Create(m_tInfo.vPos), OBJID::ITEM);
}
