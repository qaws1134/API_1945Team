#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void Set_ScrollY(float _y) { m_fScrollY += _y; }

public:
	float Get_ScrollY() const { return m_fScrollY; }


public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CScrollMgr* m_pInstance;

	float	m_fScrollY;
};

