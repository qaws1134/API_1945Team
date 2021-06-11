#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "Power_Plane.h"
#include "Rush_Plane.h"
#include "Tank.h"
#include "Player.h"

#include "FlyWing.h"
#include "Power.h"
#include "Boom.h"
#include "TowerCannon.h"
#include "TrainBoss.h"
#include "PosinCannon.h"
#include "Robot.h"

#include "MyUI.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "BackGround.h"

CStage::CStage() : m_iPreFrame(0), m_bPowerSpawn(false)
{
	iPowerSpawnCount = 0;
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER);


	m_iPreFrame = g_iStageFrame;

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMyUI>::Create(), OBJID::STATE);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBackGround>::Create(), OBJID::STATE);
}

void CStage::Update()
{
	if (m_iPreFrame == g_iStageFrame)
	{
		
		
		m_iPreFrame++;



		CreatePowerPlane(4);		

		



		CreateMonster<CTank>(4, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 50 ),0.f,0.f }, false);
		CreateMonster<CTank>(9, { float(((WINCX - WINCXZERO) >> 1) + WINCXZERO + 200),0.f,0.f }, false);

		CreateCrossRush(8,0);
		CreateCrossRush(11, 1);
		CreateCrossRush(17,0);
		CreateMonster<CFlyWing>(16, { float(WINCX), 100.f,0.f }, M_ANGLE::LEFT,  M_ANGLE::RIGHT);

		CreateMonster<CTowerCannon>(17, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO)-200), 0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN);
		CreateMonster<CTank>(22, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 210),0.f,0.f }, false);
		CreateMonster<CTank>(23, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 260),0.f,0.f }, false);
		CreateMonster<CTank>(25, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 150),0.f,0.f }, false);

		CreatePowerPlane(27);

		CreateMonster<CTowerCannon>(24, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 100), 0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN);

		CreateMonster<CTank>(31, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) -100),0.f,0.f }, false);
		CreateMonster<CTank>(33, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 150),0.f,0.f }, false);

		CreatePowerPlane(33);
		CreateCrossRush(25, 1);
		CreateCrossRush(29,0);
		CreateCrossRush(33, 1);

		CreateMonster<CTowerCannon>(34, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 180), 0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN);
		CreateMonster<CTowerCannon>(35, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250), 0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN);

		CreateMonster<CFlyWing>(35, { float(WINCXZERO),100.f,0.f },true,M_ANGLE::RIGHT, M_ANGLE::LEFT );

		CreateMonster<CTank>(36, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 250),0.f,0.f }, false);
		CreateMonster<CTank>(38, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 250),0.f,0.f }, false);

		CreateMonster<CTank>(43, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 150),0.f,0.f }, false);

		CreatePowerPlane(42);
		CreateCrossRush(40, 0);
		CreateCrossRush(44, 4);

		CreateMonster<CFlyWing>(47, { float(WINCX),100.f,0.f }, M_ANGLE::LEFT, M_ANGLE::RIGHT);

		CreateMonster<CTank>(48, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 100),0.f,0.f }, false);

		CreateMonster<CTank>(50, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250),0.f,0.f }, false);
		CreateMonster<CTank>(52, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250),0.f,0.f }, false);

		CreateMonster<CTowerCannon>(51, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 230), 0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN);

		CreatePowerPlane(55);
		CreateCrossRush(58, 3);
		CreateCrossRush(61, 0);

		CreateCrossRush(63, 1);
	//	CreateCrossRush(66, 1);
		CreateCrossRush(68, 3);

		CreateMonster<CFlyWing>(67, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 50),0.f,0.f }, false, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT,true);
		//CreateCrossRush(68, 0);
		CreateCrossRush(70, 0);


		CreateMonster<CTank>(72, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250),float(WINCY),0.f }, M_ANGLE::UP, M_ANGLE::DOWN);
		CreateMonster<CTank>(74, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250),float(WINCY),0.f }, M_ANGLE::UP, M_ANGLE::DOWN);
		CreateMonster<CTank>(76, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 250),float(WINCY),0.f }, M_ANGLE::UP, M_ANGLE::DOWN);


		CreateMonster<CFlyWing>(80, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 150),0.f,0.f }, true, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT, true);
		CreateMonster<CFlyWing>(80, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 150),0.f,0.f }, false, M_ANGLE::DOWN, M_ANGLE::DOWN_RIGHT, true);

		CreateCrossRush(83, 4);
		CreateCrossRush(86, 4);
		CreateCrossRush(89, 5);
		CreateCrossRush(91, 5);


		CreateMonster<CFlyWing>(98, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 200),0.f,0.f }, false, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT, true);
		CreateMonster<CFlyWing>(98, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 200),0.f,0.f }, false, M_ANGLE::DOWN, M_ANGLE::DOWN_RIGHT, true);

		//건물 포탑 
		CreateMonster<CTrainBoss>(123, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO)),0.f,0.f }, false);
	}
	CObjMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Collision_Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC _DC)
{
	CObjMgr::Get_Instance()->Render(_DC);
}

