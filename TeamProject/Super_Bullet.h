#pragma once
#include "Player_Bullet.h"
class Super_Bullet :
	public Player_Bullet 
{

public:
	Super_Bullet();
	virtual ~Super_Bullet();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Bomb_Update();
	void Target_Update();

public:
	void Set_Size(float _xSize, float _ySize);
	void Set_BulletType(BULLET_STATE _BULLET);

public:
	void Set_Move(bool	Move) { m_Move = Move; }


private:
	BULLET_STATE	m_eBulletType;
	bool			m_Move;
	int				m_Still;
	INFO		TestInfo;
	bool m_bMove;

};

