#pragma once
#include "Bullet.h"
class CMonster_Bullet :
	public CBullet
{
public:
	CMonster_Bullet();
	virtual ~CMonster_Bullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

