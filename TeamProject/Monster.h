#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
#include "ObjMgr.h"
class CMonster abstract:
	public CObj
{
public:
	explicit CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize()PURE;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC);
	virtual void Release() override;

public :
	virtual void Ai_Pattern()PURE;
	virtual void WriteMatrix(float _fRotAngle)PURE;
	virtual void Dir_Plane (bool _bWalk_Out)PURE; //스폰 후 방향과 퇴장 시 방향
	
public :
	void CMonster::Set_Target(CObj * _pPlayer);
public :
	//직선 총알
	template<typename T>
	CObj* CreateBullet()
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x,m_tInfo.vPos.y+ (m_tInfo.vSize.y*0.5f), m_vDir_Bullet);
	}
	//목표- 나 =  방향
	//범위,총알 갯수, 공격력 , 총알 속도
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

	DWORD m_dwAttTime;
	int m_iAttLate;

};

#endif // !__MONSTER_H__
