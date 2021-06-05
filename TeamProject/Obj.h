#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Set_Dead() { m_bDead = true; }

public:
	const RENDERID::ID& Get_RenderID() const { return m_eRenderID; }

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
protected:
	void Update_Rect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	bool	m_bDead;
	float	m_fSpeed;
	float	m_fAngle;

	RENDERID::ID	m_eRenderID;

	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_vP[4];
	D3DXVECTOR3 m_vQ[4];
};

