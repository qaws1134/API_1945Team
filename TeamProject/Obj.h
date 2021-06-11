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
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_Dir(D3DXVECTOR3 _vDir) { m_tInfo.vDir = _vDir; }
	void Set_Pos(float _x, float _y) { m_tInfo.vPos.x = _x; m_tInfo.vPos.y = _y; }
	RECT Get_Rect() { return m_tRect; };
public :
	INFO Get_Info() { return m_tInfo; }
	virtual void Update_Rect();

public:
	void Set_Hp();
	int Get_Hp();

public:
	const RENDERID::ID& Get_RenderID() const { return m_eRenderID; }
protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	
	bool	m_bDead;
	float	m_fSpeed;
	float	m_fAngle;

	int		m_iHp;

	RENDERID::ID	m_eRenderID;

	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_vP[4];
	D3DXVECTOR3 m_vQ[4];
};

