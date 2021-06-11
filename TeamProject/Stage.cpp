#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "Power_Plane.h"
#include "Rush_Plane.h"
#include "Tank.h"
#include "Player.h"
#include "MyUI.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "BackGround.h"
CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPower_Plane>::Create(), OBJID::MONSTER);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CRush_Plane>::Create(), OBJID::MONSTER);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CTank>::Create(), OBJID::MONSTER);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMyUI>::Create(), OBJID::STATE);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBackGround>::Create(), OBJID::STATE);

}

void CStage::Update()
{
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
