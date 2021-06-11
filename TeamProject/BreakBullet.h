#pragma once
#include "Monster_Bullet.h"
class CBreakBullet :
	public CMonster_Bullet
{
public:
	CBreakBullet();
	virtual ~CBreakBullet();

	// CMonster_Bullet을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void WriteMatrix() override;
	virtual void Render(HDC _DC);
private:
	DWORD m_dwExitTime;
	int m_iExitTime;

};

