#include "stdafx.h"
#include "Robot.h"
#include "M_Normal.h"
#include "ObjMgr.h"
#include "BreakBullet.h"
#include "PinPanel.h"

CRobot::CRobot()
	: m_bBegin(false), m_dwPatternTime(GetTickCount()), m_iPatternTime(0)
	, m_bPatternOn(false), m_iPatternNum(0), m_iPrePatternNum(0), m_fPatternAngle(0.f)
	, m_bBegin2(false), m_iCount(0)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
	ZeroMemory(&vJumpPos, sizeof(vJumpPos));
}


CRobot::~CRobot()
{
}

void CRobot::Initialize()
{
	m_iHp = 120;
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 250;
	m_iExitLate = 500;

	m_fPatternAngle = 230.f;
	m_iPatternTime = 5000;

	m_eDir = M_ANGLE::DOWN;
	vJumpPos[0] = {float(WINCX-WINCXZERO),float(WINCY>>1)-100.f,0.f};
	vJumpPos[1] = {float ((WINCX-WINCXZERO)>>1)+WINCXZERO,float (WINCY>>1)-100,0.f};
	vJumpPos[2] = { float((WINCX - WINCXZERO) >> 1) + WINCXZERO - 150.f,float(WINCY >> 1)+100.f,0.f };


	m_tInfo.vPos = { float((WINCX - WINCXZERO) >> 1) + WINCXZERO,float(WINCY >> 1) - 300.f,0.f };
	m_tInfo.vSize = { 200.f,160.f,0.f };
	m_tPosin = { m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f, m_tInfo.vPos.y + m_tInfo.vSize.y*0.2f,0.f };
	
	//로봇 몸통
	m_vPMonster[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y *0.5f, 0.f };
	m_vPMonster[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y *0.5f, 0.f };
	m_vPMonster[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y *0.5f, 0.f };
	m_vPMonster[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y *0.5f, 0.f };

	m_fSpeed = 1.5f;
}



void CRobot::Ai_Pattern()
{

	Begin();
	m_tPosin = { m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f, m_tInfo.vPos.y + m_tInfo.vSize.y*0.2f,0.f };

	if (m_bBegin)
	{

		if (!m_bPatternOn)
		{
			m_iPrePatternNum = m_iPatternNum;// 패턴이 끝나면 이전 패턴 저장

			m_iPatternNum = rand()%4;
			m_dwAttTime = GetTickCount();
			m_dwExitTime = GetTickCount();
			m_bPatternOn = true;
			if (m_iPrePatternNum != m_iPatternNum)	//패턴이 다르면 다시 초기화 
				InitPattern();

		}

		if (m_dwPatternTime + m_iPatternTime < GetTickCount())
		{
			m_bPatternOn = false;
			m_dwPatternTime = GetTickCount();
		}
		
		//초기화
		if (m_dwExitTime + m_iExitLate < GetTickCount())	//패턴 종료 후 딜레이
		{
			if (m_dwAttTime + m_iAttLate < GetTickCount())
			{
				AttPattern();
				m_dwAttTime = GetTickCount();
			}
		}
	}
	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);
	for (int i = 0; i < 6; i++)
		D3DXVec3TransformCoord(&m_vQMonster[i], &m_vPMonster[i], &matWorld);
}

void CRobot::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matRotParent, matTransl, matParents;

	float fDia = sqrtf(m_vDir_Bullet.x * m_vDir_Bullet.x + m_vDir_Bullet.y* m_vDir_Bullet.y);

	float	fRad = acosf(m_vDir_Bullet.x / fDia);

	//플레이어 방향
	m_fAngle = fRad * 180.f / 3.14f;
	if (m_pPlayer)
	{
		if (m_tInfo.vPos.y < m_pPlayer->Get_Info().vPos.y)
			m_fAngle *= -1.f;
	}

	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matWorld = matParents;
}

void CRobot::Render(HDC _DC)
{
	RECT rc2;
	rc2.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x*0.5f));
	rc2.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x*0.5f));
	rc2.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.5f));
	rc2.bottom = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.3f));

	Rectangle(_DC, (int)(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f - 50.f), (int)(m_tInfo.vPos.y - 10.f - 40.f), (int)(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f + 50.f), (int)(m_tInfo.vPos.y - 10.f + 40.f));
	Rectangle(_DC, (int)(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f - 50.f), (int)(m_tInfo.vPos.y - 10.f - 40.f), (int)(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f + 50.f), (int)(m_tInfo.vPos.y - 10.f + 40.f));




	Rectangle(_DC, (int)m_tPosin.x - 30, (int)m_tPosin.y - 30, (int)m_tPosin.x + 20, (int)m_tPosin.y + 30);
	MoveToEx(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y, nullptr);
	for (int i = 1; i <4; i++)
		LineTo(_DC, (int)m_vQMonster[i].x, (int)m_vQMonster[i].y);
	LineTo(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y);


}

void CRobot::Begin()
{
	if (!m_bBegin)
	{
		if (m_tInfo.vPos.y > float(WINCY >> 1) - 100.f)
		{
			m_bBegin2 = true;
			m_eDir = M_ANGLE::UP;
		}
		if (m_bBegin2)
		{
			if (m_tInfo.vPos.y < 200.f)
			{
				m_dwPatternTime = GetTickCount();
				m_bBegin = true;
				m_eDir = M_ANGLE::IDLE;
			}
		}
	}
}