void CStage::Release()
{

}

void CStage::CreatePowerPlane(int _StageFrame)
{
	CreateMonster<CPower_Plane>(_StageFrame,    { float(((WINCX - WINCXZERO) >> 1) + WINCXZERO)	,0.f,0.f });
	CreateMonster<CPower_Plane>(_StageFrame+1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 50.f)	,0.f,0.f });
	CreateMonster<CPower_Plane>(_StageFrame+2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 100.f),0.f,0.f });
	CreateMonster<CPower_Plane>(_StageFrame+3, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 150.f),0.f,0.f }, true);
}

void CStage::CreateCrossRush(int _StageFrame, int _Pattern)
{
	if (_Pattern == 0)
	{
		CreateMonster<CRush_Plane>(_StageFrame, {     float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 100),0.f,0.f }, M_ANGLE::DOWN_RIGHT, M_ANGLE::UP_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame + 2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 100),0.f,0.f }, M_ANGLE::DOWN_RIGHT, M_ANGLE::DOWN_RIGHT);

		CreateMonster<CRush_Plane>(_StageFrame + 1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 100),0.f,0.f }, M_ANGLE::DOWN_LEFT, M_ANGLE::UP_LEFT);
		CreateMonster<CRush_Plane>(_StageFrame + 3, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 100),0.f,0.f }, M_ANGLE::DOWN_LEFT, M_ANGLE::DOWN_LEFT);
	}
	else if (_Pattern == 1)
	{
		CreateMonster<CRush_Plane>(_StageFrame,	  { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 200),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::UP_LEFT);
		CreateMonster<CRush_Plane>(_StageFrame+2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 50),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT);

		CreateMonster<CRush_Plane>(_StageFrame+1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 200),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::UP_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame+3, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 50),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_RIGHT);
	}
	else if (_Pattern == 3)
	{
		CreateMonster<CRush_Plane>(_StageFrame, {   float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) -280),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame+1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) +280),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT);
		CreateMonster<CRush_Plane>(_StageFrame+2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) +60),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame+2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) ),0.f,0.f }, M_ANGLE::DOWN, M_ANGLE::DOWN_LEFT);
	}
	else if (_Pattern == 4)
	{
		CreateMonster<CRush_Plane>(_StageFrame, {     float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 200),0.f,0.f }, M_ANGLE::DOWN_RIGHT, M_ANGLE::DOWN_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame + 1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 200),0.f,0.f }, M_ANGLE::DOWN_RIGHT, M_ANGLE::DOWN_RIGHT);
		CreateMonster<CRush_Plane>(_StageFrame + 2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) - 200),0.f,0.f }, M_ANGLE::DOWN_RIGHT, M_ANGLE::DOWN_RIGHT);
	}
	else if (_Pattern == 5)
	{
		CreateMonster<CRush_Plane>(_StageFrame, {     float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 200),0.f,0.f }, M_ANGLE::DOWN_LEFT, M_ANGLE::DOWN_LEFT);
		CreateMonster<CRush_Plane>(_StageFrame + 1, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 200),0.f,0.f }, M_ANGLE::DOWN_LEFT, M_ANGLE::DOWN_LEFT);
		CreateMonster<CRush_Plane>(_StageFrame + 2, { float((((WINCX - WINCXZERO) >> 1) + WINCXZERO) + 200),0.f,0.f }, M_ANGLE::DOWN_LEFT, M_ANGLE::DOWN_LEFT);
	}

}

