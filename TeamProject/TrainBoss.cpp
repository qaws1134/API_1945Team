#include "stdafx.h"
#include "TrainBoss.h"
#include "M_Normal.h"
#include "PosinCannon.h"
#include "ObjMgr.h"
#include "Robot.h"
CTrainBoss::CTrainBoss()
	: m_bBegin(false) , m_dwPatternTime(GetTickCount()), m_iPatternTime(0)
	, m_bPatternOn(false), m_iPatternNum(0), m_iPrePatternNum(0), m_fPatternAngle(0.f)
	, m_bBegin2(false), m_iCount(0)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
	ZeroMemory(&Cannon, sizeof(Cannon));
}


CTrainBoss::~CTrainBoss()
{
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CRobot>::Create(), OBJID::MONSTER);
}

void CTrainBoss::Initialize()
{

	m_iHp = 100;
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 250;
	m_iExitLate = 500;

	m_fPatternAngle = 10.f;
	m_iPatternTime = 5000;

	m_eDir = M_ANGLE::DOWN;

	//m_tInfo.vPos = { float(WINCX>>1),-m_tInfo.vSize.y*0.5f,0.f };
	m_tInfo.vSize = { 300.f,600.f,0.f };

	
	//기차 몸통
	m_vPMonster[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y *0.5f, 0.f };
	m_vPMonster[1] = {  m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y *0.5f, 0.f };
	m_vPMonster[2] = {  m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y *0.2f, 0.f };
	m_vPMonster[3] = {  m_tInfo.vSize.x * 0.3f, m_tInfo.vSize.y *0.3f, 0.f };
	m_vPMonster[4] = { -m_tInfo.vSize.x * 0.3f, m_tInfo.vSize.y *0.3f, 0.f };
	m_vPMonster[5] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y *0.2f, 0.f };


	m_fSpeed = 1.5f;
}



void CTrainBoss::Ai_Pattern()
{

	Begin();
	m_tPosin[0] = { m_tInfo.vPos.x+m_tInfo.vSize.x  *0.2f, m_tInfo.vPos.y + m_tInfo.vSize.y*0.1f,0.f };
	m_tPosin[1] = { m_tInfo.vPos.x -m_tInfo.vSize.x * 0.2f,m_tInfo.vPos.y + m_tInfo.vSize.y*0.1f,0.f };

	if (m_bBegin)
	{
		Cannon[0]->Set_Pos(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f, m_tInfo.vPos.y-10.f );
		Cannon[1]->Set_Pos(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f, m_tInfo.vPos.y-10.f );
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

void CTrainBoss::WriteMatrix(float _fRotAngle)
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

void CTrainBoss::Render(HDC _DC)
{
	RECT rc;
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x*0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x*0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y*0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y- (m_tInfo.vSize.y*0.3f));
	if (!m_bBegin)
	{
		Rectangle(_DC, (int)(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f - 90.f), (int)(m_tInfo.vPos.y - 10.f - 40.f), (int)(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.5f + 40.f), (int)(m_tInfo.vPos.y - 10.f + 40.f));
		Rectangle(_DC, (int)(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f - 40.f), (int)(m_tInfo.vPos.y - 10.f - 40.f), (int)(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.5f + 90.f), (int)(m_tInfo.vPos.y - 10.f + 40.f));
	}

	
	Rectangle(_DC, (int)m_tPosin[1].x - 10, (int)m_tPosin[1].y - 10, (int)m_tPosin[1].x + 10, (int)m_tPosin[1].y + 10);
	Rectangle(_DC, (int)m_tPosin[0].x - 10, (int)m_tPosin[0].y - 10, (int)m_tPosin[0].x + 10, (int)m_tPosin[0].y + 10);
	MoveToEx(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y, nullptr);
	for (int i = 1; i < 6; i++)
		LineTo(_DC, (int)m_vQMonster[i].x, (int)m_vQMonster[i].y);
	LineTo(_DC, (int)m_vQMonster[0].x, (int)m_vQMonster[0].y);


}

void CTrainBoss::Begin()
{
	if (!m_bBegin)
	{
		if (m_tInfo.vPos.y > float(WINCY>>1)-100.f)
		{
			m_bBegin2 = true;
			m_eDir = M_ANGLE::UP;
		}
		if (m_bBegin2)
		{
			if (m_tInfo.vPos.y < 100.f)
			{
				m_dwPatternTime = GetTickCount();
				m_bBegin = true;
				m_eDir = M_ANGLE::IDLE;

				Cannon[0] = CAbstractFactory<CPosinCannon>::Create(m_tInfo.vPos.x + m_tInfo.vSize.x  *0.3f, m_tInfo.vPos.y - m_tInfo.vSize.y*0.2f);
				Cannon[1] = CAbstractFactory<CPosinCannon>::Create(m_tInfo.vPos.x - m_tInfo.vSize.x  *0.3f, m_tInfo.vPos.y - m_tInfo.vSize.y*0.2f);
				CObjMgr::Get_Instance()->Add_Object(Cannon[0], OBJID::MONSTER);
				CObjMgr::Get_Instance()->Add_Object(Cannon[1], OBJID::MONSTER);
			}
		}
		//0123 패턴 순서대로 시작

	}
}


void CTrainBoss::CreatePatternBullet(D3DXVECTOR3 _vPos, float _fAngle, int _PatternNum, int _iBulletType, float _fOffset)
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


void CTrainBoss::AttPattern()
{
	switch (m_iPatternNum)
	{
	case 0:
		//2개원돌기
		CreatePatternBullet(m_tPosin[0], m_fPatternAngle, 1, 0, 10.f);
		CreatePatternBullet(m_tPosin[1], m_fPatternAngle + 160.f, 1, 0, 10.f);
		m_fPatternAngle += 30.f;

		break;
	case 1:
		//1개 원돌기
		CreatePatternBullet(m_tPosin[0], m_fPatternAngle, 0, 0, 0.f);
		CreatePatternBullet(m_tPosin[1], m_fPatternAngle + 160.f, 0, 0, 0.f);
		m_fPatternAngle += 30.f;

		break;
	case 2:
		//포탑 쏘기
		static_cast<CPosinCannon*>(Cannon[0])->Set_Attack(true);
		static_cast<CPosinCannon*>(Cannon[1])->Set_Attack(true);
		break;
	case 3:
		//3개 2연발 번갈아 쏘기
		//CreatePatternBullet();
		if (m_iCount == 2)
		{
			m_iAttLate = 1000;
			m_iCount = 0;
		}
		else {
			m_iAttLate = 400;
			m_iCount++;
		}
		CreatePatternBullet(m_tPosin[0], m_fAngle, 2, 1, 30.f);
		CreatePatternBullet(m_tPosin[1], m_fAngle, 2, 1, 30.f);

		break;
	}
}

void CTrainBoss::InitPattern()
{
	switch (m_iPatternNum)
	{
	case 0 :
		//앵글값
		//공격주기
		m_fPatternAngle = 10.f;
		m_iAttLate = 300;
		m_iPatternTime = 5000;
		break;
	case 1:
		m_fPatternAngle = 10.f;
		m_iAttLate = 250;
		m_iPatternTime = 5000;
		break;
	case 2:
		m_iPatternTime = 1000;
		break;
	case 3:
		m_fPatternAngle = 10.f;
		m_iAttLate = 500;
		m_iPatternTime = 2500;
		break;
	}
}

void CTrainBoss::Release()
{
}
