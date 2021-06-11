#pragma once
#ifndef __TRAINBOSS_H__
#define __TRAINBOSS_H__

#include "Monster.h"
class CTrainBoss final:
	public CMonster
{
public:
	explicit CTrainBoss();
	virtual ~CTrainBoss();

public :
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
private:


	D3DXVECTOR3 m_tPosin[2];


	bool m_bBegin;	//����
	bool m_bBegin2;
	bool m_bPatternOn;	//���� �Է��� �ȹ���
	DWORD m_dwPatternTime;
	CObj* Cannon[2];

	float m_fPatternAngle;

	int m_iPatternTime;
	int m_iPatternNum;

	int m_iPrePatternNum;
	int m_iCount;

	// CMonster��(��) ���� ��ӵ�

};


#endif // !__TRAINBOSS_H__
