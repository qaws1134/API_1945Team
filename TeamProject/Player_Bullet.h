#pragma once
#include "Bullet.h"
class Player_Bullet :
	public CBullet
{
public:
	enum BULLET_STATE { BASIC, CHARGE, BOMB, END };
public:
	Player_Bullet();
	virtual ~Player_Bullet();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;


};

