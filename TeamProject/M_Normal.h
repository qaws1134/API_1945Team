#pragma once
#include "Monster_Bullet.h"
class CM_Normal final:
	public CMonster_Bullet
{
public:
	explicit CM_Normal();
	virtual ~CM_Normal();

public :
	virtual void Initialize() override;
	virtual void WriteMatrix() override;



};

