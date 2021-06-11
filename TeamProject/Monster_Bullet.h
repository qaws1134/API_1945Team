#pragma once
#include "Bullet.h"
class CMonster_Bullet :
	public CBullet
{
public:
	CMonster_Bullet();
	virtual ~CMonster_Bullet();

public:
	virtual void Initialize()PURE;
	virtual int Update() ;
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release() ;

public :
	void Set_BulletType(int _iType) { m_iBulletType = _iType; }
	void Set_Size(D3DXVECTOR3 _vSize) { m_tInfo.vSize = _vSize; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }

public :
	virtual void WriteMatrix()PURE;


protected:
	float m_fRotAngle;
	int m_iMaxIdx;
	//bool m_bMiddle;
	int m_iBulletType;
	D3DXVECTOR3 m_vPBullet[20];
	D3DXVECTOR3 m_vQBullet[20];
};

