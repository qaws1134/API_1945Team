#pragma once
#include "Monster.h"
class CPinPanel :
	public CMonster
{
public:
	CPinPanel();
	virtual ~CPinPanel();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Late_Update();

private:
	bool m_bBulletOn;
	bool m_bInitDir;
};

