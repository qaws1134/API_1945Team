#pragma once
#define Bullet_LaunchN 4
#define Charge_Bullet_LaunchN 4
#define Max_Player_Angle 60
#define Min_Player_Angle -60
#define Charge_Gauge_Max 200
#include "Obj.h"
#include "Basic_Bullet.h"
#include "Bullet.h"
class CPlayer :
	public CObj
{
public:
	enum BULLET_LEVEL { LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, CHARGE, BOMB, END };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Update_Rect() override;
public:
	void Add_Level();
	void Add_Bomb();

private:
	void Key_Check();
	void State_Change();
	void Bullet_Launch();
private:
	void Basic_Attack();
	void Level2_Attack();
	void Level3_Attack();
	void Level4_Attack();
	void Level5_Attack();
	void Level6_Attack();
private:
	void Charge_Shot();
	void Bomb();
private:
	template <typename T>
	CObj* Create_PlayerBullet(float _x, float _y, float _Angle,  float _xSize, float _ySize, Basic_Bullet::BULLET_STATE _STATE)
	{
		CObj* pObj = new T;
		((Basic_Bullet*)(pObj))->Set_Size(_xSize, _ySize);
		((Basic_Bullet*)(pObj))->Set_BulletType(_STATE);
		((Basic_Bullet*)(pObj))->Set_Pos(_x, _y);
		pObj->Initialize();
		return pObj;
	}


private:
	float			m_fPosinAngle;

	DWORD			m_Time;
	DWORD			m_delay;

	BULLET_LEVEL			m_eBullet_Type;
	BULLET_LEVEL			m_eBeforeBullet_Type;
	int				m_iBulletLevel;
	int				m_Bullet_State;
	bool			m_bBullet_Launch;
	int				m_Bullet_LaunchN;

	bool			m_bCharge_Shot;
	bool			m_bCharge_Bomb;

	CObj*			m_Charge_Shot;
	CObj*			m_Bomb;

	int				m_iBombN;
	int				m_Charge_Gauge;

	bool			m_bFullGauge;
};

