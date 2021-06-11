#pragma once
#define Bullet_LaunchN 4
#define Charge_Bullet_LaunchN 4
#define Max_Player_Angle 60
#define Min_Player_Angle -60
#define Charge_Gauge_Max 500
#define	Bomb_Gauge_Max 2000
#include "Obj.h"
#include "Basic_Bullet.h"
#include "Bullet.h"
class CPlayer :
	public CObj
{
public:
	enum BULLET_LEVEL { LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, CHARGE, BOMB, END };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Update_Rect() override;
public:
	void Add_Level();
	void Add_Bomb();

public:
	int Get_BombN();
	int Get_SuperShot_Gauge();
	int Get_Score();
	int Get_Super_Shot();
	int Get_Charge_Shot();
	int Get_Charge_Shot_Gauge();
	int Get_Level() { return m_iBulletLevel; }
public:
	void Super_Shot_Check();
public:
	void Set_BombN(int n);
	void Set_SuperShot_Gauge(int n);
	void Set_Score(int n);
private:
	void Key_Check();
	void State_Change();
	void Bullet_Launch();
private:
	void Basic_Attack();
	void Level2_Attack();
	void Level3_Attack();
	void Level4_Attack();
	void Level5_Attack();
	void Level6_Attack();
private:
	void Charge_Shot();
	void Bomb();

public:
	void Replay();
	void Check_Hp();
public:
	void Draw_Rect(HDC _DC);
public:
	void Dead_Player();
public:
	void Set_Player();

public:
	bool Get_DeadMove();
private:
	template <typename T>
	CObj* Create_PlayerBullet(float _x, float _y, float _Angle,  float _xSize, float _ySize, Basic_Bullet::BULLET_STATE _STATE)
	{
		CObj* pObj = new T;
		((Basic_Bullet*)(pObj))->Set_Size(_xSize, _ySize);
		((Basic_Bullet*)(pObj))->Set_BulletType(_STATE);
		((Basic_Bullet*)(pObj))->Set_Pos(_x, _y);
		pObj->Initialize();
		return pObj;
	}


private:
	float			m_fPosinAngle;

	DWORD			m_Time;
	DWORD			m_delay;

	BULLET_LEVEL			m_eBullet_Type;
	BULLET_LEVEL			m_eBeforeBullet_Type;
	int				m_iBulletLevel;
	int				m_Bullet_State;
	bool			m_bBullet_Launch;
	int				m_Bullet_LaunchN;



	//Bomb
	CObj*			m_Bomb;
	int				m_iBombN;
	bool			m_bCharge_Bomb;

	//Charge_Shot
	CObj*			m_pCharge_Shot;
	int				m_Charge_Gauge;
	int				m_iChargeShot;
	bool			m_bChargeShot;


	int				m_iScore;

	//Super_Shot
	int				m_iSuperShot;
	int				m_iSuperShot_Gauge;

	//플레이어 모습
	D3DXVECTOR3 m_pPlayer[30];
	D3DXVECTOR3 m_pDraw_Player[30];
	
	RECT			Dead_Effect[5];
	int				Dead_EffectSize[5];
	bool			m_bDead_Effect_Sequence;
	bool			m_bDead_Effect_Move;
	bool			m_bDeadMove;
	int				Dead_Montion_Num;

	bool			m_bBlink;

	int				m_iTime;
	int				m_iDelay;
};

