#pragma once
#include "Bullet.h"
class Player_Bullet :
	public CBullet
{
public:
	Player_Bullet();
	virtual ~Player_Bullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};

