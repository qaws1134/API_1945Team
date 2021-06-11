#pragma once
#include "Player_Bullet.h"
class Basic_Bullet :
	public Player_Bullet
{

public:
	Basic_Bullet();
	virtual ~Basic_Bullet();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void BasicBullet_Update();
	void ChargeBullet_Update();
public:
	void Set_Size(float _xSize, float _ySize);
	Player_Bullet::BULLET_STATE Get_BulletState();
	void Set_BulletType(Player_Bullet::BULLET_STATE _BulletState);
public:
	void Set_Move(bool   Move) { m_Move = Move; }
public:
	void Correct_Rect();
public:
	BULLET_STATE Bullet_state();
private:
	BULLET_STATE   m_eBulletType;
	bool         m_Move;
	int            m_Still;

};
