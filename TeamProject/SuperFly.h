#pragma once
#include "Obj.h"
#include "Basic_Bullet.h"
class CSuperFly :
	public CObj
{
public:
	CSuperFly();
	virtual ~CSuperFly();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Basic_Attack();

public:
	void Target_Attack();

public:
	void Correct_Rect();
private:
	template <typename T>
	CObj* Create_SuperFlyBullet(float _x, float _y, float _Angle, float _xSize, float _ySize, Basic_Bullet::BULLET_STATE _STATE)
	{
		CObj* pObj = new T;
		((T*)(pObj))->Set_Size(_xSize, _ySize);
		((T*)(pObj))->Set_BulletType(_STATE);
		((T*)(pObj))->Set_Pos(_x, _y);
		pObj->Initialize();
		return pObj;
	}

private:
	DWORD         m_Time;
	DWORD         m_delay;

	INFO         m_Fly;
};
