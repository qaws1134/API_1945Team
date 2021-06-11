#pragma once
#ifndef __POWER_PLANE_H__
#define __POWER_PLANE_H__

#include "Monster.h"
// �Ŀ��� �ִ� ����� 4���� ���� ����
class CPower_Plane final:
	public CMonster
{
public:
	explicit CPower_Plane();
	virtual ~CPower_Plane();

public :
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Dir_Plane(bool _bWalk_Out) override;
	virtual void Release() override;

private:
	bool m_bTurn;



	// CMonster��(��) ���� ��ӵ�

	// CMonster��(��) ���� ��ӵ�
};

#endif // !POWER_PLANE_H__
