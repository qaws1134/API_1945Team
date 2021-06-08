#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Create_Letter(HDC _DC, const TCHAR * _pFont, const TCHAR * _pLetter, int _x, int _y, int _size);
	void Draw_Paint(HDC _DC);
	void Draw_Rocket(HDC _DC);
	void Load_Rocket();
	void Move_Plane();
private:
	DWORD	dwDelay;
	DWORD	dwTime;
	bool	m_bColor;

	D3DXVECTOR3 m_pAirPlane[62];
	D3DXVECTOR3 m_pAirPlane_draw[62];
	float m_fAngle;
	INFO  m_tInfo;
	float m_fSpeed;
	bool  m_bDir;

};

