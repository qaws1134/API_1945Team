#pragma once
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "Monster.h"
class CRobot final :
	public CMonster
{
public:
	explicit CRobot();
	virtual ~CRobot();

public:
	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Render(HDC _DC);
	virtual void Release() override;

	//��ġ,����, ���ϳѹ�, �Ѿ� Ÿ��, ����, ����

	void CreatePatternBullet(D3DXVECTOR3 _vPos, float _fAngle, int _PatternNum, int _iBulletType, float _fOffset);



private:
	void Begin();
	void AttPattern();
	void InitPattern();
	void CreatePanle(M_ANGLE::DIRANGLE _eID);
	void CRobot::CreatePanle(M_ANGLE::DIRANGLE _eID, float fOffset);
private:
	D3DXVECTOR3 m_tPosin;

	D3DXVECTOR3 vJumpPos[3];

	bool m_bBegin;	//����
	bool m_bBegin2;
	bool m_bPatternOn;	//���� �Է��� �ȹ���
	DWORD m_dwPatternTime;

	float m_fPatternAngle;

	int m_iPatternTime;
	int m_iPatternNum;

	bool m_bPanel=false;
	int randomJump;
	int m_iPrePatternNum;
	int m_iCount;

	float m_fRev = 1;
	// CMonster��(��) ���� ��ӵ�

};


#endif // !__ROBOT_H__