void CRobot::CreatePatternBullet(D3DXVECTOR3 _vPos, float _fAngle, int _PatternNum, int _iBulletType, float _fOffset)
{

	if (_PatternNum == 0)
	{
		CObj* pObj1 = nullptr;
		pObj1 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj1)->Set_BulletType(_iBulletType);
		pObj1->Initialize();
		pObj1->Set_Angle(_fAngle);
		CObjMgr::Get_Instance()->Add_Object(pObj1, OBJID::M_BULLET);
	}
	else if (_PatternNum == 1)
	{

		CObj* pObj2 = nullptr;
		pObj2 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj2)->Set_BulletType(_iBulletType);
		pObj2->Initialize();
		pObj2->Set_Angle(_fAngle - _fOffset);
		CObjMgr::Get_Instance()->Add_Object(pObj2, OBJID::M_BULLET);

		CObj* pObj3 = nullptr;
		pObj3 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj3)->Set_BulletType(_iBulletType);
		pObj3->Initialize();
		pObj3->Set_Angle(_fAngle + _fOffset);
		CObjMgr::Get_Instance()->Add_Object(pObj3, OBJID::M_BULLET);
	}
	else if (_PatternNum == 2)
	{
		CObj* pObj1 = nullptr;
		pObj1 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj1)->Set_BulletType(_iBulletType);
		pObj1->Initialize();
		CObjMgr::Get_Instance()->Add_Object(pObj1, OBJID::M_BULLET);

		CObj* pObj2 = nullptr;
		pObj2 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj2)->Set_BulletType(_iBulletType);
		pObj2->Initialize();
		pObj2->Set_Angle(_fAngle - _fOffset);
		CObjMgr::Get_Instance()->Add_Object(pObj2, OBJID::M_BULLET);

		CObj* pObj3 = nullptr;
		pObj3 = CreateBullet<CM_Normal>(_vPos.x, _vPos.y, _fAngle);
		static_cast<CMonster_Bullet*>(pObj3)->Set_BulletType(_iBulletType);
		pObj3->Initialize();
		pObj3->Set_Angle(_fAngle + _fOffset);
		CObjMgr::Get_Instance()->Add_Object(pObj3, OBJID::M_BULLET);
	}
}


void CRobot::AttPattern()
{
	switch (m_iPatternNum)
	{
	case 0:

		//좌우 발사
		CreatePatternBullet(m_tPosin, m_fPatternAngle, 0, 1, 0.f);
		m_fPatternAngle += 15.f*m_fRev;
		if (m_iCount == 3)
		{
			m_iAttLate = 400;
			m_iCount = 0;
			m_fRev *= -1;
		}
		else
		{
			m_iAttLate = 150;
			m_iCount++;
		}
		break;
	case 1:
		//브레이크 불렛 발사
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBreakBullet>::Create(m_tPosin.x,m_tPosin.y, D3DXVECTOR3{0.f,1.f,0.f}), OBJID::M_BULLET);
		break;
	case 2:
		if (!m_bPanel)
		{
			CreatePanle(M_ANGLE::UP_LEFT);
			CreatePanle(M_ANGLE::UP_RIGHT);
			CreatePanle(M_ANGLE::DOWN_LEFT);
			CreatePanle(M_ANGLE::DOWN_RIGHT);
			m_bPanel = true;
		}
		//핀 판넬1
		break;
	case 3:
		if (!m_bPanel)
		{
			CreatePanle(M_ANGLE::UP_LEFT);
			CreatePanle(M_ANGLE::UP_LEFT, -5.f);
			CreatePanle(M_ANGLE::UP);
			CreatePanle(M_ANGLE::UP_RIGHT);
			CreatePanle(M_ANGLE::UP_RIGHT, 5.f);
			m_bPanel = true;
		}
		break;
	case 4:
		m_tInfo.vDir = vJumpPos[randomJump];

		//점프
		//->이동 
		break;
	}
}

void CRobot::InitPattern()
{
	switch (m_iPatternNum)
	{
	case 0:
		m_fSpeed = 0.f;
		m_fPatternAngle = 270.f;
		m_iAttLate = 150;
		m_iPatternTime = 3000;
		m_fRev = 1;
		break;
	case 1:
		m_fSpeed = 0.f;
		m_fPatternAngle = 240;
		m_iAttLate = 1500;
		m_iPatternTime = 1500;
		break;
	case 2:
		m_bPanel = false;
		m_fSpeed = 0.f;
		m_iPatternTime =  2000;
		break;
	case 3:
		m_bPanel = false;
		m_fSpeed = 0.f;
		m_iPatternTime = 2000;
		break;
	case 4:
		randomJump = rand() % 3;
		m_iPatternTime = 2000;
	}
}

void CRobot::CreatePanle(M_ANGLE::DIRANGLE _eID)
{
	CObj* pObj = CAbstractFactory<CPinPanel>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
	static_cast<CMonster*>(pObj)->Set_eDir(_eID);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
}
void CRobot::CreatePanle(M_ANGLE::DIRANGLE _eID,float fOffset)
{
	CObj* pObj = CAbstractFactory<CPinPanel>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
	static_cast<CMonster*>(pObj)->Set_eDir(_eID);
	pObj->Set_Dir(D3DXVECTOR3(pObj->Get_Info().vDir.x + fOffset, pObj->Get_Info().vDir.y, 0.f));


	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
}
void CRobot::Release()
{
}
