#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
#include "ObjMgr.h"
class CMonster abstract:
	public CObj
{
protected:
public:
	explicit CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize()PURE;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC);
	virtual void Release() PURE;

public :
	virtual void Ai_Pattern()PURE;
	virtual void WriteMatrix(float _fRotAngle)PURE;
	virtual void Dir_Plane (bool _bWalk_Out); //스폰 후 방향과 퇴장 시 방향
	
public :
	void Set_Target();
	void Set_eDir(M_ANGLE::DIRANGLE _eDir) { m_eDir = _eDir; }
	void Set_eExitDir(M_ANGLE::DIRANGLE _eDir) { m_eExitDir = _eDir; }
	void Set_Item() { m_bItemDrop = true; }
public :
	//직선 총알
	template<typename T>
	CObj* CreateBullet()
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x , m_tInfo.vPos.y, m_vDir_Bullet);
	}
	template<typename T>
	CObj* CreateBullet(bool _bBullSize)
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y, m_vDir_Bullet, _bBullSize);
	}
	template<typename T>
	CObj* CreateBullet(float _fOffsetX, float _fOffsetY)
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x+ _fOffsetX, m_tInfo.vPos.y + _fOffsetY, m_vDir_Bullet);
	}
	template<typename T>
	CObj* CreateBullet(float _fX, float fY, float _fAngle )
	{
		return CAbstractFactory<T>::Create(_fX, fY, _fAngle);
	}

	template<typename T>
	void CreateXWayBullet(float _Angle, float _BulletNum, int _iAtt, float _fSpeed)
	{
		float fMinAngle = m_fAngle - (_Angle / 2);

		for (int i = 0; i < _BulletNum; i++)
		{
			fMinAngle += (float)((_Angle / _BulletNum));
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<T>(fMinAngle, _iAtt, _fSpeed), _eID);
		}
	}
protected:
	CObj* m_pPlayer;
	bool m_bWalk_Out;	//등장 퇴장 패턴 판단
	bool m_bItemDrop;


	D3DXVECTOR3 m_vDir_Bullet;
	DWORD m_dwExitTime;
	int m_iExitLate;
	
	float m_fTurnAngle;
	DWORD m_dwAttTime;
	int m_iAttLate;
	
	D3DXVECTOR3 m_vPMonster[20];
	D3DXVECTOR3 m_vQMonster[20];


	M_ANGLE::DIRANGLE m_eDir;
	M_ANGLE::DIRANGLE m_eExitDir;

};

#endif // !__MONSTER_H__
