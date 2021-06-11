#pragma once
#include "Obj.h"
class CMyUI :
	public CObj
{
public:
	CMyUI();
	virtual ~CMyUI();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_PlayerData();
public:
	void Draw_Line(HDC _DC);
	void Write_Word(HDC _DC);
	void Draw_State(HDC _DC);


public:
	void Create_Letter(HDC _DC, const TCHAR * _pFont, const TCHAR * _pLetter, int _x, int _y, int _size);
	int m_iScore;
	int m_iBombN;
	int m_iSuperShotGauge;
	int m_iSuperShotN;
	int m_iChargeShotN;
	int m_iChargeGauge;

	D3DXVECTOR3 m_pAirPlane[62];
	D3DXVECTOR3 m_pAirPlane_draw[62];

};

