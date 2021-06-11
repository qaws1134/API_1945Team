#pragma once
#include "Scene.h"
#include "ObjMgr.h"
class CObj;
class CMonster;
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


public :
	void CreatePowerPlane(int _StageFrame);
	void CreateCrossRush(int _StageFrame,int _Pattern);
public :
	//»ý¼º½Ã v_pos, e_eangledir e_exitangledir, b_reverse , b_itemDrop

	template<typename T>
	void CreateMonster(int _iFrame,D3DXVECTOR3 _vPos
		, bool _bItemDrop = 0 )
	{
		//MonsterCount pre next 
		if (_iFrame == g_iStageFrame)
		{
			T*pMonster = new T;
			pMonster->Initialize();
			pMonster->Set_Pos(_vPos.x, _vPos.y);
			if (_bItemDrop)
				pMonster->Set_Item();
			CObjMgr::Get_Instance()->Add_Object(pMonster, OBJID::MONSTER);
		}
	}
	template<typename T>
	void CreateMonster(int _iFrame, D3DXVECTOR3 _vPos
		, M_ANGLE::DIRANGLE _eBeginDir
		, M_ANGLE::DIRANGLE _eExitDir)
	{
		if (_iFrame == g_iStageFrame)
		{
			T*pMonster = new T;
			pMonster->Initialize();
			pMonster->Set_Pos(_vPos.x, _vPos.y);
			pMonster->Set_eDir(_eBeginDir);
			pMonster->Set_eExitDir(_eExitDir);

			CObjMgr::Get_Instance()->Add_Object(pMonster, OBJID::MONSTER);
		}
	}
	template<typename T>
	void CreateMonster(int _iFrame, D3DXVECTOR3 _vPos
		, bool _bItemDrop 
		, M_ANGLE::DIRANGLE _eBeginDir 
		, M_ANGLE::DIRANGLE _eExitDir
		, bool _bReverse  = 0)
	{
		if (_iFrame == g_iStageFrame)
		{
			T*pMonster = new T;
			pMonster->Initialize();
			pMonster->Set_Pos(_vPos.x, _vPos.y);
			pMonster->Set_eDir(_eBeginDir);
			pMonster->Set_eExitDir(_eExitDir);
			if (_bItemDrop)
				pMonster->Set_Item();
			if (_bReverse != 0)
				pMonster->Set_Reverse();
			CObjMgr::Get_Instance()->Add_Object(pMonster, OBJID::MONSTER);
		}
	}



private:

	int iPowerSpawnCount;
	bool m_bPowerSpawn;
	int m_iPreFrame;
};

