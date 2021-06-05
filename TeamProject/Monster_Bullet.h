#pragma once
#include "Bullet.h"
class Monster_Bullet :
	public CBullet
{
public:
	Monster_Bullet();
	virtual ~Monster_Bullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

