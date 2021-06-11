#include "stdafx.h"
#include "FlyWing.h"
#include "ObjMgr.h"
#include "M_Normal.h"
#include "Boom.h"
//생성시 v_pos, e_eangledir e_exitangledir, b_reverse , b_itemDrop

CFlyWing::CFlyWing() :m_bPattern(false), m_bPatternCount(0), m_bStay(false), m_bReverse(false)
{
}

CFlyWing::~CFlyWing()
{
	Release();
}

void CFlyWing::Initialize()
{
	m_iHp = 25;

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 100;
	m_iExitLate = 3300;

	m_tInfo.vPos = { 100.f,100.f, 0.f };
	m_tInfo.vSize = { 200.f,200.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f,m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[1] = { 0.f,-m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.3f , 0.f };
	m_vP[3] = { 0.f,m_tInfo.vSize.y * 0.1f , 0.f };

	m_vPosin[0] = {  25.f,0.f,0.f };
	m_vPosin[1] = {  -15.f,0.f, 0.f};
	m_vPosin[2] = {0.f ,0.f- 10.f,0.f };

	m_fAngle = -60.f;
	m_fSpeed = 1.f;
}

void CFlyWing::Ai_Pattern()
{

	//턴타임
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		if (!m_bWalk_Out)
		{
			Set_eDir(m_eExitDir);
			m_fSpeed = 0.1f;
			if(!m_bReverse)
				m_iExitLate =6700;
			else
				m_iExitLate = 4500;
			m_bStay = true;
			GetTickCount();
			m_bWalk_Out = true;
		}
		else
		{
			m_bStay = false;
			m_fSpeed = 1.7f;
		}
	}

	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);
	if (!m_bReverse)
	{
		if (m_bStay)
		{
			if (m_dwAttTime + m_iAttLate < GetTickCount())
			{
				if (!m_bPattern)
				{
					m_fAngle = -75.f;
					for (int i = 0; i < 2; i++)
					{
						CreatePatternBullet(m_vPosin[i].x, m_vPosin[i].y, m_fAngle);
						m_fAngle -= 30.f;
					}

					m_iAttLate = 200;
					m_bPatternCount++;

					if (m_bPatternCount == 2)
					{
						m_iAttLate = 800;
						m_bPattern = true;
					}
				}
				else
				{

					m_fAngle = -90.f;
					CreatePatternBullet(m_vPosin[2].x, m_vPosin[2].y, m_fAngle);
					m_bPatternCount = 0;
					m_bPattern = false;
				}
				m_dwAttTime = GetTickCount();
			}
		}
	}
	else
	{
		if (m_bStay)
		{
			if (m_dwAttTime + m_iAttLate < GetTickCount())
			{
				if (!m_bPattern)
				{
					m_fAngle = -60.f;
					for (int i = 0; i < 2; i++)
					{
						CreatePatternBullet(m_vPosin[i].x, m_vPosin[i].y, m_fAngle);
						m_fAngle -= 60.f;
					}
					m_iAttLate = 800;
					m_bPattern = true;
				}
				else
				{

					m_fAngle = -90.f;
					CreatePatternBullet(m_vPosin[2].x, m_vPosin[2].y, m_fAngle);
					m_bPatternCount = 0;
					m_bPattern = false;
				}
				m_dwAttTime = GetTickCount();
			}
		}
	}

	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CFlyWing::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matRotParent, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	if(!m_bReverse)
		matWorld = matParents;
	else
	{
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(180.f));
		matWorld = matRot*matParents;
	}

}

void  CFlyWing::CreatePatternBullet(float _fX, float _fY, float _fAngle)
{
	CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(m_tInfo.vPos.x+_fX, m_tInfo.vPos.y + _fY, _fAngle-5), OBJID::M_BULLET);
	CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(m_tInfo.vPos.x + _fX, m_tInfo.vPos.y + _fY, _fAngle+5), OBJID::M_BULLET);
}

void CFlyWing::Release()
{
	if (m_bItemDrop)
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBoom>::Create(m_tInfo.vPos), OBJID::ITEM);
}